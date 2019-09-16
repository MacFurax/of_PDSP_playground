#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	gui.setup(); 
	setupParamsLayout();

	int polyphonyVoiceCount = 1;
	int unisonVoiceCount = 1;

	synth.setVoiceCount(polyphonyVoiceCount);

	midiKeys.setPolyMode(polyphonyVoiceCount, unisonVoiceCount);

	/*int voiceIndex = 0;
	for (auto& voice : synth.getVoices())
	{
		midiKeys.out_trig(voiceIndex) >> voice.in("trigger");
		midiKeys.out_pitch(voiceIndex) >> voice.in("pitch");
		synthParams.Patch("OSC1.Level") >> voice.in("level");
		synthParams.Patch("OSC1.PW") >> voice.in("pulseWidth");
		synthParams.Patch("OSC1.Sine") >> voice.osc1SineLevel;
		synthParams.Patch("OSC1.Triangle") >> voice.osc1TriangleLevel;
		synthParams.Patch("OSC1.Pulse") >> voice.osc1PulseLevel;
		synthParams.Patch("OSC1.Saw") >> voice.osc1SawLevel;
		synthParams.Patch("OSC1.Noise") >> voice.osc1NoiseLevel;

		synthParams.Patch("OSC1.A") >> voice.osc1ADSR.in_attack();
		synthParams.Patch("OSC1.D") >> voice.osc1ADSR.in_decay();
		synthParams.Patch("OSC1.S") >> voice.osc1ADSR.in_sustain();
		synthParams.Patch("OSC1.R") >> voice.osc1ADSR.in_release();

		voiceIndex++;
	}*/

	midiKeys.out_trig(0) >> synth.adsr.in_trig();
	midiKeys.out_pitch(0) >> synth.osc.in_pitch();

	synthParams.Patch("OSC1.A") >> synth.adsr.in_attack();
	synthParams.Patch("OSC1.D") >> synth.adsr.in_decay();
	synthParams.Patch("OSC1.S") >> synth.adsr.in_sustain();
	synthParams.Patch("OSC1.R") >> synth.adsr.in_release();

	synth.patchVoicesToSynth();

	0.5f >> synth.in("level");

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

}

void ofApp::setupParamsLayout()
{
	paramsLayout.StartWindow("OSC 1");

	paramsLayout.StartGroup("OSC");

	shared_ptr<LayoutParam> param = paramsLayout.AddParam("level", synthParams.getParamDesc("OSC1.Level"));
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
