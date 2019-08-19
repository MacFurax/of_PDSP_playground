#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

class Synth : public pdsp::Patchable
{
public:
  class Voice : public pdsp::Patchable { // internal class ----------------------
      //friend class PolySynth;
  public:
    Voice() {}
    Voice(const Voice& other) {}

    void setup(Synth & ui, int v);


  private:
    pdsp::PatchNode     voiceTrigger;
    pdsp::PatchNode     voicePitch;

    pdsp::VAOscillator  oscillator;
        
    pdsp::Amp           voiceAmp;

    pdsp::ADSR          ampEnv;
    

  }; // end Voice class -------------------------------------------------------

  // public API --------------------------------------------------------------
  void setup(int numVoices);

  std::vector<Voice> voices;
};