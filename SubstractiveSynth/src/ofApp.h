#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxPDSP.h"
#include "SubstractiveSynthParams.h"
#include "PatchParamsOfxImGui.h"
#include "PatchParamsLayout.h"


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

private:

    void draw_ui();
    void draw_ui_param(shared_ptr<LayoutParam> param);
    void draw_ui_group(shared_ptr<LayoutGroup> group);

    ofxImGui::Gui           gui;

    SubstractiveSynthParams synthParams;
    PatchParamsLayout       paramsLayout;
    PatchParamsOfxImGui     paramsUI;
};
