#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxImGui.h"
#include "CorporateGreyTheme.h"
#include "Synth.h"
#include "ofxXmlSettings.h"

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
    
    // wave forms
    std::vector<std::string> waveFormes = {"sine", "triangle", "saw", "pulse", "noise"};
    
    // OSC 1
    pdsp::ValueControl      waveFormCtrl;
    pdsp::Parameter         waveForm;
    pdsp::Parameter         pulseWidth;
    pdsp::Parameter         attack;
    pdsp::Parameter         decay;
    pdsp::Parameter         sustain;
    pdsp::Parameter         release;
    pdsp::Parameter         detune;
    pdsp::Parameter         detuneFine;
    pdsp::Parameter         level;

    std::vector<std::string> lfoWaveFormes = { "sine", "triangle", "saw", "square" };
    pdsp::ValueControl      lfo1waveFormCtrl;
    pdsp::Parameter         lfo1waveForm;
    pdsp::Parameter         lfo1Freq;
    pdsp::Parameter         lfo1ToOSCPitchAmp;
    pdsp::Parameter         lfo1ToOSCLevelAmp;
    pdsp::Parameter         lfo1ToOSCPWAmp;


    // OSC 2
    pdsp::ValueControl      waveForm2Ctrl;
    pdsp::Parameter         waveForm2;
    pdsp::Parameter         pulseWidth2;
    pdsp::Parameter         attack2;
    pdsp::Parameter         decay2;
    pdsp::Parameter         sustain2;
    pdsp::Parameter         release2;
    pdsp::Parameter         detune2;
    pdsp::Parameter         detuneFine2;
    pdsp::Parameter         level2;
    // OSC 2 filter ADSR
    std::vector<std::string> osc2FilterTypes = {"LowPass", "BandPass", "HighPass", "Notch" };
    pdsp::ValueControl      osc2FilterTypeCtrl;
    pdsp::Parameter         osc2FilterType;
    pdsp::Parameter         osc2FilterCutoff;
    pdsp::Parameter         osc2FilterReso;
    pdsp::Parameter         osc2FilterLevel;
    pdsp::Parameter         osc2FilterAttack;
    pdsp::Parameter         osc2FilterDecay;
    pdsp::Parameter         osc2FilterSustain;
    pdsp::Parameter         osc2FilterRelease;


    // Filter
    std::vector<std::string> filterTypes = { "LowPass24", "LowPass12", "HighPass24", "HighPass12", "BandPass24", "BandPass12" };
    pdsp::ValueControl      filterTypeCtrl;
    pdsp::Parameter         filterType;
    pdsp::Parameter         filterCutoff;
    pdsp::Parameter         filterReso;

    // Filter 2
    std::vector<std::string> filter2Types = { "LowPass", "BandPass", "HighPass", "Notch"};
    pdsp::ValueControl      filter2TypeCtrl;
    pdsp::Parameter         filter2Type;
    pdsp::Parameter         filter2Cutoff;
    pdsp::Parameter         filter2Reso;

    // filter LFO
    pdsp::ValueControl      filterLFOWaveFormCtrl;
    pdsp::Parameter         filterLFOWaveForm;
    pdsp::Parameter         filterLFOFreq;
    pdsp::Parameter         filterLFOAmount;

    Synth                   synth;

    pdsp::ParameterGain     gain;

    ofxImGui::Gui           gui;

    ofParameterGroup        patch;
    ofParameter<string>     patchVersion;
    ofParameter<string>     patchName;
    ofParameter<string>     patchDescription;
    ofParameterGroup        voiceOSC1Config;
    ofParameterGroup        voiceOSC2Config;
    ofParameterGroup        synthFilters;

};
