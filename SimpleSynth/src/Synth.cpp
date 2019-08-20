#include "Synth.h"

void Synth::Voice::setup(Synth & ui, int v)
{
  addModuleInput("trig", voiceTrigger); // first, default in
  addModuleInput("pitch", voicePitch);
  addModuleInput("cutoff", filter.in_cutoff());
  addModuleInput("reso", filter.in_reso());
  addModuleOutput("signal", voiceAmp); // first, default out

  // patchs
  // voice in pitch to osc pitch
  voicePitch >> oscillator.in_pitch();
  // osc out to amp in
  oscillator.out_pulse() >> filter >> voiceAmp;
  // ADSR out to amp modulation in, here with fixed ADSR values
  voiceTrigger >> ampEnv >> voiceAmp.in_mod();

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