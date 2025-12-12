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
  if (ul_ref == 0) {
    delete this;
  }
  return ul_ref;
}

// IAudioEndpointVolumeCallback method (This is the important part)
HRESULT STDMETHODCALLTYPE VolumeListener::OnNotify(AUDIO_VOLUME_NOTIFICATION_DATA* notify_data) {
  if (notify_data == nullptr) return S_OK;

  float volumeScalar = notify_data->fMasterVolume;
  float voiceMeeterVolume = volumeScalar * 72.0f - 60.0f;

  if (vm_) {
    vm_->setBusGain(0, voiceMeeterVolume);
  }

  return S_OK;
}