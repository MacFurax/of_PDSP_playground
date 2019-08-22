#include "Synth.h"

void Synth::Voice::setup(Synth & ui, int v)
{
  addModuleInput("trig", osc.in("trigger")); // first, default in
  addModuleInput("pitch", osc.in("pitch"));
  addModuleOutput("signal", osc); // first, default out
}

void Synth::setup(int numVoices)
{
  voices.resize(numVoices);

  int voiceIndex = 0;
  for (auto &v : voices)
  {
    v.setup(*this, voiceIndex);
    voiceIndex++;
  }
}