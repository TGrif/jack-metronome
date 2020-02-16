#ifndef ALSA_ENGINE_H
#define ALSA_ENGINE_H

#include <alsa/asoundlib.h>


class AlsaEngine {
  
  protected:
    
    int err;
    short buf[128];
    
    snd_pcm_t *playback_handle;
    snd_pcm_hw_params_t *hw_params;
    
};

#endif // ALSA_ENGINE_H
