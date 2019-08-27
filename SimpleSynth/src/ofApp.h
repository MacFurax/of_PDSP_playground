#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxImGui.h"
#include "CorporateGreyTheme.h"
#include "Synth.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void setup_PDSP();
    void setup_GUI();
    void RefreshMIDIInDeviceList();
    void update();
    void draw();

    void draw_UI();

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

    pdsp::Engine            engine;
    int                     voicesNum;
    const int               polyphonyVoiceCount = 8;
    const int               unisonVoiceCount = 1;

    pdsp::ComputerKeyboard  keyboard;

    pdsp::midi::Input       midiIn;
    pdsp::midi::Keys        midiKeys;
    pdsp::midi::Controls    midiCCs;

    // params controlling synth behaviour
    
    // MIDI in port selection variables
    // separate window
    ofParameterGroup        MIDIINParamGroup;
    int                     selectedMIDIIN = 0;
    std::vector<string>     midiInDeviceNames;
    int                     midiInDeviceCount;
    
    pdsp::ParameterGain     gain;

    std::vector<std::string> waveFormes = {"sine", "triangle", "saw", "pulse"};
    pdsp::ValueControl      waveFormCtrl;
    pdsp::Parameter         waveForm;
    pdsp::Parameter         pulseWidth;
    pdsp::Parameter         attack;
    pdsp::Parameter         decay;
    pdsp::Parameter         sustain;
    pdsp::Parameter         release;
    pdsp::Parameter         detune;
    pdsp::Parameter         detuneFine;
    pdsp::ParameterAmp      level;

    pdsp::ValueControl      waveForm2Ctrl;
    pdsp::Parameter         waveForm2;
    pdsp::Parameter         pulseWidth2;
    pdsp::Parameter         attack2;
    pdsp::Parameter         decay2;
    pdsp::Parameter         sustain2;
    pdsp::Parameter         release2;
    pdsp::Parameter         detune2;
    pdsp::Parameter         detuneFine2;
    pdsp::ParameterAmp      level2;

    Synth                   synth;

    ofxImGui::Gui           gui;
};
