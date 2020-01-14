#include "metronome.hh"

#include "ui.cc"



// int playbackIndex = 0;
// int playbackIndex2 = 0;

int jack_time;
int jack_time_start = 0;
// int counter = 0;
int BPM_in_milli = 1000;

// 1 minute -> 60 secondes -> 60000 millisecondes
// 60 BPM -> 1 battement par seconde -> 1 battement pour 1000 millisecondes


int process_callback (jack_nframes_t nframes, void*) {
  
  float* outputBuffer_left = (float*)jack_port_get_buffer(AUDIO_out_left, nframes);
  float* outputBuffer_right = (float*)jack_port_get_buffer(AUDIO_out_right, nframes);
  
  // void* midi_port_buf = jack_port_get_buffer(MIDI_out, nframes);

  
  jack_time = jack_get_time();  // TODO BPM
  // std::cout << jack_time << std::endl;
  
  
  for (int i = 0; i < (int) nframes; i++) {
    
      if (playbackIndex >= sampleVector.size()) {
        playbackIndex = 0;
      }

      outputBuffer_left[i] = sampleVector.at(playbackIndex);
      outputBuffer_right[i] = sampleVector.at(playbackIndex);
      playbackIndex++;

  }

  return 0;
  
}

int loadTickSound() {
  SndfileHandle fileHandleTick("assets/metro_1.wav", SFM_READ,  SF_FORMAT_WAV | SF_FORMAT_FLOAT, 1, 44100);
  SndfileHandle fileHandleTack("assets/metro_2.wav", SFM_READ,  SF_FORMAT_WAV | SF_FORMAT_FLOAT, 1, 44100);
  
  // get the number of frames in the sample
  int sizeTick = fileHandleTick.frames();
  int sizeTack = fileHandleTack.frames();
  
  // std::cout << sizeTick << std::endl;
  // std::cout << sizeTack << std::endl;
  
  if (sizeTick == 0 || sizeTack == 0) {
    std::cout << "Problem when loading metronome sound." << std::endl;
    return -1;
  }
  
  // int channels   = fileHandleTick.channels();
  // int samplerate = fileHandleTick.samplerate();
  // 
  // std::cout << channels << std::endl;
  // std::cout << samplerate << std::endl;
  
  sampleVector.resize(sizeTick);
  // sampleVector2.resize(sizeTack);
  
  fileHandleTick.read(&sampleVector.at(0), sizeTick);
  // fileHandleTack.read(&sampleVector2.at(0), sizeTack);
  
  return 0;
}


void jack_shutdown (void *arg) {  // FIXME
  std::cout << "Jack jack_shutdown." << std::endl;
}


int main (int argc, char *argv[]) {
  // jack_client_free(client);
  client = jack_client_open("MetronomeJackClientTest", JackNullOption, 0, 0);
  std::cout << jack_get_client_name(client) << std::endl;
  // std::cout << client << std::endl;
  jack_set_process_callback(client, process_callback, 0);
  jack_activate(client);
  
  // sample_rate = jack_get_sample_rate(client);
  int sampleRate = jack_get_sample_rate( client );
  std::cout << sampleRate << std::endl;
  
  AUDIO_out_left = jack_port_register(client, "output_L", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  AUDIO_out_right = jack_port_register(client, "output_R", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  // MIDI_out = jack_port_register(client, "output", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
  
  // jack_on_shutdown(client, jack_shutdown, 0);
  
  int loadSound = loadTickSound();
  if (loadSound) {
    std::cout << "Problem when loading metronome sound." << std::endl;
    return 0;
  }
  
  jack_time_start = jack_get_time();
  std::cout << jack_time_start << std::endl;
  
  
  buildUI(argc, argv);
  
  
  while (true) {
    sleep(1);
  }
  
  /*int d = */jack_deactivate(client);
  // std::cout << d << std::endl;
  // close the client
  /*int c = */jack_client_close(client);
  // std::cout << c << std::endl;
  std::cout << "Jack closed." << std::endl;
  return 0;
  
}
