#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	gui.setup(); 
	setupParamsLayout();

	int polyphonyVoiceCount = 8;
	int unisonVoiceCount = 1;

	synth.setVoiceCount(polyphonyVoiceCount);

	midiKeys.setPolyMode(polyphonyVoiceCount, unisonVoiceCount);
	
	int voiceIndex = 0;
	for (auto& voice : synth.getVoices())
	{
		midiKeys.out_trig(voiceIndex) >> voice.in("trigger");
		midiKeys.out_pitch(voiceIndex) >> voice.in("pitch");

		synthParams.Patch("OSC1.Level") >> voice.in("level");

		synthParams.Patch("OSC1.PW") >> voice.in("pulseWidth");

		synthParams.Patch("OSC1.Detune") >> voice.osc1coarseDetune;
		synthParams.Patch("OSC1.Fine") >> voice.osc1FineDetune;

		synthParams.Patch("OSC1.Sine") >> voice.osc1SineLevel.in_mod();
		synthParams.Patch("OSC1.Triangle") >> voice.osc1TriangleLevel.in_mod();
		synthParams.Patch("OSC1.Pulse") >> voice.osc1PulseLevel.in_mod();
		synthParams.Patch("OSC1.Saw") >> voice.osc1SawLevel.in_mod();
		synthParams.Patch("OSC1.Noise") >> voice.osc1NoiseLevel.in_mod();

		synthParams.Patch("OSC1.A") >> voice.osc1ADSR.in_attack();
		synthParams.Patch("OSC1.D") >> voice.osc1ADSR.in_decay();
		synthParams.Patch("OSC1.S") >> voice.osc1ADSR.in_sustain();
		synthParams.Patch("OSC1.R") >> voice.osc1ADSR.in_release();

		synthParams.Patch("OSC1.LFO Freq") >> voice.osc1LFO.in_freq();

		synthParams.Patch("OSC1.LFO Sine") >> voice.osc1LFOSineLevel.in_mod();
		synthParams.Patch("OSC1.LFO Triangle") >> voice.osc1LFOTriangleLevel.in_mod();
		synthParams.Patch("OSC1.LFO Saw") >> voice.osc1LFOSawLevel.in_mod();
		synthParams.Patch("OSC1.LFO Square") >> voice.osc1LFOSquareLevel.in_mod();

		synthParams.Patch("OSC1.LFO PW") >> voice.osc1PWAmp.in_mod();
		synthParams.Patch("OSC1.LFO Pitch") >> voice.osc1PitchAmp.in_mod();
		synthParams.Patch("OSC1.LFO Level") >> voice.osc1LevelAmp.in_mod();



		voiceIndex++;
	}


	mainOutParams.Patch("MAIN.Level") >> synth.in("level");
	synthParams.Patch("SYNTH.Filter Type") >> synth.filter.in_mode();
	synthParams.Patch("SYNTH.Filter Cutoff") >> synth.filter.in_cutoff();
	synthParams.Patch("SYNTH.Filter Reso") >> synth.filter.in_reso();


	synth.patchVoicesToSynth();

	synth >> engine.audio_out(0);
	synth >> engine.audio_out(1);

	midiIn.listPorts();
	midiIn.openPort(0); //set the right port !!!


  // for our midi controllers to work we have to add them to the engine, so it know it has to process them
	engine.addMidiController(midiKeys, midiIn); // add midi processing to the engine
	engine.addMidiController(midiCCs, midiIn);  // add midi processing to the engine
	engine.listDevices();
	engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
	engine.setup(44100, 512, 3);

	midiDevicesGUI.setPDSPMIDI(&midiIn);
	patchSaveLoadGUI.setPatchParams(&synthParams);

}

