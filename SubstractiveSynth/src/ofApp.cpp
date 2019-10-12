#include "ofApp.h"
#include "CorporateGreyTheme.h"
#include "CorporateOrangeTheme.h"
#include "FlatDryWineGreenTheme.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowShape(1800, 1000);
	ofSetWindowTitle("Substractive Synth");
	ofSetBackgroundColor(58);

	gui.enableDocking();
	gui.setup( new ofxImGui::CorporateOrangeTheme());
	//gui.setup(new ofxImGui::FlatDryWineGreenTheme());

	setPatchParams();

	int polyphonyVoiceCount = 8;
	int unisonVoiceCount = 1;

	midiKeys.setPolyMode(polyphonyVoiceCount, unisonVoiceCount);

	synth.setup(polyphonyVoiceCount*unisonVoiceCount);

	int voiceIndex = 0;
	for (auto voice : synth.getVoices())
	{
		midiKeys.out_trig(voiceIndex) >> voice->in_trig();
		midiKeys.out_pitch(voiceIndex) >> voice->in_pitch();

		1.0f >> voice->in("level"); // level of the voice
		// each voice element can have there own level
		// TODO FIX voice are setup in reverse order
		VoiceElement * ve = voice->getVoiceElementAt(0);

		pp.patch("voice02.osc.level") >> ve->in("level");
		pp.patch("voice02.osc.detune") >> ve->in("detune");
		pp.patch("voice02.osc.fine") >> ve->in("fine");
		pp.patch("voice02.osc.pw") >> ve->in("pulseWidth");

		pp.patch("voice02.adsr.a") >> ve->in("attack");
		pp.patch("voice02.adsr.d") >> ve->in("decay");
		pp.patch("voice02.adsr.s") >> ve->in("sustain");
		pp.patch("voice02.adsr.r") >> ve->in("release");

		pp.patch("voice02.osc.sine") >> ve->in("sineLevel");
		pp.patch("voice02.osc.triangle") >> ve->in("triangleLevel");
		pp.patch("voice02.osc.saw") >> ve->in("sawLevel");
		pp.patch("voice02.osc.pulse") >> ve->in("pulseLevel");
		pp.patch("voice02.osc.noise") >> ve->in("noiseLevel");


		pp.patch("voice02.filter.cutoff") >> ve->in("filter.cutoff");
		pp.patch("voice02.filter.reso") >> ve->in("filter.reso");
		pp.patch("voice02.filter.type") >> ve->in("filter.type");

		pp.patch("voice02.env adsr.a") >> ve->in("filter.attack");
		pp.patch("voice02.env adsr.d") >> ve->in("filter.decay");
		pp.patch("voice02.env adsr.s") >> ve->in("filter.sustain");
		pp.patch("voice02.env adsr.r") >> ve->in("filter.release");
		
		pp.patch("voice02.env adsr.cutoff") >> ve->in("filter.adsr.toCutOff");
		pp.patch("voice02.env adsr.pw") >> ve->in("filter.adsr.toPw");
		
		pp.patch("voice02.env adsr.sine") >> ve->in("filter.adsr.toSine");
		pp.patch("voice02.env adsr.triangle") >> ve->in("filter.adsr.toTriangle");
		pp.patch("voice02.env adsr.saw") >> ve->in("filter.adsr.toSaw");
		pp.patch("voice02.env adsr.pulse") >> ve->in("filter.adsr.toPulse");

		ve = voice->getVoiceElementAt(1);

		pp.patch("voice01.osc.level") >> ve->in("level");
		pp.patch("voice01.osc.detune") >> ve->in("detune");
		pp.patch("voice01.osc.fine") >> ve->in("fine");
		pp.patch("voice01.osc.pw") >> ve->in("pulseWidth");

		pp.patch("voice01.osc.sine") >> ve->in("sineLevel");
		pp.patch("voice01.osc.triangle") >> ve->in("triangleLevel");
		pp.patch("voice01.osc.saw") >> ve->in("sawLevel");
		pp.patch("voice01.osc.pulse") >> ve->in("pulseLevel");
		pp.patch("voice01.osc.noise") >> ve->in("noiseLevel");

		pp.patch("voice01.adsr.a") >> ve->in("attack");
		pp.patch("voice01.adsr.d") >> ve->in("decay");
		pp.patch("voice01.adsr.s") >> ve->in("sustain");
		pp.patch("voice01.adsr.r") >> ve->in("release");

		pp.patch("voice01.filter.type") >> ve->in("filter.type");
		pp.patch("voice01.filter.cutoff") >> ve->in("filter.cutoff");
		pp.patch("voice01.filter.reso") >> ve->in("filter.reso");

		pp.patch("voice01.lfo.freq") >> ve->in("lfo.freq");
		pp.patch("voice01.lfo.sine") >> ve->in("lfo.sine");
		pp.patch("voice01.lfo.triangle") >> ve->in("lfo.triangle");
		pp.patch("voice01.lfo.saw") >> ve->in("lfo.saw");
		pp.patch("voice01.lfo.square") >> ve->in("lfo.square");
			   
		pp.patch("voice01.lfo.pitch") >> ve->in("lfo.toPitch");
		pp.patch("voice01.lfo.level") >> ve->in("lfo.toLevel");
		pp.patch("voice01.lfo.pw") >> ve->in("lfo.toPw");
		pp.patch("voice01.lfo.cutoff") >> ve->in("lfo.toCutOff");

		pp.patch("voice01.lfo.toSine") >> ve->in("lfo.toSine");
		pp.patch("voice01.lfo.toTriangle") >> ve->in("lfo.toTriangle");
		pp.patch("voice01.lfo.toSaw") >> ve->in("lfo.toSaw");
		pp.patch("voice01.lfo.toPulse") >> ve->in("lfo.toPulse");
		pp.patch("voice01.lfo.toNoise") >> ve->in("lfo.toNoise");

		voiceIndex++;
	}
	

	pp.patch("synth.level") >> synth.in("level");
	pp.patch("synth.filter.type") >> synth.in("filter.type");
	pp.patch("synth.filter.cutoff") >> synth.in("filter.cutoff");
	pp.patch("synth.filter.reso") >> synth.in("filter.reso");

	pp.patch("synth.filter.lfo.type") >> synth.in("filter.lfo.type");
	pp.patch("synth.filter.lfo.freq") >> synth.in("filter.lfo.freq");
	pp.patch("synth.filter.lfo.cutoff") >> synth.in("filter.lfo.cutoff");

	pp.patch("synth.modulation.lfo freq") >> synth.in("filter.modulation.lfo freq");
	pp.patch("synth.modulation.reso") >> synth.in("filter.modulation.reso");
	pp.patch("synth.modulation.cutoff") >> synth.in("filter.modulation.cutoff");

	// patch CC modulation 
	midiCCs.out(1) >> synth.in_modulation();

	pp.patch("synth.compressor.threshold") >> compressor.in_threshold();
	pp.patch("synth.compressor.ratio") >> compressor.in_ratio();
	pp.patch("synth.compressor.attack") >> compressor.in_attack();
	pp.patch("synth.compressor.release") >> compressor.in_release();
	pp.patch("synth.compressor.knee") >> compressor.in_knee();


	pp.patch("FX.delay.level") >> delayLevel.in_mod();
	pp.patch("FX.delay.time") >> delay.in_time();
	pp.patch("FX.delay.feedback") >> delay.in_feedback();
	pp.patch("FX.delay.damping") >> delay.in_damping();

	// * 0.3f is to avoid going over 1 when signal is summed
	// 0.3 is 1/3 because 3 signals are summed

	synth >> compressor >> delay >> delayLevel * 0.3f >> engine.audio_out(0);
								    delayLevel * 0.3f >> engine.audio_out(1);

	pp.patch("FX.chorus.level") >> chorusLevel.in_mod();
	pp.patch("FX.chorus.speed") >> chorus.in_speed();
	pp.patch("FX.chorus.depth") >> chorus.in_depth();
	pp.patch("FX.chorus.delay") >> chorus.in_delay();

	synth >> compressor >> chorus >> chorusLevel * 0.3f >> engine.audio_out(0);
							         chorusLevel * 0.3f >> engine.audio_out(1);

	synth >> compressor * 0.3f >> engine.audio_out(0);
	synth >> compressor * 0.3f >> engine.audio_out(1);


	midiIn.openPort(0); 

	midiKeys.setPitchBend(-12.f, 12.f);
	
	// for our midi controllers to work we have to add them to the engine, so it know it has to process them
	engine.addMidiController(midiKeys, midiIn); // add midi processing to the engine
	engine.addMidiController(midiCCs, midiIn);  // add midi processing to the engine
	//engine.setApi(ofSoundDevice::MS_DS);
	engine.listDevices();
	engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
	engine.setup(48000, 512, 3);

	midiDeviceUI.setPDSPMIDI(&midiIn);
	patchParamUI.setPatchParams(pp);
	patchSaveLoadUI.setPatchParams(&pp);

}

