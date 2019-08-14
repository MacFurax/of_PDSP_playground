#pragma once

#include "ofxImGui.h"

namespace ImGui
{
  static auto vector_getter = [](void* vec, int idx, const char** out_text)
  {
    auto& vector = *static_cast<std::vector<std::string>*>(vec);
    if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
    *out_text = vector.at(idx).c_str();
    return true;
  };

  bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);

  bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values);

}

void ShowHelpMarker(const char* desc);
bool MyKnob(const char* label, float* p_value, float v_min, float v_max, int valuePrecision = 2);
void ofxImGuiSetFont( ofxImGui::Gui gui, std::string fontPath, float size);
void ofxImGuiEnableDocking();
void ofxImGuiApplyCorporateGreyTheme(float is3D);
void ofxImGuiStartDocking();
void ofxImGuiEndDocking();

