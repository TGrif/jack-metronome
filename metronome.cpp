#include "testjack.hpp"


void process_callback (jack_nframes_t nframes, void*) {
  
  void* midi_port_buf = jack_port_get_buffer(MIDI_out, nframes);
  
}

void loop() {
  // int i = 0;
  while (true) {
  // while (i < 3) {
    std::cout << "tic" << std::endl;
    sleep(1);
    // i++;
  }
}

void jack_shutdown (void *arg) {  // FIXME
  std::cout << "Jack jack_shutdown." << std::endl;
}


int main (int argc, char *argv[]) {
  
  client = jack_client_open("MetronomeJackClientTest", JackNullOption, 0, 0);
  jack_set_process_callback(client, process_callback, 0);
  MIDI_out = jack_port_register(client, "output", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
  jack_activate(client);
  jack_on_shutdown(client, jack_shutdown, 0);
  
  loop();
  
  
  jack_deactivate(client);
  
  // close the client
  jack_client_close(client);
  std::cout << "Jack closed." << std::endl;
  return 0;
  
}
