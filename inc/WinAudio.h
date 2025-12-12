#ifndef WIN_AUDIO_H
#define WIN_AUDIO_H

// clang-format off
#include <windows.h>
#include <mmdeviceapi.h>
// clang-format on

#include "VolumeListener.h"

class WinAudio {
 public:
  WinAudio(VolumeListener* volume_listener);
  ~WinAudio();

  bool init();

  void setVolume(float volume);

 private:
  IAudioEndpointVolume* ep_volume_ = nullptr;
  IMMDeviceEnumerator* device_enumerator_ = nullptr;
  IMMDevice* device_ = nullptr;

  VolumeListener* volume_listener_ = nullptr;
};

#endif