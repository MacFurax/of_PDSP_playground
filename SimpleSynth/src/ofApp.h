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
    
    // global group 
    ofParameterGroup        globalParamGroup;
    
    ofParameterGroup        mainOutParamGroup;
    pdsp::ParameterGain     gain;

    ofParameterGroup        ADSRParamGroup;
    pdsp::Parameter         attack;
    pdsp::Parameter         decay;
    pdsp::Parameter         sustain;
    pdsp::Parameter         release;

    ofParameterGroup        filterADSRParamGroup;
    pdsp::Parameter         envAttack;
    pdsp::Parameter         envDecay;
    pdsp::Parameter         envSustain;
    pdsp::Parameter         envRelease;

    ofParameterGroup        filterParamGroup;
    pdsp::Parameter         cutoff;
    pdsp::Parameter         reso;

    Synth                   synth;

    ofxImGui::Gui           gui;

    
};
