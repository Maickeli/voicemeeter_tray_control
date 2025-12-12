#include <windows.h>

#include <iostream>

#include "Tray.h"
#include "VoicemeeterApi.h"
#include "VolumeListener.h"
#include "WinAudio.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int) {
  Tray tray;

  Voicemeeter vm;

  // Command line args
  int argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  for (int i = 1; i < argc; ++i) {
    if (wcscmp(argv[i], L"--cmd") == 0) {
      AllocConsole();
      freopen("CONOUT$", "w", stdout);
    }
  }
  LocalFree(argv);

  if (!vm.init()) {
    MessageBox(nullptr, "Failed load VoiceMeeter DLL", "Error", MB_OK);
    return -1;
  }

  if (!vm.connect()) {
    MessageBox(nullptr, "Failed to connect to VoiceMeeter", "Error", MB_OK);
    return -1;
  }

  VolumeListener volume_listener(&vm);
  WinAudio win_audio(&volume_listener);
  if (!win_audio.init()) {
    MessageBox(nullptr,
               "Failed connect to VoiceMeeter audio device volume control. "
               "Make sure VoiceMeeter Input (VB-Audio VoiceMeeter VAIO) "
               "device is enabled. ",
               "Error", MB_OK);
    return -1;
  }

  float vm_volume = vm.getBusGainNormalized(0);
  win_audio.setVolume(vm_volume);

  bool vm_mute = vm.getBusMute(0);
  win_audio.setMute(vm_mute);

  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
