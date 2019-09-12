# of_PDSP_playground

Visual studio solution to play with OpenFrameworks (ofx)ImGui and ofxPDSP

Required Addons

* ofxAudioFile
* ofxGui
* ofxImGui (my fork https://github.com/MacFurax/ofxImGui.git `branch docking` )
* ofxPDSP  (my fork https://github.com/MacFurax/ofxPDSP.git `branch features/midi`)
* ofxMidi
* ofxOSC

Required libraries

* ofxPDSP_More (https://github.com/MacFurax/ofxPDSP_More.git)

# Compile

For now only with Visual Studio (2017)

Folder layout for this solution to compile should be

```
<any_folder>
    of_v0.10.1_vs2017_release
    OF
        of_PDSP_playground
```

# Projects

## ProgressiveSynth

Progresivelly build synths (additive, substractive, pays wih filters, LFOs...) and UIs to configure them.

