#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "modules/voiceFullFeatures.h"

class Synth : public pdsp::Patchable
{
public:

  class Voice : public pdsp::Patchable { // internal class ----------------------
      friend class Synth;
  public:
    Voice() {}
    Voice(const Voice& other) {}

    void setup(Synth & ui, int v);

    VoiceFullFeatures  osc;

  }; // end Voice class -------------------------------------------------------

  // public API --------------------------------------------------------------
  void setup(int numVoices);

  std::vector<Voice> voices;

  pdsp::PatchNode         allVoices;
  pdsp::VAFilter          filter;
  pdsp::SVFilter          filter2;


  pdsp::Amp          signalOut;
};