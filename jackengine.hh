#ifndef JACK_ENGINE_H
#define JACK_ENGINE_H

#include <jack/jack.h>
#include <jack/midiport.h>

typedef jack_default_audio_sample_t sample_t;  // NOOP


class JackEngine {

  protected:

    jack_client_t* client;

    jack_port_t* AUDIO_out_left;
    jack_port_t* AUDIO_out_right;

    int sampleRate;

};

#endif // JACK_ENGINE_H