#include "ImGuiHelpers.h"

void ShowHelpMarker(const char* desc)
{
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

// Implementing a simple custom widget using the public API.
// You may also use the <imgui_internal.h> API to get raw access to more data/helpers, however the internal API isn't guaranteed to be forward compatible.
// FIXME: Need at least proper label centering + clipping (internal functions RenderTextClipped provides both but api is flaky/temporary)
bool MyKnob(const char* label, float* p_value, float v_min, float v_max, int valuePrecision)
{
  ImGuiIO& io = ImGui::GetIO();
  ImGuiStyle& style = ImGui::GetStyle();

  float radius_outer = 20.0f;
  ImVec2 pos = ImGui::GetCursorScreenPos();
  float line_height = ImGui::GetTextLineHeight();
  ImVec2 center = ImVec2(pos.x + radius_outer, pos.y + radius_outer + line_height);
  
  ImDrawList* draw_list = ImGui::GetWindowDrawList();

  float ANGLE_MIN = 3.141592f * 0.75f;
  float ANGLE_MAX = 3.141592f * 2.25f;

  ImGui::InvisibleButton(label, ImVec2(radius_outer * 3, radius_outer * 2 + line_height + style.ItemInnerSpacing.y*4));
  bool value_changed = false;
  bool is_active = ImGui::IsItemActive();
  bool is_hovered = ImGui::IsItemActive();
  if (is_active && io.MouseDelta.x != 0.0f)
  {
    float step = (v_max - v_min) / 400.0f;
    *p_value += io.MouseDelta.x * step;
    if (*p_value < v_min) *p_value = v_min;
    if (*p_value > v_max) *p_value = v_max;
    value_changed = true;
  }

  float t = (*p_value - v_min) / (v_max - v_min);
  float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
  float angle_cos = cosf(angle), angle_sin = sinf(angle);
  float radius_inner = radius_outer * 0.40f;

  //draw label
  draw_list->AddText(ImVec2(pos.x, pos.y), ImGui::GetColorU32(ImGuiCol_Text), label);
  // draw knob
  draw_list->AddCircleFilled(center, radius_outer, ImGui::GetColorU32(ImGuiCol_FrameBg), 16);
  draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - 2), center.y + angle_sin * (radius_outer - 2)), ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);
  draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
  // drraw value
  std::stringstream ss;
  ss << std::setprecision(valuePrecision) << std::fixed << *p_value;
  draw_list->AddText(ImVec2(pos.x, pos.y + radius_outer * 2 + style.ItemInnerSpacing.y*4), ImGui::GetColorU32(ImGuiCol_Text), ss.str().c_str());

 /* if (is_active || is_hovered)
  {
    ImGui::SetNextWindowPos(ImVec2(pos.x - style.WindowPadding.x, pos.y - line_height - style.ItemInnerSpacing.y - style.WindowPadding.y));
    ImGui::BeginTooltip();
    ImGui::Text("%.3f", *p_value);
    ImGui::EndTooltip();
  }*/

  return value_changed;
}

bool MyKnob2(const char* label, float* p_value, float v_min, float v_max, int valuePrecision, float radius, bool filledNeedle)
{
  ImGuiIO& io = ImGui::GetIO();
  ImGuiStyle& style = ImGui::GetStyle();

  float radius_outer = radius;
  ImVec2 pos = ImGui::GetCursorScreenPos(); // get top left of current widget
  float line_height = ImGui::GetTextLineHeight();
  float space_height = line_height * 0.1; // to add between top, text, knob, value and bottom
  float space_width = radius * 0.1; // to add on left and right to diameter of knob
  ImVec4 widgetRec = ImVec4(pos.x, pos.y, radius*2.0f + space_width*2.0f, space_height*4.0f + radius*2.0f + line_height*2.0f);
  ImVec2 labelLength = ImGui::CalcTextSize(label);
  
  ImVec2 center = ImVec2(pos.x + space_width + radius, pos.y + space_height*2 + line_height + radius);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();

  float ANGLE_MIN = 3.141592f * 0.75f;
  float ANGLE_MAX = 3.141592f * 2.25f;

  ImGui::InvisibleButton(label, ImVec2(widgetRec.z, widgetRec.w));
  bool value_changed = false;
  bool is_active = ImGui::IsItemActive();
  bool is_hovered = ImGui::IsItemActive();
  if (is_active && io.MouseDelta.x != 0.0f)
  {
    float step = (v_max - v_min) / 400.0f;
    *p_value += io.MouseDelta.x * step;
    if (*p_value < v_min) *p_value = v_min;
    if (*p_value > v_max) *p_value = v_max;
    value_changed = true;
  }

  float t = (*p_value - v_min) / (v_max - v_min);
  float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
  float angle_cos = cosf(angle), angle_sin = sinf(angle);
  float radius_inner = radius_outer * 0.40f;

  //draw label
  float texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
  draw_list->AddText(ImVec2(texPos, pos.y+ space_height), ImGui::GetColorU32(ImGuiCol_Text), label);
  // draw knob
  draw_list->AddCircleFilled(center, radius_outer, ImGui::GetColorU32(ImGuiCol_FrameBg), 16);
  draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - 2), center.y + angle_sin * (radius_outer - 2)), ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);
  draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
  
  // draw value
  std::stringstream ss;
  ss << std::setprecision(valuePrecision) << std::fixed << *p_value;
  labelLength = ImGui::CalcTextSize(ss.str().c_str());
  texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);

  draw_list->AddText(ImVec2(texPos, pos.y + space_height*3 + line_height + radius*2), ImGui::GetColorU32(ImGuiCol_Text), ss.str().c_str());

  return value_changed;
}

// apply CorporateGrey theme from
// https://github.com/ocornut/imgui/issues/707#issuecomment-468798935
//
// is3D
// 0 = FLAT APPEARENCE
// 1 = MORE "3D" LOOK
//
void ofxImGuiApplyCorporateGreyTheme(float is3D = 1.0f)
{
  ImGuiStyle & style = ImGui::GetStyle();
  ImVec4 * colors = style.Colors;
  
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
  colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
  colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

  style.PopupRounding = 3;

  style.WindowPadding = ImVec2(4, 4);
  style.FramePadding = ImVec2(6, 4);
  style.ItemSpacing = ImVec2(6, 2);

  style.ScrollbarSize = 18;

  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = is3D;

  style.WindowRounding = 3;
  style.ChildRounding = 3;
  style.FrameRounding = 3;
  style.ScrollbarRounding = 2;
  style.GrabRounding = 3;

#ifdef IMGUI_HAS_DOCK 
  style.TabBorderSize = is3D;
  style.TabRounding = 3;

  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
#endif
}


