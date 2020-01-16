#include "jackengine.hh"
#include "metronome.hh"


// typedef jack_default_audio_sample_t sample_t;


int Metronome::staticProcess(jack_nframes_t nframes, void *arg)
{
  return static_cast<Metronome*>(arg)->process(nframes);
}

int Metronome::process(jack_nframes_t nframes) {
  
  float* outputBuffer_left = (float*) jack_port_get_buffer(AUDIO_out_left, nframes);
  float* outputBuffer_right = (float*) jack_port_get_buffer(AUDIO_out_right, nframes);

  
  // std::cout << jack_time_to_frames(client, nframes) << std::endl;
  // std::cout << (sizeof(sample_t) * nframes) << std::endl;
    
    
    for (int i = 0; i < (int) nframes; i++) {

      if (counter < 3) {
        if (playbackIndex < sampleVector.size()) {
          sample = sampleVector.at(playbackIndex);
        }
      } else {
        if (playbackIndex < sampleVector2.size()) {
          sample = sampleVector2.at(playbackIndex);
        } else {
          sample = 0;
        }
      }

      outputBuffer_left[i] = sample;
      outputBuffer_right[i] = sample;
      
      ++playbackIndex;
      ++cur_time;
      
      
      if (cur_time >= next_click) {
        // std::cout << (counter < 3 ? "tic" : "tac") << std::endl;
        
        playbackIndex = 0;
        next_click += dt;
        
        counter++;
        if (counter == 4) counter = 0;
        
      }

    }
    
  return 0;
  
}

int Metronome::loadTickSound() {
  SndfileHandle fileHandleTick("assets/metro_1.wav", SFM_READ,  SF_FORMAT_WAV | SF_FORMAT_FLOAT, 1, 44100);
  SndfileHandle fileHandleTack("assets/metro_2.wav", SFM_READ,  SF_FORMAT_WAV | SF_FORMAT_FLOAT, 1, 44100);
  
  // get the number of frames in the sample
  int sizeTick = fileHandleTick.frames();
  int sizeTack = fileHandleTack.frames();

  // std::cout << sizeTick << std::endl;  // 23886
  // std::cout << sizeTack << std::endl;  // 5389
  
  if (sizeTick == 0 || sizeTack == 0) {
    std::cout << "Problem when loading metronome sound." << std::endl;
    return -1;
  }
  
  // int channels   = fileHandleTick.channels();
  // int samplerateTick = fileHandleTick.samplerate();
  // int samplerateTack = fileHandleTack.samplerate();
  
  // std::cout << channels << std::endl;
  // std::cout << samplerateTick << std::endl;
  // std::cout << samplerateTack << std::endl;
  
  sampleVector.resize(sizeTick);
  sampleVector2.resize(sizeTack);
  
  fileHandleTick.read(&sampleVector.at(0), sizeTick);
  fileHandleTack.read(&sampleVector2.at(0), sizeTack);
  
  return 0;
}


void Metronome::jack_shutdown (void *arg) {  // FIXME
  // jack_deactivate(client);
  // jack_client_close(client);
  std::cout << "Jack jack_shutdown." << std::endl;
  exit(1);
}

Metronome::Metronome() {

  // jack_client_free(client);
  
  client = jack_client_open("Jack Metronome", JackNullOption, 0, 0);
  // std::cout << jack_get_client_name(client) << std::endl;
  
  jack_set_process_callback(client, staticProcess, static_cast<void*>(this));
  // jack_set_process_callback(client, process_callback, 0);
  jack_activate(client);
  
  jack_on_shutdown(client, jack_shutdown, 0);
  
  sampleRate = jack_get_sample_rate(client);
  // std::cout << sampleRate << std::endl;
  
  AUDIO_out_left = jack_port_register(client, "output_L", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  AUDIO_out_right = jack_port_register(client, "output_R", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  
  
  if (loadTickSound()) {
    std::cout << "Problem when loading metronome sound." << std::endl;
    // return 0;
    return;
  }
  
  
  dt = sampleRate * 60. / BPM;
  next_click = dt;
  
  // jack_time_start = jack_get_time();
  // std::cout << jack_time_start << std::endl;
  
  
  // std::cout << "ui" << std::endl;
  /*
  while (true) {
    sleep(1);
  }
  
  jack_deactivate(client);
  jack_client_close(client);
  
  std::cout << "Jack closed." << std::endl;*/
  // return 0;
  
}

Metronome::~Metronome() {
  // noop
}
