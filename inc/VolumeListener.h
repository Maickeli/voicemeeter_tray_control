#ifndef VOLUME_LISTENER_H
#define VOLUME_LISTENER_H

// clang-format off
#include "VoicemeeterApi.h"

#include <endpointvolume.h>
// clang-format on

class VolumeListener : public IAudioEndpointVolumeCallback {
 public:
  VolumeListener(Voicemeeter* vm);

  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID** ppvInterface) override;
  ULONG STDMETHODCALLTYPE AddRef() override;
  ULONG STDMETHODCALLTYPE Release() override;
  HRESULT STDMETHODCALLTYPE OnNotify(AUDIO_VOLUME_NOTIFICATION_DATA* pNotify) override;

 private:
  LONG cref_;
  Voicemeeter* vm_;
};

#endif