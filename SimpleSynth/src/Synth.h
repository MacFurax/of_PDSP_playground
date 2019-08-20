#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

class Synth : public pdsp::Patchable
{
public:
  class Voice : public pdsp::Patchable { // internal class ----------------------
      friend class Synth;
  public:
    Voice() {}
    Voice(const Voice& other) {}

    void setup(Synth & ui, int v);

    pdsp::ADSR          ampEnv;

  private:
    pdsp::PatchNode     voiceTrigger;
    pdsp::PatchNode     voicePitch;

    pdsp::VAOscillator  oscillator;

    pdsp::VAFilter      filter;
        
    pdsp::Amp           voiceAmp;

  }; // end Voice class -------------------------------------------------------

  // public API --------------------------------------------------------------
  void setup(int numVoices);

  std::vector<Voice> voices;
};