#include "Synth.h"

void Synth::Voice::setup(Synth & ui, int v)
{
  addModuleInput("trig", voiceTrigger); // first, default in
  addModuleInput("pitch", voicePitch);
  addModuleOutput("signal", voiceAmp); // first, default out

  // patchs
  // voice in pitch to osc pitch
  voicePitch >> oscillator.in_pitch();
  // osc out to amp in
  oscillator.out_pulse() >> voiceAmp;
  // ADSR out to amp modulation in, here with fixed ADSR values
  voiceTrigger >> ampEnv.set(0.0f, 100.0f, 0.5f, 1000.0f) >> voiceAmp.in_mod();

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