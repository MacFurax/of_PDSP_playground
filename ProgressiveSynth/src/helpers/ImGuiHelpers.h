#pragma once

#include "ofxImGui.h"


void ShowHelpMarker(const char* desc);
bool MyKnob(const char* label, float* p_value, float v_min, float v_max, int valuePrecision = 2);
void ofxImGuiApplyCorporateGreyTheme(float is3D);


