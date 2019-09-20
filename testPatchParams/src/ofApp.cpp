#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowShape(1600, 800);

	gui.setup();

	pp.AddParam("synth.level", 0.5f, 0.0f, 1.0f);
	pp.AddParam("synth.filter.type", 0, {"LowPass", "BandPass", "HighPass", "Notch"});
	pp.AddParam("synth.filter.cutoff", 180.0f, 0.0f, 180.0f);
	pp.AddParam("synth.filter.reso", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("synth.filter.lfo.type", 0, {"Sine", "Triangle", "Saw", "Square"});
	pp.AddParam("synth.filter.lfo.freq", 1.0f, 0.0f, 20.0f);
	pp.AddParam("synth.filter.lfo.cutoff", 0.0f, 0.0f, 80.0f, 50.0f, ParamLayouts::SameLine);

	
	pp.AddParam("voice01.osc.level", 0.5f, 0.0f, 1.0f);
	pp.AddParam("voice01.osc.detune", 0.0f, -12.0f, 12.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.fine", 0.0f, -1.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.pw", 0.5f, 0.1f, 0.9f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.osc.sine", 1.0f, 0.0f, 1.0f);
	pp.AddParam("voice01.osc.triangle", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.saw", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.pulse", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.noise", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	
	pp.AddParam("voice01.adsr.a", 10.0f, 0.0f, 3000.0f);
	pp.AddParam("voice01.adsr.d", 300.0f, 0.0f, 3000.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.adsr.s", 0.5f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.adsr.r", 300.0f, 0.0f, 3000.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.filter.type", 0, { "LowPass", "BandPass", "HighPass", "Notch" });
	pp.AddParam("voice01.filter.cutoff", 180.0f, 0.0f, 180.0f);
	pp.AddParam("voice01.filter.reso", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.lfo.freq", 1.0f, 0.0f, 30.0f);
	pp.AddParam("voice01.lfo.pitch", 0.0f, 0.0f, 40.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.level", 0.0f, 0.0f, 0.5f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.pw", 0.0f, 0.0f, 0.4f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.cutoff", 0.0f, 0.0f, 40.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.lfo.sine", 1.0f, 0.0f, 1.0f);
	pp.AddParam("voice01.lfo.triangle", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.saw", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.square", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	



	pp.AddParam("voice02.osc.level", 0.5f, 0.0f, 1.0f);
	pp.AddParam("voice02.osc.detune", 0.0f, -12.0f, 12.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.fine", 0.0f, -1.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.pw", 0.5f, 0.1f, 0.9f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice02.osc.sine", 1.0f, 0.0f, 1.0f);
	pp.AddParam("voice02.osc.triangle", 0.0f, 0.0f, 1.0f,  50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.saw", 0.0f, 0.0f, 1.0f,  50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.pulse", 0.0f, 0.0f, 1.0f,  50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.noise", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	

	pp.AddParam("voice02.adsr.a", 10.0f, 0.0f, 3000.0f);
	pp.AddParam("voice02.adsr.d", 300.0f, 0.0f, 3000.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.adsr.s", 0.5f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.adsr.r", 300.0f, 0.0f, 3000.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice02.filter.type", 0, { "LowPass", "BandPass", "HighPass", "Notch" });
	pp.AddParam("voice02.filter.cutoff", 180.0f, 0.0f, 180.0f);
	pp.AddParam("voice02.filter.reso", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice02.env adsr.a", 10.0f, 0.0f, 3000.0f);
	pp.AddParam("voice02.env adsr.d", 300.0f, 0.0f, 3000.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.env adsr.s", 0.5f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.env adsr.r", 300.0f, 0.0f, 3000.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.env adsr.cutoff", 0.0f, 0.0f, 40.0f);
	pp.AddParam("voice02.env adsr.pw", 0.0f, 0.0f, 0.4f, 50.0f, ParamLayouts::SameLine);


	int polyphonyVoiceCount = 8;
	int unisonVoiceCount = 1;

	midiKeys.setPolyMode(polyphonyVoiceCount, unisonVoiceCount);

	midiIn.openPort(0); 
	// for our midi controllers to work we have to add them to the engine, so it know it has to process them
	engine.addMidiController(midiKeys, midiIn); // add midi processing to the engine
	engine.addMidiController(midiCCs, midiIn);  // add midi processing to the engine
	engine.listDevices();
	engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
	engine.setup(44100, 512, 3);

	midiDeviceUI.setPDSPMIDI(&midiIn);
	patchParamUI.setPatchParams(pp);
	patchSaveLoadUI.setPatchParams(&pp);


	//patchStore.save("toto", *(pp.getOfParameterGroup()));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  

	drawUI();
}

void ofApp::drawUI()
{
	gui.begin();

	patchParamUI.draw();
	midiDeviceUI.draw();
	patchSaveLoadUI.draw();

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
