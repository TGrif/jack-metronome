#include <iostream>

#include <jack/jack.h>
#include <jack/midiport.h>

#include <gtkmm.h>

#include "helpers.cpp"


jack_client_t* client;

jack_port_t* AUDIO_out_left;
jack_port_t* AUDIO_out_right;

jack_port_t* MIDI_in;
jack_port_t* MIDI_out;


const int sampleRate = 44100;
