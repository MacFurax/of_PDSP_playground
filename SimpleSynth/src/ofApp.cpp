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

    // patch ADSR envelope
    attack >> synth.voices[voiceIndex].ampEnv.in_attack();
    decay >> synth.voices[voiceIndex].ampEnv.in_decay();
    sustain >> synth.voices[voiceIndex].ampEnv.in_sustain();
    release >> synth.voices[voiceIndex].ampEnv.in_release();

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
  midiIn.openPort(2); //set the right port !!!


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
  string fontPath = ofToDataPath("./fonts/Roboto-Regular.ttf", true);
  cout << "Load ImGui font from \n[" << fontPath << "]\n";

  int fontIdx = gui.addFont(fontPath, 20.0f);
  gui.SetDefaultFont(fontIdx);

  // Initi ImGui with CorporateGrey Theme
  gui.setup( static_cast<ofxImGui::BaseTheme*>(new ofxImGui::CorporateGreyTheme()) );

  gain.set("gain", 0, -48, 12);
  gain.enableSmoothing(50.f);
  attack.set("attack", 0, 0, 1000);
  attack.enableSmoothing(50.f);
  decay.set("decay", 100, 0, 1000);
  decay.enableSmoothing(50.f);
  sustain.set("sustain", 0.5f, 0.0f, 1.0f);
  sustain.enableSmoothing(50.f);
  release.set("release", 1000, 0, 5000);
  release.enableSmoothing(50.f);
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

  auto mainSettings = ofxImGui::Settings();

  if (ofxImGui::BeginWindow("-O Main O-", mainSettings, false))
  {
    ofxImGui::AddParameter(gain.getOFParameterInt());
    ofxImGui::AddParameter(attack.getOFParameterInt());
    ofxImGui::AddParameter(decay.getOFParameterInt());
    ofxImGui::AddParameter(sustain.getOFParameterFloat());
    ofxImGui::AddParameter(release.getOFParameterInt());
  }
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
