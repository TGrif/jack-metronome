#ifndef JACK_ENGINE_H
#define JACK_ENGINE_H

#include <jack/jack.h>
#include <jack/midiport.h>


class JackEngine {
    
  protected:
  
    // static int staticProcess(jack_nframes_t nframes, void *arg);
    // int process(jack_nframes_t nframes);
    
    jack_client_t* client;

    jack_port_t* AUDIO_out_left;
    jack_port_t* AUDIO_out_right;
  
    int sampleRate;
  
};

#endif // JACK_ENGINE_H