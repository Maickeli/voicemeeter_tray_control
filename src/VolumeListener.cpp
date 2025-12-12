#include "VolumeListener.h"

VolumeListener::VolumeListener(Voicemeeter* vm) : cref_(1), vm_(vm) {}

HRESULT STDMETHODCALLTYPE VolumeListener::QueryInterface(REFIID riid, VOID** ppvInterface) {
  if (IID_IUnknown == riid) {
    *ppvInterface = (IUnknown*)this;
  } else if (__uuidof(IAudioEndpointVolumeCallback) == riid) {
    *ppvInterface = (IAudioEndpointVolumeCallback*)this;
  } else {
    *ppvInterface = nullptr;
    return E_NOINTERFACE;
  }
  AddRef();
  return S_OK;
}

ULONG STDMETHODCALLTYPE VolumeListener::AddRef() { return InterlockedIncrement(&cref_); }

ULONG STDMETHODCALLTYPE VolumeListener::Release() {
  ULONG ul_ref = InterlockedDecrement(&cref_);
  return ul_ref;
}

HRESULT STDMETHODCALLTYPE VolumeListener::OnNotify(AUDIO_VOLUME_NOTIFICATION_DATA* notify_data) {
  if (notify_data == nullptr) return S_OK;

  float volume = notify_data->fMasterVolume;
  float vm_volume = volume * 72.0f - 60.0f;

  bool mute = notify_data->bMuted != FALSE;

  if (vm_) {
    vm_->setBusGain(0, vm_volume);
    vm_->setBusMute(0, mute);
  }

  return S_OK;
}
