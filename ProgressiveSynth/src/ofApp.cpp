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
  ui_Draw();
}

void ofApp::ui_Draw()
{
  gui.begin();
  ofxImGuiStartDocking();

  ui_Menu();

  ui_OSCWindow();
  ui_EnvelopeWindow();
  ui_FiltersWindow();

  if (ui_show_audio_settings) ui_AudioSettings();

  ofxImGuiEndDocking();
  gui.end();
}

void ofApp::ui_Menu()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit", "ALT+F4")) 
      {
        ofExit();
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Settings"))
    {
      ImGui::MenuItem("Audio & MIDI", "", &ui_show_audio_settings);
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

void ofApp::ui_OSCWindow()
{
  ImGui::Begin("OSCs");
    ImGui::Text("OSC 1");
    ImGui::Combo("Wave form", &ui_selected_wave_forms, wavesForms);

    MyKnob("Tune", &ui_osc_detune, -10.0, 10.0);
    ImGui::SameLine();
    MyKnob("Fine", &ui_osc_fine_detune, -0.5, 0.5);
        
    if (ui_selected_wave_forms == 2) // pulse wave forms
    {
      ImGui::SameLine();
      MyKnob("Pulse Width", &ui_osc_pulse_width, 0.0f, 1.0f);
    }
  
  ImGui::End();
}

void ofApp::ui_EnvelopeWindow()
{
  ImGui::Begin("Envelopes");

  ImGui::End();
}

void ofApp::ui_FiltersWindow()
{
  ImGui::Begin("Filters");

  ImGui::End();
}

void ofApp::ui_AudioSettings()
{
  ImGui::Begin("Audio Settings", &ui_show_audio_settings);

  ImGui::End();
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
