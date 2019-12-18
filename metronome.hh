#include <iostream>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>

#include <sndfile.hh>

#include "helpers.cc"



jack_client_t* client;

jack_port_t* AUDIO_out_left;
jack_port_t* AUDIO_out_right;

jack_port_t* MIDI_in;
jack_port_t* MIDI_out;


const int sampleRate = 44100;
// int samplerate = jack_get_sample_rate( client );
