#ifndef METRONOME_H
#define METRONOME_H

#include <iostream>
#include <atomic>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>

#include <sndfile.hh>

// #include <gtkmm.h>


jack_client_t* client;

jack_port_t* AUDIO_out_left;
jack_port_t* AUDIO_out_right;


int sampleRate;

std::vector<float> sampleVector;
std::vector<float> sampleVector2;

float sample;

int playbackIndex = 0;

int BPM = 80;

std::atomic<double> dt;  // tempo ?
unsigned int cur_time = 0;
double next_click;
int counter = 0;

#endif // METRONOME_H