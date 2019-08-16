#include "SynthDeuxOscillateurs.h"



void SynthDeuxOscillateurs::Voice::setup(SynthDeuxOscillateurs & m, int v)
{
  // create inputs and outputs
  addModuleInput("trig", voiceTrigger); // voice trigger
  addModuleInput("pitch", oscillator01.in_pitch()); // voice pitch
  addModuleOutput("signal", voiceAmp); // voice output

  // patching 

  //// setup wave forms switch
  //waveFormSwitch01.resize(4);

  //oscillator01.out_sine() >> waveFormSwitch01.input(0);
  //oscillator01.out_triangle() >> waveFormSwitch01.input(1);
  //oscillator01.out_saw() >> waveFormSwitch01.input(2);
  //oscillator01.out_pulse() >> waveFormSwitch01.input(3);

  //0.0f >> waveFormSwitch01.in_select();

  //// path Synth to update selected wave form
  //m.wave_form >> waveFormSwitch01;

  //// switch output to voice amp
  //waveFormSwitch01 >> voiceAmp;

  //// setup pulse wave form pulse width control
  //m.pulse_width_ctrl >> oscillator01.in_pw();

  //voiceTrigger >> envelope >> voiceAmp.in_mod();

  //m.env_ctrl_attack >> envelope.in_attack();
  //m.env_ctrl_decay >> envelope.in_decay();
  //m.env_ctrl_sustain >> envelope.in_sustain();
  //m.env_ctrl_release >> envelope.in_release();

  oscillator01 >> m.mainOut01;
  oscillator01 >> m.mainOut02;
}

void SynthDeuxOscillateurs::setup(int numVoices)
{
  
  //set params values
  env_ctrl_attack.set(0);
  env_ctrl_attack.enableSmoothing(50);
  env_ctrl_decay.set(200);
  env_ctrl_decay.enableSmoothing(50);
  env_ctrl_sustain.set(0.6f);
  env_ctrl_sustain.enableSmoothing(50);
  env_ctrl_release.set(1000);
  env_ctrl_release.enableSmoothing(50);

  // setup voices
  voices.resize(numVoices);

  for (int i = 0; i < numVoices; ++i) {
    voices[i].setup(*this, i);
  }


}

pdsp::Patchable & SynthDeuxOscillateurs::MainOut01()
{
  return mainOut01;
}

pdsp::Patchable & SynthDeuxOscillateurs::MainOut02()
{
  return mainOut02;
}
