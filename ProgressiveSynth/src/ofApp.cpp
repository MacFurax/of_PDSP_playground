#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetEscapeQuitsApp(false);

  // ofLog will write in a log file, it will be created in data folder
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofLogToFile("app.log");

  ofSetWindowTitle("Progressive Soft Synthetizer");

  setupImGui();
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
  drawImGui();
}

void ofApp::drawImGui()
{
  gui.begin();
  ofxImGuiStartDocking();

  ImGui::Begin("Knobs");
    MyKnob("Attack", &attackValue, 0.0f, 5000.0f, 0);
    ImGui::SameLine();
    MyKnob("Decay", &decayValue, 0.0f, 2000.0f, 0);
    ImGui::Button("TOTO");
  ImGui::End();

  ofxImGuiEndDocking();
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
