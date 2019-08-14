#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "helpers/ImGuiHelpers.h"
#include "ofxPDSP.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void setupImGui();
    void update();
    void draw();

    void drawImGui();

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

    // ofxImGui
    ofxImGui::Gui gui;
    float attackValue = 0.0f;
    float decayValue = 300.0f;

    
};
