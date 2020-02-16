#ifndef METRONOME_H
#define METRONOME_H

#include <atomic>
#include <vector>

#include <sndfile.hh>

using std::vector;
using std::atomic;


class Metronome: JackEngine, AlsaEngine {
  
  public:
    
    Metronome();
    virtual ~Metronome();
    
    
  protected:
    
    void change_BPM(int val);
    
    int BPM = 80;
    int volume;   // TODO
    
    
  private:
    
    static int staticProcess(jack_nframes_t nframes, void *arg);
    int process(jack_nframes_t nframes);
    static void jack_shutdown(void *arg);
    
    int loadTickSound();
    
    vector<float> sampleVectorTick;
    vector<float> sampleVectorTack;

    float sample;

    int playbackIndex = 0;

    unsigned int cur_time = 0;
    atomic<double> nb_frames;
    double next_click = nb_frames;
    int counter = 0;
    
};

#endif // METRONOME_H