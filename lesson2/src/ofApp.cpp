#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetWindowShape(640, 360); // we don't need fancy graphics at the moment

  //--------PATCHING-------
  gate.out_trig() >> env.set(0.0f, 70.0f, 0.1f, 700.0f);
  env * 0.5f >> amp.in_mod();
  noise >> amp >> engine.audio_out(0);
  amp >> engine.audio_out(1);

  //------------SETUPS AND START AUDIO-------------
  engine.listDevices();
  engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup(44100, 512, 3);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
  float trig = ofMap(y, 0, ofGetHeight(), 1.0f, 0.0f);
  gate.trigger(trig);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  gate.off();
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