void ofApp::setupParamsLayout()
{

	mainOutParams.AddParam("MAIN.Level", 0.5f, 0.0f, 1.0f);

	paramsLayout.StartWindow("Main Out");

		shared_ptr<LayoutParam> param = paramsLayout.AddParam("level", mainOutParams.getParamDesc("MAIN.Level"));
		param->widgetType = LayoutParam::WidgetTypes::Knob;
	paramsLayout.EndWindow();

	paramsLayout.StartWindow("Synth :: Filter");

		param = paramsLayout.AddParam("cutoff", synthParams.getParamDesc("SYNTH.Filter Type"));
		//param->widgetType = LayoutParam::WidgetTypes::Knob;

		param = paramsLayout.AddParam("cutoff", synthParams.getParamDesc("SYNTH.Filter Cutoff"));
		param->widgetType = LayoutParam::WidgetTypes::Knob;

		param = paramsLayout.AddParam("reso", synthParams.getParamDesc("SYNTH.Filter Reso"));
		param->widgetType = LayoutParam::WidgetTypes::Knob;
		param->paramLayout = LayoutParam::ParamLayouts::SameLine;

	paramsLayout.EndWindow();

	paramsLayout.StartWindow("Voice 1 :: OSC + LFO");

		paramsLayout.StartGroup("OSC");

			param = paramsLayout.AddParam("level", synthParams.getParamDesc("OSC1.Level"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;

			param = paramsLayout.AddParam("detune", synthParams.getParamDesc("OSC1.Detune"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("fine", synthParams.getParamDesc("OSC1.Fine"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("pw", synthParams.getParamDesc("OSC1.PW"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;


			param = paramsLayout.AddParam("sine", synthParams.getParamDesc("OSC1.Sine"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;

			param = paramsLayout.AddParam("triangle", synthParams.getParamDesc("OSC1.Triangle"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("saw", synthParams.getParamDesc("OSC1.Saw"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("pulse", synthParams.getParamDesc("OSC1.Pulse"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("noise", synthParams.getParamDesc("OSC1.Noise"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

		paramsLayout.EndGroup();


		paramsLayout.StartGroup("ADSR");

			param = paramsLayout.AddParam("A", synthParams.getParamDesc("OSC1.A"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;

			param = paramsLayout.AddParam("D", synthParams.getParamDesc("OSC1.D"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("S", synthParams.getParamDesc("OSC1.S"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("R", synthParams.getParamDesc("OSC1.R"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;


		paramsLayout.EndGroup();

		paramsLayout.StartGroup("LFO");

			param = paramsLayout.AddParam("freq", synthParams.getParamDesc("OSC1.LFO Freq"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;

			param = paramsLayout.AddParam("pitch", synthParams.getParamDesc("OSC1.LFO Pitch"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("level", synthParams.getParamDesc("OSC1.LFO Level"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("pw", synthParams.getParamDesc("OSC1.LFO PW"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("sine", synthParams.getParamDesc("OSC1.LFO Sine"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;

			param = paramsLayout.AddParam("triangle", synthParams.getParamDesc("OSC1.LFO Triangle"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("saw", synthParams.getParamDesc("OSC1.LFO Saw"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

			param = paramsLayout.AddParam("square", synthParams.getParamDesc("OSC1.LFO Square"));
			param->widgetType = LayoutParam::WidgetTypes::Knob;
			param->paramLayout = LayoutParam::ParamLayouts::SameLine;

		paramsLayout.EndGroup();

	paramsLayout.EndWindow();
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

  auto mainSettings = ofxImGui::Settings();
  for (auto lw : paramsLayout.Windows())
  {
	ofxImGui::BeginWindow(lw->mName, mainSettings, false);

	for (auto param : lw->params)
	{
	  drawUIParam(param);
	}

	for (auto group : lw->subGroup)
	{
	  drawUIGroup(group);

	}

	ofxImGui::EndWindow(mainSettings);
  }

  midiDevicesGUI.draw();
  patchSaveLoadGUI.draw();

  gui.end();
}

void ofApp::drawUIParam(shared_ptr<LayoutParam> param )
{
  if (param->paramLayout == LayoutParam::ParamLayouts::SameLine)
  {
	ImGui::SameLine();
  }
  switch ( param->widgetType )
  {
  case LayoutParam::WidgetTypes::Knob:
	ofxImGui::AddKnob(param->mLabel, param->mParamDesc->pdspParameter->getOFParameterFloat());
	break;
  case LayoutParam::WidgetTypes::VFader:
	  ofxImGui::AddVSlider(param->mLabel, param->mParamDesc->pdspParameter->getOFParameterFloat(), ImVec2(50, 160));
	break;
  case LayoutParam::WidgetTypes::Combo:
	  ofxImGui::AddCombo(param->mLabel, 
			param->mParamDesc->pdspParameter->getOFParameterInt(), 
			param->mParamDesc->comboOptions
		  );
	  break;
  case LayoutParam::WidgetTypes::HFader:
	  ofxImGui::AddParameter(param->mLabel, param->mParamDesc->pdspParameter->getOFParameterFloat());
	  break;
  default:
	ofLogWarning() << "ofApp::draw_ui_param - Unkown widget type " << static_cast<int>(param->widgetType);
  }
}


void ofApp::drawUIGroup(shared_ptr<LayoutGroup> group)
{
  if (ImGui::CollapsingHeader(group->mName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
	for (auto param : group->params)
	{
	  drawUIParam(param);
	}

	for (auto subGroup : group->subGroup)
	{
	  drawUIGroup(subGroup);
	}
  }
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
