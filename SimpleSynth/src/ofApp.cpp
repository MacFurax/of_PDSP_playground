#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetWindowTitle("sImpLe sYnTh");

  setup_GUI();
  setup_PDSP();
  
 
}

void ofApp::setup_PDSP()
{
  // Patching ---------------------------------------------------------
  // set up control
  // you can use setPolyMode(int maxNotes, int unisonVoices) or setMonoMode(int unisonVoices, bool legato, MonoPriority priority)
  midiKeys.setPolyMode(polyphonyVoiceCount, unisonVoiceCount);

  // voices is a vector of synth voices, we resize it to the midiKeys voice number     
  voicesNum = midiKeys.getVoicesNumber();

  // set keyboard polyphony
  keyboard.setPolyMode(polyphonyVoiceCount);

  synth.setup(voicesNum);

  int voiceIndex = 0;
  for (auto& v : synth.voices)
  {
    // connect each voice to a midi pitch and trigger output
    midiKeys.out_trig(voiceIndex) >> synth.voices[voiceIndex].in("trig");
    midiKeys.out_pitch(voiceIndex) >> synth.voices[voiceIndex].in("pitch");

    /*cutoff >> synth.voices[voiceIndex].in("cutoff");
    reso >> synth.voices[voiceIndex].in("reso");*/

    // patch OSC settings

    waveForm >> synth.voices[voiceIndex].osc.waveForm.in_select();
    pulseWidth >> synth.voices[voiceIndex].osc.in("pw");
    attack >> synth.voices[voiceIndex].osc.adsr.in_attack();
    decay >> synth.voices[voiceIndex].osc.adsr.in_decay();
    sustain >> synth.voices[voiceIndex].osc.adsr.in_sustain();
    release >> synth.voices[voiceIndex].osc.adsr.in_release();

    detune >> synth.voices[voiceIndex].osc.detuneCoarse;
    detuneFine >> synth.voices[voiceIndex].osc.detuneFine;

    // patch each voice to output gain
    synth.voices[voiceIndex] >> gain;

    voiceIndex++;
  }

  // patch gain to audio engine output 
  gain >> engine.audio_out(0);
  gain >> engine.audio_out(1);

  // audio / midi setup----------------------------

  //get MIDI control
  cout << "Number of MIDI IN port " << midiIn.getPortCount() << "\n";
  for (auto s : midiIn.getPortList())
  {
    cout << "port :" << s << "\n";
  }
  midiIn.listPorts();
  midiIn.openPort(selectedMIDIIN); //set the right port !!!


  // for our midi controllers to work we have to add them to the engine, so it know it has to process them
  engine.addMidiController(midiKeys, midiIn); // add midi processing to the engine
  engine.addMidiController(midiCCs, midiIn);  // add midi processing to the engine
  engine.listDevices();
  engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup(44100, 512, 3);
}

void ofApp::setup_GUI()
{
  // load a different font
  string fontPath = ofToDataPath("./fonts/Roboto/Roboto-Light.ttf", true);
  cout << "Load ImGui font from \n[" << fontPath << "]\n";

  int fontIdx = gui.addFont(fontPath, 20.0f);
  gui.SetDefaultFont(fontIdx);

  gui.enableDocking();

  // Init ImGui with CorporateGrey Theme
  gui.setup( static_cast<ofxImGui::BaseTheme*>(new ofxImGui::CorporateGreyTheme()) );
  
  gain.set("gain", 0, -48, 12);
  gain.enableSmoothing(50.f);
  
  waveForm.set("wave form", 0, 0, 3);
  pulseWidth.set("pw", 0.5f, 0.5f, 0.9f);
  pulseWidth.enableSmoothing(100.f);
  attack.set("attack", 0, 0, 1000);
  attack.enableSmoothing(50.f);
  decay.set("decay", 100, 0, 1000);
  decay.enableSmoothing(50.f);
  sustain.set("sustain", 0.5f, 0.0f, 1.0f);
  sustain.enableSmoothing(50.f);
  release.set("release", 1000, 0, 5000);
  release.enableSmoothing(50.f);
  detune.set("detune", 0.0f, 0.0f, 8.0f);
  detune.enableSmoothing(50.f);
  detuneFine.set("fine", 0.0f, 0.0f, 1.0f);
  detuneFine.enableSmoothing(50.f);

  waveForm2.set("wave form", 0, 0, 3);
  pulseWidth2.set("pw", 0.5f, 0.5f, 0.9f);
  pulseWidth2.enableSmoothing(100.f);
  attack2.set("attack", 0.0f, 0.0f, 1000.0f);
  attack2.enableSmoothing(50.f);
  decay2.set("decay", 100.0f, 0.0f, 1000.0f);
  decay2.enableSmoothing(50.f);
  sustain2.set("sustain", 0.5f, 0.0f, 1.0f);
  sustain2.enableSmoothing(50.f);
  release2.set("release", 1000.0f, 0.0f, 5000.0f);
  release2.enableSmoothing(50.f);
  detune2.set("detune", 0.0f, -8.0f, 8.0f);
  detune2.enableSmoothing(50.f);
  detuneFine2.set("fine", 0.0f, -1.0f, 1.0f);
  detuneFine2.enableSmoothing(50.f);

  knobValue.set("Knob", 10.0f, 0.0f, 20.0f);
  knobValue.enableSmoothing(50.f);

  RefreshMIDIInDeviceList();
}

