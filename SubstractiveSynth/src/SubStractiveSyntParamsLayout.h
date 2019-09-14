#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxPDSP.h"
#include "SubstractiveSynthParams.h"
#include "PatchParamsOfxImGui.h"
#include "PatchParamsLayout.h"

class SubstractiveSynthParamsLayout : public PatchParamsLayout
{
public:
  SubstractiveSynthParamsLayout();
  ~SubstractiveSynthParamsLayout();
};