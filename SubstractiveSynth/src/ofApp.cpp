#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  gui.setup();

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

  //paramsUI.setPatchParams(synthParams);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  draw_ui();
}

void ofApp::draw_ui()
{
  gui.begin();

  //paramsUI.Draw();

  auto mainSettings = ofxImGui::Settings();
  for (auto lw : paramsLayout.Windows())
  {
    ofxImGui::BeginWindow(lw->mName, mainSettings, false);

    for (auto param : lw->params)
    {
      draw_ui_param(param);
    }

    for (auto group : lw->subGroup)
    {
      draw_ui_group(group);

    }

    ofxImGui::EndWindow(mainSettings);
  }

  gui.end();
}

void ofApp::draw_ui_param(shared_ptr<LayoutParam> param )
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
  default:
    ofLogWarning() << "ofApp::draw_ui_param - Unkown widget type " << static_cast<int>(param->widgetType);
  }
}


void ofApp::draw_ui_group(shared_ptr<LayoutGroup> group)
{
  if (ImGui::CollapsingHeader(group->mName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    for (auto param : group->params)
    {
      draw_ui_param(param);
    }

    for (auto subGroup : group->subGroup)
    {
      draw_ui_group(subGroup);
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
