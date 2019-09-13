#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();

  patchStore.setup("./patches/", "xml");
  patchStore.reloadPatchsFileList();

  selectedPatch.set("Patchs", 0, 0, patchStore.numFiles());
    
  //
  // PDSP setup
  //
  pp.AddParam("OSC1.waveForm", 0, { "sine", "triangle", "saw", "pulse" });
  pp.AddParam("OSC1.pitch", 68.0f, 12.f, 180.f);
  pp.AddParam("OSC1.level", 0.5f, 0.f, 1.f, 50.f, ParamDesc::Layouts::SameLine);
  pp.AddParam("OSC1.pw", 0.7f, 0.5f, 0.9f, 50.f, ParamDesc::Layouts::SameLine);
  
  pp.AddParam("OSC1.LFO wf", 0, { "sine", "triangle", "saw", "square" });
  pp.AddParam("OSC1.LFO freq", 1.0f, 0.f, 20.f);
  pp.AddParam("OSC1.LFO pitch", 0.0f, 0.0f, 90.f, 50.f, ParamDesc::Layouts::SameLine);
  
  pp.AddParam("OSC1.LFO2 wf", 0, { "sine", "triangle", "saw", "square" });
  pp.AddParam("OSC1.LFO2 freq", 1.0f, 0.f, 20.f);
  pp.AddParam("OSC1.LFO2 pw", 0.0f, 0.f, 1.f, 50.f, ParamDesc::Layouts::SameLine);
  
  ppDrawer.setPatchParams(pp);

  // OSC 1

  waveForms.resize(4);
  osc.out_sine() >> waveForms.input(0);
  osc.out_triangle() >> waveForms.input(1);
  osc.out_saw() >> waveForms.input(2);
  osc.out_pulse() >> waveForms.input(3);
  
  waveForms >> oscLevel;
  
  pp.Patch("OSC1.pitch") >> osc.in_pitch();
  pp.Patch("OSC1.pw") >> osc.in_pw();
  pp.Patch("OSC1.waveForm") >> waveForms.in_select();
  pp.Patch("OSC1.level") >> oscLevel.in_mod();
  
  // LFO 1
  pp.Patch("OSC1.LFO freq") >> lfo.in_freq();

  lfoWaveForms.resize(4);
  lfo.out_sine() >> lfoWaveForms.input(0);
  lfo.out_triangle() >> lfoWaveForms.input(1);
  lfo.out_saw() >> lfoWaveForms.input(2);
  lfo.out_square() >> lfoWaveForms.input(3);

  pp.Patch("OSC1.LFO wf") >> lfoWaveForms.in_select();

  lfoWaveForms >> lfoLevelToPitch;
  pp.Patch("OSC1.LFO pitch") >> lfoLevelToPitch.in_mod();

  lfoLevelToPitch >> osc.in_pitch();

  // LFO 2
  pp.Patch("OSC1.LFO2 freq") >> lfo2.in_freq();

  lfo2WaveForms.resize(4);
  lfo2.out_sine() >> lfo2WaveForms.input(0);
  lfo2.out_triangle() >> lfo2WaveForms.input(1);
  lfo2.out_saw() >> lfo2WaveForms.input(2);
  lfo2.out_square() >> lfo2WaveForms.input(3);

  pp.Patch("OSC1.LFO2 wf") >> lfo2WaveForms.in_select();
  
  lfo2WaveForms >> lfo2LevelToPW;

  pp.Patch("OSC1.LFO2 pw") >> lfo2LevelToPW.in_mod();


  lfo2LevelToPW >> osc.in_pw();
  
  oscLevel >> engine.audio_out(0);
  oscLevel >> engine.audio_out(1);

  midiIn.openPort(0); //set the right port !!!
  engine.addMidiController(midiCCs, midiIn);  // add midi processing to the engine

  engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup(44100, 512, 3);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  gui.begin();

  auto mainSettings = ofxImGui::Settings();

  ofxImGui::BeginWindow("Patchs", mainSettings, false);

  if (patchStore.numFiles() > 0)
  {
    if (ofxImGui::AddCombo(selectedPatch, patchStore.patcheNames()))
    {
      // patch selection changes, load the new patch
    }
  }
  else
  {
    ImGui::Text("No patches");
  }

  ImGui::SameLine();
  if (ImGui::Button("Reload"))
  {
    patchStore.reloadPatchsFileList();
    selectedPatch.setMax(patchStore.numFiles());
  }


  if (ImGui::Button("Load"))
  {
    if (patchStore.numFiles() > 0)
    {
      if (!patchStore.Load(selectedPatch.get(), pp.rootGroup))
      {
        // load failed
      }
    }
  }

  ofxImGui::AddParameter(pp.Name(), 256);
  ofxImGui::AddParameter(pp.Description(), 2048, true);

  if (ImGui::Button("Save"))
  {
    string fn = patchStore.buildFullFilename(pp.Name().get());
    //ofLogNotice() << "ofApp::draw - Save to " + fn + ".xml";
    if (!patchStore.Save(fn, pp.rootGroup))
    {
      // save failed
    }
  }
  ofxImGui::EndWindow(mainSettings);

  ppDrawer.Draw();
 
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
