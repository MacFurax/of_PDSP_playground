#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();

  pp.AddParam("OSC1.level", 0.5f, 0.f, 1.f);
  pp.AddParam("OSC1.waveForm", 0, { "sine", "triangle", "saw", "pulse", "noise" });
  pp.AddParam("OSC1.detune", 0.0f, -12.f, 12.f);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  gui.begin();

  auto mainSettings = ofxImGui::Settings();

  for (auto child : pp.childsGroups)
  {
    ofxImGui::BeginWindow(child->getName(), mainSettings, false);
    for (int x = 0; x < child->size() ; x++)
    {
      ofAbstractParameter& param = child->get(x);
      ImGui::Text(param.getName().c_str());
    }
    ofxImGui::EndWindow(mainSettings);
  }

  

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
