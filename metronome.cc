#include "jackengine.hh"
// #include "alsaengine.hh"

#include "metronome.hh"
#include "tempo.hh"


int Metronome::staticProcess(jack_nframes_t nframes, void *arg) {
  return static_cast<Metronome*>(arg)->process(nframes);
}

int Metronome::process(jack_nframes_t nframes) {
  
  float* outputBuffer_left = (float*) jack_port_get_buffer(AUDIO_out_left, nframes);
  float* outputBuffer_right = (float*) jack_port_get_buffer(AUDIO_out_right, nframes);
  
  
  for (int i = 0; i < (int) nframes; i++) {

    if (counter < 3) {
      if (playbackIndex < sampleVectorTick.size()) {
        sample = sampleVectorTick.at(playbackIndex);
      }
    } else {
      sample = playbackIndex < sampleVectorTack.size()
        ? sampleVectorTack.at(playbackIndex)
        : 0;
    }

    outputBuffer_left[i] = sample;
    outputBuffer_right[i] = sample;
    
    ++playbackIndex;
    ++cur_time;
    
    
    if (cur_time >= next_click) {
      
      playbackIndex = 0;
      next_click += nb_frames;
      
      counter++;
      if (counter == 4) {
        counter = 0;
      }
      
    }

  }
    
  return 0;
  
}

int Metronome::loadTickSound() {
  SndfileHandle fileHandleTick("assets/tick.wav", SFM_READ, SF_FORMAT_WAV, 1, 44100);  // sampleRate ?
  SndfileHandle fileHandleTack("assets/tack.wav", SFM_READ, SF_FORMAT_WAV, 1, 44100);
  
  int sizeTick = fileHandleTick.frames();  // 23886
  int sizeTack = fileHandleTack.frames();  // 5389
  
  if (sizeTick == 0 || sizeTack == 0) {
    return 1;
  }
  
  sampleVectorTick.resize(sizeTick);
  sampleVectorTack.resize(sizeTack);
  
  fileHandleTick.read(&sampleVectorTick.at(0), sizeTick);
  fileHandleTack.read(&sampleVectorTack.at(0), sizeTack);
  
  return 0;
}

void Metronome::jack_shutdown(void *arg) {
  std::cout << "Jack shutdown." << std::endl;
  exit(1);
}

void Metronome::change_BPM(int val) {
  nb_frames = sampleRate * 60. / val;
}


Metronome::Metronome() {
  // std::cout << client << std::endl;
  client = jack_client_open("Jack Metronome", JackNullOption, 0, 0);
  if (client == nullptr) {
    throw std::runtime_error("Can't open Jack client.");
  }
  
  jack_set_process_callback(client, staticProcess, static_cast<void*>(this));
  
  if (jack_activate(client)) {
    throw std::runtime_error("Can't activate Jack client.");
  }
  
  jack_on_shutdown(client, jack_shutdown, 0);
  
  sampleRate = jack_get_sample_rate(client);
  
  
  AUDIO_out_left = jack_port_register(client, "output_L", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  AUDIO_out_right = jack_port_register(client, "output_R", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  if (AUDIO_out_left == nullptr || AUDIO_out_right == nullptr) {
    throw std::runtime_error("Can't register output ports.");
  }
  
  if (loadTickSound()) {
    throw std::runtime_error("Problem when loading metronome sound.");
  }
  
  change_BPM(BPM);
  
}

Metronome::~Metronome() {
  jack_port_unregister(client, AUDIO_out_left);
  jack_port_unregister(client, AUDIO_out_right);
  jack_deactivate(client);
  jack_client_close(client);
}
