#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetEscapeQuitsApp(false);

  // ofLog will write in a log file, it will be created in data folder
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofLogToFile("app.log");

  ofSetWindowTitle("Progressive Soft Synthetizer");

  setupImGui();

  oscWaveFormSwitch.resize(wavesForms.size());
  osc.out_sine() >> oscWaveFormSwitch.input(0);
  osc.out_triangle() >> oscWaveFormSwitch.input(1);
  osc.out_saw() >> oscWaveFormSwitch.input(2);
  osc.out_pulse() >> oscWaveFormSwitch.input(3);

  pulseWidthCtrl.set(0.5f);
  pulseWidthCtrl.enableSmoothing(50);

  pulseWidthCtrl >> osc.in_pw();

  oscWaveFormSwitch >> mainOut;

  gainCtrl.enableSmoothing(50);
  gainCtrl >> mainOut.in_mod();

  mainOut >> engine.audio_out(0);
  mainOut >> engine.audio_out(1);

  engine.listDevices();
  engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup(44100, 512, 3);

}

void ofApp::setupImGui()
{
  // set my font for ImGui
  string fontPath = ofToDataPath("./fonts/Roboto-Regular.ttf", true);
  ofxImGuiSetFont(gui, fontPath, 16.0f);
  
  gui.setup();

  ofxImGuiEnableDocking();

  // set CorporateGrey theme
  ofxImGuiApplyCorporateGreyTheme(1.0f);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ui_Draw();
}

void ofApp::ui_Draw()
{
  gui.begin();
  ofxImGuiStartDocking();

  ui_Menu();

  ui_OSCWindow();
  ui_EnvelopeWindow();
  ui_FiltersWindow();
  ui_OutputWindow();

  if (ui_show_audio_settings) ui_AudioSettings();

  ofxImGuiEndDocking();
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
    ImGui::Combo("Wave form", &ui_selected_wave_forms, wavesForms);

    MyKnob("Tune", &ui_osc_detune, -10.0, 10.0);
    ImGui::SameLine();
    MyKnob("Fine", &ui_osc_fine_detune, -0.5, 0.5);
        
    if (ui_selected_wave_forms == pulse_wave_idx) // pulse wave forms
    {
      ImGui::SameLine();
      static float previous_osc_pulse_width = ui_osc_pulse_width;
      MyKnob("Pulse Width", &ui_osc_pulse_width, 0.1f, 0.9f);
      if (previous_osc_pulse_width != ui_osc_pulse_width)
      {
        pulseWidthCtrl.set(ui_osc_pulse_width);
      }
      
    }

    if (ui_selected_wave_forms != ui_selected_wave_forms_previous)
    {
      ui_selected_wave_forms_previous = ui_selected_wave_forms;
      ui_selected_wave_forms >> oscWaveFormSwitch.in_select();
    }
  
  ImGui::End();
}

void ofApp::ui_EnvelopeWindow()
{
  ImGui::Begin("Envelopes");

  ImGui::End();
}

void ofApp::ui_OutputWindow()
{
  ImGui::Begin("Main Output");
    float gain_before = ui_gain;
    ImGui::VSliderFloat("Gain", ImVec2(50, 230), &ui_gain, -43.0f, 12.0f, "%.2f");
    if (gain_before != ui_gain)
    {
      ui_gain >> dBToLin >> gainCtrl;
    }
  ImGui::End();
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

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