void ofApp::RefreshMIDIInDeviceList()
{
  midiInDeviceNames = midiIn.getPortList();
  midiInDeviceCount = midiInDeviceNames.size();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  draw_UI();
}

void ofApp::draw_UI()
{
  gui.begin();
  
  if (ImGui::Begin("MIDI IN"))
  {
    if (midiInDeviceCount > 0)
    {
      int currentSelectedDevice = selectedMIDIIN;
      ofxImGui::VectorCombo("Devices", &selectedMIDIIN, midiInDeviceNames);
      if (currentSelectedDevice != selectedMIDIIN)
      {
        midiIn.closePort();
        midiIn.openPort(selectedMIDIIN);
      }
    }
    else
    {
      ImGui::Text("No MIDI in devices");
    }
    if (ImGui::Button("Refresh device list"))
    {
      RefreshMIDIInDeviceList();
    }
  }
  ImGui::End();

  auto mainSettings = ofxImGui::Settings();

  ofxImGui::BeginWindow("Main Out", mainSettings, false);
    ofxImGui::AddParameter(gain.getOFParameterInt());
    ofxImGui::AddKnob(knobValue.getOFParameterFloat());
  ofxImGui::EndWindow(mainSettings);

  ofxImGui::BeginWindow("OSC 1", mainSettings, false);
    ofxImGui::AddCombo( waveForm.getOFParameterInt(), waveFormes);

    ofxImGui::AddParameter(attack.getOFParameterInt());
    ofxImGui::AddParameter(decay.getOFParameterInt());
    ofxImGui::AddParameter(sustain.getOFParameterFloat());
    ofxImGui::AddParameter(release.getOFParameterInt());

    ofxImGui::AddParameter(pulseWidth.getOFParameterFloat());
    
    ofxImGui::AddParameter(detune.getOFParameterFloat());
    ofxImGui::AddParameter(detuneFine.getOFParameterFloat());

  ofxImGui::EndWindow(mainSettings);

  ofxImGui::BeginWindow("OSC 2", mainSettings, false);
    ofxImGui::AddCombo(waveForm2.getOFParameterInt(), waveFormes);

    ofxImGui::AddKnob(detune2.getOFParameterFloat());
    ImGui::SameLine();
    ofxImGui::AddKnob(detuneFine2.getOFParameterFloat());

    if (waveForm2.get() == 3)
    {
      ImGui::SameLine();
      ofxImGui::AddKnob(pulseWidth2.getOFParameterFloat());
    }

    ofxImGui::AddKnob(attack2.getOFParameterFloat());
    ImGui::SameLine();
    ofxImGui::AddKnob(decay2.getOFParameterFloat());
    ImGui::SameLine();
    ofxImGui::AddKnob(sustain2.getOFParameterFloat());
    ImGui::SameLine();
    ofxImGui::AddKnob(release2.getOFParameterFloat());

  ofxImGui::EndWindow(mainSettings);


  gui.end();
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
