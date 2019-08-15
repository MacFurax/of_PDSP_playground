#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "helpers/ImGuiHelpers.h"
#include "ofxPDSP.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void setupImGui();
    void update();
    void draw();

    void ui_Draw();
    void ui_Menu();
    void ui_OSCWindow();
    void ui_EnvelopeWindow();
    void ui_OutputWindow();
    void ui_FiltersWindow();
    void ui_AudioSettings();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    // ofxImGui
    ofxImGui::Gui gui;
    bool ui_show_audio_settings = false;
    float attackValue = 0.0f;
    float decayValue = 300.0f;

    std::vector<std::string> wavesForms = {"sine", "triangle", "saw", "pulse"};
    const int pulse_wave_idx = 3;
    int ui_selected_wave_forms = 0;
    int ui_selected_wave_forms_previous = 0;
    float ui_osc_fine_detune = 0.0f;
    float ui_osc_detune = 0.0f;
    float ui_osc_pulse_width = 0.5f;
    float ui_gain = -23.0f;

    //ofx PDSP
    pdsp::Engine engine;
    pdsp::VAOscillator osc;
    pdsp::Switch oscWaveFormSwitch;
    pdsp::DBtoLin dBToLin;
    pdsp::Amp mainOut;

    pdsp::ValueControl pulseWidthCtrl;
    pdsp::ValueControl gainCtrl;

    
};
