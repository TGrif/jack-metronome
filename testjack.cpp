
// g++ testjack.cpp -o testjack `pkg-config jack gtkmm-2.4 --cflags --libs`

#include <jack/jack.h>
#include <jack/midiport.h>

#include "testjack.hpp"

#include "helpers.cpp"
#include "ui.cpp"


// jack_port_t* inputPort = 0;
jack_port_t* outputPort_left = 0;
jack_port_t* outputPort_right = 0;
jack_port_t* inputMidiPort = 0;

const int sampleRate = 44100;
int size = sampleRate * 1;


int process_callback(jack_nframes_t nframes, void*) {

  jack_midi_event_t in_event;
  
  // float* inputBuffer = (float*)jack_port_get_buffer(inputPort, nframes);
  float* outputBuffer_left = (float*)jack_port_get_buffer(outputPort_left, nframes);
  float* outputBuffer_right = (float*)jack_port_get_buffer(outputPort_right, nframes);
  
  void* midi_port_buf = jack_port_get_buffer(inputMidiPort, nframes);
  
  /*
  float sample[size];
  
  int frequency = 1800; // <-- frequency of the wave generated
  
  for (int i = 0; i < size; i++) {
    // write each sample, the math here is generating a sin wave
    sample[i] = sin(float(i) / size * M_PI * frequency);
    // outputBuffer[i] = sin(float(i) / size * 3.14 * frequency);
  }
  
  
  // this is the intresting part, we work with each sample of audio data
  // one by one, copying them across. Try multiplying the input by 0.5,
  // it will decrease the volume...
  for (int i = 0; i < (int) nframes; i++)
  {
    // copy data from input to output. Note this is not optimized for speed!
    // outputBuffer[i] = inputBuffer[i];
    // outputBuffer[i] = sin(float(i) / size * M_PI * frequency);
    outputBuffer_left[i] = sample[i];
    outputBuffer_right[i] = sample[i];
  }
  */
  
  for (int i = 0; i < (int) nframes; i++) {
    jack_midi_event_get(&in_event, midi_port_buf, i);
    if (in_event.buffer[0])
      std::cout << "Msg. " << in_event.buffer[0] << std::endl;
  }
  
  return 0;
}

void generate_sine() {
  
}



// void jack_shutdown(*client) {
//   // tell JACK to stop processing the client
//   jack_deactivate(client);
// 
//   // close the client
//   jack_client_close(client);
//   std::cout << "Jack closed." << std:endl;
// 
//   exit(0);
// }


int main(int argc, char *argv[]) {
  
  parseArguments(argc, argv);
  
  // buildUI(argc, argv);
  
  
  // create a JACK client and activate
  jack_client_t* client = jack_client_open("JackClientTest", JackNullOption, 0, 0);
  
  // register the process callback : JACK "calls us back" when there is
  // work to be done, and the "process" function does that work.
  jack_set_process_callback(client, process_callback, 0);
  // jack_on_shutdown(jack_handle, jack_shutdown(client), 0);
  
  // register two ports, one input one output, both of AUDIO type
  // inputPort = jack_port_register(client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
  outputPort_left = jack_port_register(client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  outputPort_right = jack_port_register(client, "output2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

  if ((outputPort_left == NULL) || (outputPort_right == NULL)) {
    fprintf(stderr, "no more JACK ports available\n");
    exit(1);
  }
  
  inputMidiPort = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
  
  // activate the client, ie: enable it for processing
  jack_activate(client);

  // pause for 30 seconds, letting process() do it's thing
  sleep(30);

  // tell JACK to stop processing the client
  jack_deactivate(client);
  
  // close the client
  jack_client_close(client);
  std::cout << "Jack closed." << std::endl;
  
  return 0;
}

// https://medium.com/@audiowaves/lets-write-a-simple-sine-wave-generator-with-c-and-juce-c8ab42d1f54f
// https://stackoverflow.com/questions/29748082/c-jackaudio-cant-get-stereo-sound
// https://github.com/harryhaaren/openAudioProgrammingTutorials
// https://github.com/harryhaaren/JACK-MIDI-Examples/
