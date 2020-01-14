#ifndef METRONOME_H
#define METRONOME_H

#include <iostream>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>

#include <sndfile.hh>


jack_client_t* client;

jack_port_t* AUDIO_out_left;
jack_port_t* AUDIO_out_right;

jack_port_t* MIDI_in;
jack_port_t* MIDI_out;

std::vector<float> sampleVector;
// std::vector<float> sampleVector2;

int playbackIndex = 0;
// int playbackIndex2 = 0;

#endif // METRONOME_H