#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxPDSP.h"
#include "ofxPDSPTools.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void ofApp::drawUI();

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
		PatchParams             pp;
		PatchFilesStore			patchStore;
		ofxImGuiPatchParamsUI	patchParamUI;
		ofxImGuiMIDIDevicesSelector MIDIDeviceUI;
		ofxImGuiLoadSavePatchs	patchSaveLoadUI;

		ofxImGui::Gui			gui;

		pdsp::midi::Input       midiIn;
		pdsp::midi::Keys        midiKeys;
		pdsp::midi::Controls    midiCCs;
		pdsp::Engine			engine;

		
};
