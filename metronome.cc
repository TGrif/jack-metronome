#include <vector>
#include <sndfile.hh>

#include "testjack.hh"

#include "ui.cc"


std::vector<float> sampleVector;
std::vector<float> sampleVector2;
int playbackIndex = 0;
int playbackIndex2 = 0;
int counter = 0;

int process_callback (jack_nframes_t nframes, void*) {
  
  float* outputBuffer_left = (float*)jack_port_get_buffer(AUDIO_out_left, nframes);
  float* outputBuffer_right = (float*)jack_port_get_buffer(AUDIO_out_right, nframes);
  
  // void* midi_port_buf = jack_port_get_buffer(MIDI_out, nframes);
  
  for (int i = 0; i < (int) nframes; i++) {
    
    // TODO fix metronome tick
    
    // here we check if index has gone played the last sample, and if it
    // has, then we reset it to 0 (the start of the sample).
    if (counter < 3) {
      
      
      if ( playbackIndex2 >= sampleVector2.size() ) {
        playbackIndex2 = 0;
        // counter = 0;
      }
      
      // std::cout << counter << std::endl;
      // because we have made sure that index is always between 0 -> sample.size(),
      // its safe to access the array .at(index)  The program would crash it furthury
      
      outputBuffer_left[i] = sampleVector2.at(playbackIndex2);
      outputBuffer_right[i] = sampleVector2.at(playbackIndex2);
      playbackIndex2++;
    } else {
      
    
      if ( playbackIndex >= sampleVector.size() ) {
        playbackIndex = 0;
        // counter++;
      }
      outputBuffer_left[i] = sampleVector.at(playbackIndex);
      outputBuffer_right[i] = sampleVector.at(playbackIndex);
      playbackIndex++;
    }
    
    // increase the index, so that we play the next sample
    
    if (counter > 3) counter = 0;
    else counter++;
  }

  return 0;
  
}

int loadTickSound() {
  SndfileHandle fileHandleTick("assets/metro_1.wav", SFM_READ,  SF_FORMAT_WAV | SF_FORMAT_FLOAT, 1, 44100);
  SndfileHandle fileHandleTack("assets/metro_2.wav", SFM_READ,  SF_FORMAT_WAV | SF_FORMAT_FLOAT, 1, 44100);
  
  // get the number of frames in the sample
  int sizeTick  = fileHandleTick.frames();
  int sizeTack  = fileHandleTack.frames();
  
  std::cout << sizeTick << std::endl;
  std::cout << sizeTack << std::endl;
  
  if (sizeTick == 0 || sizeTack == 0) {
    std::cout << "Problem when loading metronome sound." << std::endl;
    // file doesn't exist or is of incompatible type, main handles the -1
    return -1;
  }
  
  // int channels   = fileHandleTick.channels();
  // int samplerate = fileHandleTick.samplerate();
  // 
  // std::cout << channels << std::endl;
  // std::cout << samplerate << std::endl;
  
  sampleVector.resize(sizeTick);
  sampleVector2.resize(sizeTack);
  
  fileHandleTick.read(&sampleVector.at(0), sizeTick);
  fileHandleTack.read(&sampleVector2.at(0), sizeTack);
    
  return 0;
}

int loop() {
  int loadSound = loadTickSound();
  if (loadSound) {
    std::cout << "Problem when loading metronome sound." << std::endl;
    return 0;
  }
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
  // jack_client_free(client);
  // std::cout << client << std::endl;
  client = jack_client_open("MetronomeJackClientTest", JackNullOption, 0, 0);
  
  AUDIO_out_left = jack_port_register(client, "output_L", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  AUDIO_out_right = jack_port_register(client, "output_R", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  // MIDI_out = jack_port_register(client, "output", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
  
  jack_set_process_callback(client, process_callback, 0);
  jack_activate(client);
  jack_on_shutdown(client, jack_shutdown, 0);
  
  loop();
  
  // buildUI(argc, argv);
  
  // Gtk::Main kit(argc, argv);
  // 
  // MainWindow window;
  // //Shows the window and returns when it is closed.
  // Gtk::Main::run(window);
  // sleep(3);
  
  int d = jack_deactivate(client);
  // std::cout << d << std::endl;
  // close the client
  int c = jack_client_close(client);
  // std::cout << c << std::endl;
  std::cout << "Jack closed." << std::endl;
  return 0;
  
}
