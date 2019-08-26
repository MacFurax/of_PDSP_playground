#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "modules/oscWaveSelectDetune.h"

class Synth : public pdsp::Patchable
{
public:

  class Voice : public pdsp::Patchable { // internal class ----------------------
      friend class Synth;
  public:
    Voice() {}
    Voice(const Voice& other) {}

    void setup(Synth & ui, int v);

    OscWaveSelectDetune  osc;

  }; // end Voice class -------------------------------------------------------

  // public API --------------------------------------------------------------
  void setup(int numVoices);

  std::vector<Voice> voices;
  pdsp::Amp          signalOut;
};