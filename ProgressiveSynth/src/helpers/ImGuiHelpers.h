#pragma once

#include "ofxImGui.h"


void ShowHelpMarker(const char* desc);
bool MyKnob(const char* label, float* p_value, float v_min, float v_max, int valuePrecision = 2);
bool MyKnob2(const char* label, float* p_value, float v_min, float v_max, int valuePrecision = 2, float radius = 40.0f, bool filledNeedle = false);
void ofxImGuiApplyCorporateGreyTheme(float is3D);


