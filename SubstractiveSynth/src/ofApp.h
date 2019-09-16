#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxPDSP.h"
#include "SubstractiveSynthParams.h"
#include "SubstractiveSynth.h"
#include "PatchParamsOfxImGui.h"
#include "PatchParamsLayout.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupParamsLayout();
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

private:

    void drawUI();
    void drawUIParam(shared_ptr<LayoutParam> param);
    void drawUIGroup(shared_ptr<LayoutGroup> group);

    ofxImGui::Gui gui;

	pdsp::midi::Input       midiIn;
	pdsp::midi::Keys        midiKeys;
	pdsp::midi::Controls    midiCCs;
	pdsp::Engine            engine;

	SubstractiveSynth synth;

    SubstractiveSynthParams synthParams;
    PatchParamsLayout paramsLayout;

};
