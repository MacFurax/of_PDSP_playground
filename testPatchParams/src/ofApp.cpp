#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	pp.AddParam("synth.level", 0.5f, 0.0f, 1.0f);
	pp.AddParam("synth.filter.cutoff", 180.0f, 0.0f, 180.0f);
	pp.AddParam("synth.filter.reso", 0.0f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.level", 0.5f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.sine", 1.0f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.triangle", 0.0f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.saw", 0.0f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.pulse", 0.0f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.noise", 0.0f, 0.0f, 1.0f);
	pp.AddParam("synth.voice.OSC1.pw", 0.0f, 0.0f, 1.0f);

	ofxXmlSettings tmpxmlset;
	ofSerialize(tmpxmlset, *(pp.getOfParameterGroup()));
	tmpxmlset.saveFile("toto.xml");
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
