#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "helpers/ImGuiHelpers.h"
#include "ofxPDSP.h"
#include "Synths/SynthDeuxOscillateurs.h"


class Voice
{
public:
  Voice()
  {}
  Voice(const Voice & other)
  {
    cout << "Voice copy constructor \n";
  }
  Voice& operator=(const Voice & other)
  {
    cout << "Voice move cnstructor \n";
    return *this;
  }

  pdsp::VAOscillator osc;
  pdsp::Amp          amp;
  pdsp::ADSR         envelopes;
  pdsp::Switch       waveFormSwitch;

};


class ofApp : public ofBaseApp{

  public:
    void setup();
    void setupPDSP();
    void setupImGui();
    void update();
    void draw();

    void ui_Draw();
    void ui_Menu();
    void ui_OSCWindow();
    void ui_EnvelopeWindow();
    void ui_OutputWindow();
    void Panic();
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

    float ui_env_attack = 5.0f;
    float ui_env_decay = 105.0f;
    float ui_env_sustain = 0.5f;
    float ui_env_release = 1000.f;

    bool midiLearnChk[100];

    //ofx PDSP
    pdsp::Engine                    engine;
    pdsp::ComputerKeyboard          keyboard;

    pdsp::midi::Input               midiIn;
    pdsp::midi::Keys                midiKeys;
    pdsp::midi::Controls            midiCCs;
    
    std::vector<Voice>              voices;

    pdsp::Amp                       mainOut;
    pdsp::ValueControl              gainCtrl;
    pdsp::ValueControl              waveSelectCtrl;
    pdsp::ValueControl              pulseWidthCtrl;

    pdsp::ValueControl              envAttackCtrl;
    pdsp::ValueControl              envDecayCtrl;
    pdsp::ValueControl              envSustainCtrl;
    pdsp::ValueControl              envReleaseCtrl;

    
};
