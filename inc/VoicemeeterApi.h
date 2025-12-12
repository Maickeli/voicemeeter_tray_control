#ifndef VOICEMEETER_API_H
#define VOICEMEETER_API_H

#include <windows.h>

typedef int(__cdecl* VBVMR_Login)();
typedef int(__cdecl* VBVMR_Logout)();
typedef int(__cdecl* VBVMR_GetParameterFloat)(const char* param, float* value);
typedef int(__cdecl* VBVMR_SetParameterFloat)(const char* param, float value);
typedef int(__cdecl* VBVMR_IsParametersDirty)();

class Voicemeeter {
 private:
  HMODULE dll = nullptr;
  VBVMR_Login login = nullptr;
  VBVMR_Logout logout = nullptr;
  VBVMR_GetParameterFloat getParam = nullptr;
  VBVMR_SetParameterFloat setParam = nullptr;
  VBVMR_IsParametersDirty isParamsDirty = nullptr;

 public:
  ~Voicemeeter();

  bool init();

  bool connect();

  float getBusGain(int num);
  void setBusGain(int num, float gain);

  float getBusGainNormalized(int num);

  int checkParamsDirty();
};

#endif