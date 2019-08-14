#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetWindowShape(640, 360); // we don't need fancy graphics at the moment

  //--------PATCHING-------
  // we will make our patching here

  amp.set(ampValue);

  basePitch >> osc1;
  basePitch >> osc2;
  osc1 >> amp >> engine.audio_out(0);
  osc1 >> amp >> engine.audio_out(1);
  osc2.out_pulse() >> amp >> engine.audio_out(0);
  osc2.out_pulse() >> amp >> engine.audio_out(1);

  

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

  if (key == '+')
  {
    ampValue += ampInc;
    ampValue >> amp.in_mod();

  }
  else if( key == '-')
  {
    ampValue -= ampInc;
    ampValue >> amp.in_mod();
  }

  if (key == '8')
  {
    detuneLevel += 0.001f;
    float newPitch = basePitch + detuneLevel;
    newPitch >> osc2;
  }
  else if (key == '2')
  {
    detuneLevel -= 0.001f;
    float newPitch = basePitch + detuneLevel;
    newPitch >> osc2;
  }
  
  

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

void ofApp::exit()
{
  engine.stop();
}
