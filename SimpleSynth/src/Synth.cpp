#include "Synth.h"

void Synth::Voice::setup(Synth & ui, int v)
{
  addModuleInput("trig", osc.in("trigger")); // first, default in
  addModuleInput("pitch", osc.in("pitch"));
  


  addModuleOutput("signal", osc); // first, default out
  
}

void Synth::setup(int numVoices)
{
  addModuleInput("filter_LFO_freq", filterLFO.in_freq()); // first = default, here useless
  addModuleInput("filter_LFO_shape", filterLFOShape.in_select());
  addModuleInput("filter_LFO_amount", lFOToFilterAmount.in_mod());

  addModuleOutput("signal", signalOut); // first = default

  voices.resize(numVoices);

  signalOut.set(1.0f);

  int voiceIndex = 0;
  for (auto &v : voices)
  {
    v.setup(*this, voiceIndex);
    v.out("signal") >> allVoices; // all voice ouput here

    voiceIndex++;
  }


  filterLFOShape.resize(4);

  filterLFO.out_sine() >> filterLFOShape.input(0);
  filterLFO.out_triangle() >> filterLFOShape.input(1);
  filterLFO.out_saw() >> filterLFOShape.input(2);
  filterLFO.out_square() >> filterLFOShape.input(3);

  filterLFOShape >> lFOToFilterAmount;

  lFOToFilterAmount >> filter.in_cutoff();
  lFOToFilterAmount >> filter2.in_cutoff();

  allVoices >> filter;
  allVoices >> filter2;

  filter >> afterFilters;
  filter2 >> afterFilters;

  afterFilters >> signalOut;
}