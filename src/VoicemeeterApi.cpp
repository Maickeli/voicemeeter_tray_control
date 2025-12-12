#include "VoicemeeterApi.h"

#include <iostream>

Voicemeeter::~Voicemeeter() {
  logout();
  FreeLibrary(dll);
}

bool Voicemeeter::init() {
  dll = LoadLibraryA("C:\\Program Files (x86)\\VB\\Voicemeeter\\VoicemeeterRemote64.dll");

  if (!dll) {
    dll = LoadLibraryA("C:\\Program Files (x86)\\VB\\Voicemeeter\\VoicemeeterRemote.dll");
  }

  if (!dll) {
    return false;
  }

  login = (VBVMR_Login)GetProcAddress(dll, "VBVMR_Login");
  logout = (VBVMR_Logout)GetProcAddress(dll, "VBVMR_Logout");
  getParam = (VBVMR_GetParameterFloat)GetProcAddress(dll, "VBVMR_GetParameterFloat");
  setParam = (VBVMR_SetParameterFloat)GetProcAddress(dll, "VBVMR_SetParameterFloat");
  isParamsDirty = (VBVMR_IsParametersDirty)GetProcAddress(dll, "VBVMR_IsParametersDirty");

  return login && logout && setParam && getParam && isParamsDirty;
}

bool Voicemeeter::connect() { return login() == 0; }

float Voicemeeter::getBusGain(int num) {
  isParamsDirty();
  char param[64];
  sprintf_s(param, "Bus[%d].Gain", num);
  float gain = 0;
  getParam(param, &gain);
  return gain;
}

void Voicemeeter::setBusGain(int num, float gain) {
  char param[64];
  sprintf_s(param, "Bus[%d].Gain", num);
  setParam(param, gain);
}

float Voicemeeter::getBusGainNormalized(int num) {
  float gain = getBusGain(num);
  float normalized = (gain + 60.0f) / 72.0f;
  return normalized;
}

int Voicemeeter::checkParamsDirty() { return isParamsDirty(); }
