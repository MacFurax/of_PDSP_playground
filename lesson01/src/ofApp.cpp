#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //--------PATCHING-------
  // we will make our patching here
  osc.out_sine() * 0.5f >> engine.audio_out(0);
  osc.out_sine() * 0.5f >> engine.audio_out(1);

  /*60.f >> osc.in_pitch();
  lfo.out_triangle() * 24.0f >> osc.in_pitch();*/

  60.f + lfo.out_triangle() * 24.0f >> osc.in_pitch();

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
  float pitch = ofMap(x, 0, ofGetWidth(), 48.0f, 72.0f);
  float lfoFreq = ofMap(y, 0, ofGetHeight(), 1.5f, 0.25f);
  pitch >> osc.in_pitch();
  lfoFreq >> lfo.in_freq();
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
