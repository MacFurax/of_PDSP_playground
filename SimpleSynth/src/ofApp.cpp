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

    cutoff >> synth.voices[voiceIndex].in("cutoff");
    reso >> synth.voices[voiceIndex].in("reso");

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
  mainOutParamGroup.setName("Main Out");
  mainOutParamGroup.add(static_cast<ofAbstractParameter&>(gain.getOFParameterInt()));

  attack.set("attack", 0, 0, 1000);
  attack.enableSmoothing(50.f);
  decay.set("decay", 100, 0, 1000);
  decay.enableSmoothing(50.f);
  sustain.set("sustain", 0.5f, 0.0f, 1.0f);
  sustain.enableSmoothing(50.f);
  release.set("release", 1000, 0, 5000);
  release.enableSmoothing(50.f);
  ADSRParamGroup.setName("Envelope");
  ADSRParamGroup.add(static_cast<ofAbstractParameter&>(attack.getOFParameterInt()));
  ADSRParamGroup.add(static_cast<ofAbstractParameter&>(decay.getOFParameterInt()));
  ADSRParamGroup.add(static_cast<ofAbstractParameter&>(sustain.getOFParameterFloat()));
  ADSRParamGroup.add(static_cast<ofAbstractParameter&>(release.getOFParameterInt()));

  cutoff.set("cutoff", 82,20,136);
  reso.set("reso", 0.0f, 0.0f, 1.0f);
  filterParamGroup.setName("Filter");
  filterParamGroup.add(static_cast<ofAbstractParameter&>(cutoff.getOFParameterInt()));
  filterParamGroup.add(static_cast<ofAbstractParameter&>(reso.getOFParameterFloat()));

  filterADSRParamGroup.setName("Filter envelope");
  envAttack.set("attack", 10, 0, 1000);
  envAttack.enableSmoothing(50.f);
  envDecay.set("decay", 100, 0, 1000);
  envDecay.enableSmoothing(50.f);
  envSustain.set("sustain", 0.6f, 0.0f, 1.0f);
  envSustain.enableSmoothing(50.f);
  envRelease.set("release", 1000, 0, 5000);
  envRelease.enableSmoothing(50.f);
  filterADSRParamGroup.add(static_cast<ofAbstractParameter&>(envAttack.getOFParameterInt()));
  filterADSRParamGroup.add(static_cast<ofAbstractParameter&>(envDecay.getOFParameterInt()));
  filterADSRParamGroup.add(static_cast<ofAbstractParameter&>(envSustain.getOFParameterFloat()));
  filterADSRParamGroup.add(static_cast<ofAbstractParameter&>(envRelease.getOFParameterInt()));

  globalParamGroup.setName("Synth");
  globalParamGroup.add(static_cast<ofAbstractParameter&>(mainOutParamGroup));
  globalParamGroup.add(static_cast<ofAbstractParameter&>(ADSRParamGroup));
  globalParamGroup.add(static_cast<ofAbstractParameter&>(filterParamGroup));
  globalParamGroup.add(static_cast<ofAbstractParameter&>(filterADSRParamGroup));

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

  ofxImGui::AddGroup(globalParamGroup, mainSettings, false);

  /*ofxImGui::AddGroup(mainOutParamGroup, mainSettings);
  ofxImGui::AddGroup(ADSRParamGroup, mainSettings);
  ofxImGui::AddGroup(filterParamGroup, mainSettings);*/

  /*if (ofxImGui::BeginWindow("-O Main O-", mainSettings, false))
  {
    ofxImGui::AddParameter(gain.getOFParameterInt());
    ofxImGui::AddParameter(attack.getOFParameterInt());
    ofxImGui::AddParameter(decay.getOFParameterInt());
    ofxImGui::AddParameter(sustain.getOFParameterFloat());
    ofxImGui::AddParameter(release.getOFParameterInt());
  }
  ofxImGui::EndWindow(mainSettings);*/

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
