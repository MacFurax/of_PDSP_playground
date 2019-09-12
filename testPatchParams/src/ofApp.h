#pragma once

#include "ofMain.h"
#include "PatchParams.h"
#include "PatchParamsOfxImGui.h"
#include "PatchFilesStore.h"
#include "ofxPDSP.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    pdsp::Engine            engine;
    pdsp::VAOscillator      osc;
    pdsp::Switch            waveForms;
    pdsp::Amp               oscLevel;
    pdsp::LFO               lfo;
    pdsp::Switch            lfoWaveForms;
    pdsp::Amp               lfoLevelToPitch;
    pdsp::Amp               lfoLevelToPW;

    PatchParams             pp;
    PatchParamsOfxImGui     ppDrawer;

    ofxImGui::Gui           gui;

    const string            patchesDirBase = "patches/";
    ofDirectory             patchesDir;
    ofParameter<int>        selectedPatch;
    std::vector<string>     patchNames;

    PatchFilesStore         patchStore;
		
};
