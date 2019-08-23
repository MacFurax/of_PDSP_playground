#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetEscapeQuitsApp(false);

  // ofLog will write in a log file, it will be created in data folder
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofLogToFile("app.log");

  ofSetWindowTitle("Progressive Soft Synthetizer");

  setupImGui();

  setupPDSP();

}

void ofApp::setupPDSP()
{
  
  waveSelectCtrl.set(0.0f);
  pulseWidthCtrl.set(ui_osc_pulse_width);
  pulseWidthCtrl.enableSmoothing(300);

  envAttackCtrl.set(ui_env_attack);
  envAttackCtrl.enableSmoothing(10);

  envDecayCtrl.set(ui_env_decay);
  envDecayCtrl.enableSmoothing(10);

  envSustainCtrl.set(ui_env_sustain);
  envSustainCtrl.enableSmoothing(10);

  envReleaseCtrl.set(ui_env_release);
  envReleaseCtrl.enableSmoothing(10);

  gainCtrl.set(pdsp::DBtoLin::eval(ui_gain));
  gainCtrl.enableSmoothing(30);
  gainCtrl >> mainOut.in_mod();

  keyboard.setPolyMode(8);
  int voicesNum = keyboard.getVoicesNumber();
  
  voices.resize(voicesNum);

  int channelIdx = 0;
  for (auto& v : voices)
  {
    // set envelope
    envAttackCtrl >> v.envelopes.in_attack();
    envDecayCtrl >> v.envelopes.in_decay();
    envSustainCtrl >> v.envelopes.in_sustain();
    envReleaseCtrl >> v.envelopes.in_release();

    v.waveFormSwitch.resize(4);

    v.osc.out_sine() >> v.waveFormSwitch.input(0);
    v.osc.out_triangle() >> v.waveFormSwitch.input(1);
    v.osc.out_saw() >> v.waveFormSwitch.input(2);
    v.osc.out_pulse() >> v.waveFormSwitch.input(3);

    pulseWidthCtrl >> v.osc.in_pw();

    waveSelectCtrl >> v.waveFormSwitch.in_select();

    keyboard.out_trig(channelIdx) >> v.envelopes.in_trig();
    v.envelopes >> v.amp.in_mod();

    keyboard.out_pitch(channelIdx) >> v.osc.in_pitch();

    v.waveFormSwitch >> v.amp;

    v.amp >> mainOut;

    channelIdx++;
  }

  //osc.out_sine() >> mainOut;
  
  mainOut >> engine.audio_out(0);
  mainOut >> engine.audio_out(1);

  midiIn.listPorts();

  cout << "MIDI in port count " << midiIn.getPortCount() << "\n";
  
  engine.listDevices();
  engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup(44100, 512, 3);
}

void ofApp::setupImGui()
{
  // set my font for ImGui
  string fontPath = ofToDataPath("./fonts/Roboto-Regular.ttf", true);
  int fontIdx = gui.addFont(fontPath, 16.0f);
  gui.SetDefaultFont(fontIdx);
  
  gui.enableDocking();
  gui.setup();

  //ofxImGuiEnableDocking();

  // set CorporateGrey theme
  ofxImGuiApplyCorporateGreyTheme(1.0f);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ui_Draw();
  keyboard.draw(100, 465, 200, 180);
}

void ofApp::ui_Draw()
{
  gui.begin();

  ui_Menu();

  ui_OSCWindow();
  ui_EnvelopeWindow();
  ui_FiltersWindow();
  ui_OutputWindow();

  if (ui_show_audio_settings) ui_AudioSettings();

  gui.end();
}

void ofApp::ui_Menu()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit", "ALT+F4")) 
      {
        ofExit();
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Settings"))
    {
      ImGui::MenuItem("Audio & MIDI", "", &ui_show_audio_settings);
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

void ofApp::ui_OSCWindow()
{
  ImGui::Begin("OSCs");
    ImGui::Text("OSC 1");

    // wave form selector
    ofxImGui::VectorCombo("Wave form", &ui_selected_wave_forms, wavesForms);
    if (ui_selected_wave_forms != ui_selected_wave_forms_previous)
    {
      ui_selected_wave_forms_previous = ui_selected_wave_forms;
      waveSelectCtrl.set(ui_selected_wave_forms);
    }
    
    // show OSC tuning knobs
    ImGui::Knob("Tune", &ui_osc_detune, -10.0, 10.0);
    ImGui::SameLine();
    ImGui::Knob("Fine", &ui_osc_fine_detune, -0.5, 0.5);
    ImGui::SameLine();
    static float temp = 0.0f;
    ImGui::Knob("New", &temp, -0.5, 0.5);
    
    // if wave form is pulse (square) show pulse width knob
    if (ui_selected_wave_forms == pulse_wave_idx) // pulse wave forms
    {
      ImGui::SameLine();
      static float previous_osc_pulse_width = ui_osc_pulse_width;
      ImGui::Knob("Pulse Width", &ui_osc_pulse_width, 0.1f, 0.9f);
      if (previous_osc_pulse_width != ui_osc_pulse_width)
      {
        pulseWidthCtrl.set(ui_osc_pulse_width);
      }
    }
  
  ImGui::End();
}

void ofApp::ui_EnvelopeWindow()
{
  ImGui::Begin("Envelopes");
    ImGui::Text("Trigger Envelope");
    ImGui::Knob("Attack", &ui_env_attack, 0.0, 2000.0);
    envAttackCtrl.set(ui_env_attack);
    ImGui::SameLine();
    ImGui::Knob("Decay", &ui_env_decay, 0.0, 2000.0);
    envDecayCtrl.set(ui_env_decay);
    ImGui::SameLine();
    ImGui::Knob("Sustain", &ui_env_sustain, 0.0, 1.0);
    envSustainCtrl.set(ui_env_sustain);
    ImGui::SameLine();
    ImGui::Knob("Release", &ui_env_release, 0.0, 5000.0);
    envReleaseCtrl.set(ui_env_release);
    ImGui::SameLine();

  ImGui::End();
}

void ofApp::ui_OutputWindow()
{
  ImGui::Begin("Main Output");
    float gain_before = ui_gain;
    ImGui::VSliderFloat("Gain", ImVec2(50, 230), &ui_gain, -43.0f, 12.0f, "%.2f");
    if (gain_before != ui_gain)
    {
      gainCtrl.set(pdsp::DBtoLin::eval(ui_gain));
    }

    if (ImGui::Button("Panic"))
    {
      Panic();
    }

  ImGui::End();
}

void ofApp::Panic()
{
  for (auto& v : voices)
  {
    0.0f >> v.envelopes.in_trig();
  }
}

void ofApp::ui_FiltersWindow()
{
  ImGui::Begin("Filters");

  ImGui::End();
}

void ofApp::ui_AudioSettings()
{
  ImGui::Begin("Audio Settings", &ui_show_audio_settings);

  ImGui::End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  keyboard.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  keyboard.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
