#include "WinAudio.h"

#include <functiondiscoverykeys_devpkey.h>

#include <iostream>

WinAudio::WinAudio(VolumeListener* volume_listener) : volume_listener_(volume_listener) {}

WinAudio::~WinAudio() {
  ep_volume_->UnregisterControlChangeNotify(volume_listener_);
  volume_listener_->Release();

  ep_volume_->Release();
  device_->Release();
  device_enumerator_->Release();
  CoUninitialize();
}

bool WinAudio::init() {
  CoInitialize(nullptr);

  CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER,
                   __uuidof(IMMDeviceEnumerator), (LPVOID*)&device_enumerator_);

  IMMDeviceCollection* devices = nullptr;
  device_enumerator_->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &devices);

  UINT count = 0;
  devices->GetCount(&count);

  for (UINT i = 0; i < count; i++) {
    IMMDevice* dev = nullptr;
    devices->Item(i, &dev);

    IPropertyStore* props = nullptr;
    dev->OpenPropertyStore(STGM_READ, &props);

    PROPVARIANT name;
    PropVariantInit(&name);

    props->GetValue(PKEY_Device_FriendlyName, &name);

    if (wcscmp(name.pwszVal, L"Voicemeeter Input (VB-Audio Voicemeeter VAIO)") == 0) {
      device_ = dev;
      props->Release();
      break;
    }

    PropVariantClear(&name);
    props->Release();
    dev->Release();
  }

  if (!device_) {
    std::cerr << "Couldn't find Voicemeeter output device";
    return false;
  }

  devices->Release();
  device_->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr,
                    (LPVOID*)&ep_volume_);

  ep_volume_->RegisterControlChangeNotify(volume_listener_);

  return true;
}

void WinAudio::setVolume(float volume) {
  if (!ep_volume_) return;
  ep_volume_->SetMasterVolumeLevelScalar(volume, nullptr);
}

void WinAudio::setMute(bool mute) {
  if (!ep_volume_) return;

  ep_volume_->SetMute(mute ? TRUE : FALSE, nullptr);
}