void ofApp::setPatchParams()
{
	pp.AddParam("synth.level", 0.5f, 0.0f, 1.0f);
	pp.AddParam("synth.filter.type", 0, { "LowPass", "BandPass", "HighPass", "Notch" });
	pp.AddParam("synth.filter.cutoff", 180.0f, 0.0f, 180.0f);
	pp.AddParam("synth.filter.reso", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("synth.filter.lfo.type", 0, { "Sine", "Triangle", "Saw", "Square" });
	pp.AddParam("synth.filter.lfo.freq", 1.0f, 0.0f, 20.0f);
	pp.AddParam("synth.filter.lfo.cutoff", 0.0f, 0.0f, 80.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("synth.modulation.lfo freq", 0.0f, 0.0f, 40.0f);
	pp.AddParam("synth.modulation.cutoff", 0.0f, 0.0f, 90.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("synth.modulation.reso", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("synth.compressor.threshold", -20.0f, -120.0f, 0.0f);
	pp.AddParam("synth.compressor.ratio", 4.0f, 0.0f, 100.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("synth.compressor.attack", 10.0f, 0.0f, 300.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("synth.compressor.release", 50.0f, 0.0f, 300.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("synth.compressor.knee", 0.0f, 0.0f, 20.0f, 50.0f, ParamLayouts::SameLine);
	// TODO add a gain

	pp.AddParam("FX.delay.level", 0.0f, 0.0f, 1.0f);
	pp.AddParam("FX.delay.time", 300.0f, 0.0f, 500.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("FX.delay.feedback", 0.2f, 0.0f, 0.99f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("FX.delay.damping", 0.2f, 0.f, 0.99f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("FX.chorus.level", 0.0f, 0.0f, 1.0f);
	pp.AddParam("FX.chorus.speed", 0.25f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("FX.chorus.depth", 10.0f, 0.0f, 100.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("FX.chorus.delay", 80.0f, 0.0f, 200.0f, 50.0f, ParamLayouts::SameLine);

	// Voice 1 with 
	// one osc with detune, ADSR and filter
	// LFO patchable to level, pitch , pulse width and cutoff

	pp.AddParam("voice01.osc.level", 0.80f, 0.0f, 1.0f);
	pp.AddParam("voice01.osc.detune", 0.0f, -12.0f, 12.0f, 0.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.fine", 0.0f, -1.0f, 1.0f, 0.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.osc.pw", 0.5f, 0.1f, 0.9f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.osc.sine", 0.4f, 0.0f, 1.0f);
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

	pp.AddParam("voice01.lfo.sine", 1.0f, 0.0f, 1.0f);
	pp.AddParam("voice01.lfo.triangle", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.saw", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.square", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.lfo.freq", 1.0f, 0.0f, 30.0f);
	pp.AddParam("voice01.lfo.pitch", 0.0f, 0.0f, 40.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.level", 0.0f, 0.0f, 0.5f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.pw", 0.0f, 0.0f, 0.4f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.cutoff", 0.0f, 0.0f, 40.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice01.lfo.toSine", 0.0f, 0.0f, 40.0f);
	pp.AddParam("voice01.lfo.toTriangle", 0.0f, 0.0f, 0.5f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.toSaw", 0.0f, 0.0f, 0.4f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.toPulse", 0.0f, 0.0f, 40.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice01.lfo.toNoise", 0.0f, 0.0f, 40.0f, 50.0f, ParamLayouts::SameLine);


	// Voice 2 with 
	// one osc with detune and ADSR
	// filter with adsr patch to filter.cutoff
	pp.AddParam("voice02.osc.level", 0.80f, 0.0f, 1.0f);
	pp.AddParam("voice02.osc.detune", 0.0f, -12.0f, 12.0f, 0.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.fine", 0.0f, -1.0f, 1.0f, 0.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.pw", 0.5f, 0.1f, 0.9f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice02.osc.sine", 0.4f, 0.0f, 1.0f);
	pp.AddParam("voice02.osc.triangle", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.saw", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.osc.pulse", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
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
	pp.AddParam("voice02.env adsr.cutoff", 0.0f, 0.0f, 60.0f);
	pp.AddParam("voice02.env adsr.pw", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);

	pp.AddParam("voice02.env adsr.sine", 0.0f, 0.0f, 1.0f);
	pp.AddParam("voice02.env adsr.triangle", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.env adsr.saw", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
	pp.AddParam("voice02.env adsr.pulse", 0.0f, 0.0f, 1.0f, 50.0f, ParamLayouts::SameLine);
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
