#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

// my fist Polyphonique synth using ofxPDSP
class SynthDeuxOscillateurs {

public:
  // single voice class
  class Voice : public pdsp::Patchable {
    friend class SynthDeuxOscillateurs;

    public:
      Voice() {}
      Voice(const Voice& other) {}

    private:
      void setup(SynthDeuxOscillateurs & m, int v);

      // OSC 1 
      pdsp::VAOscillator oscillator01;
      pdsp::ValueControl pulseWidthCtrl01;
      pdsp::Switch waveFormSwitch01;

      // voice 
      pdsp::PatchNode voiceTrigger;
      pdsp::Amp voiceAmp;
      pdsp::ADSR envelope;
  }; // end voice class ----------------------------------

  std::vector<Voice>  voices;

  pdsp::PatchNode pulse_width_ctrl;
  //pdsp::ValueControl gainCtrl;

  pdsp::ValueControl env_ctrl_attack;
  pdsp::ValueControl env_ctrl_decay;
  pdsp::ValueControl env_ctrl_sustain;
  pdsp::ValueControl env_ctrl_release;

  pdsp::PatchNode wave_form;

  // Synth01 puclic APPI
  void setup( int numVoices );
  pdsp::Patchable& MainOut01();
  pdsp::Patchable& MainOut02();

private:
 
  pdsp::Amp mainOut01;
  pdsp::Amp mainOut02;
   
  
};
