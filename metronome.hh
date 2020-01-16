#ifndef METRONOME_H
#define METRONOME_H

#include <atomic>
#include <vector>

#include <sndfile.hh>


class Metronome: JackEngine {
  
  public:
    
    Metronome();
    virtual ~Metronome();


  private:
    
    static int staticProcess(jack_nframes_t nframes, void *arg);
    int process(jack_nframes_t nframes);
    
    int loadTickSound();
    static void jack_shutdown (void *arg);
    
    
    std::vector<float> sampleVector;
    std::vector<float> sampleVector2;

    float sample;

    int playbackIndex = 0;

    int BPM = 80;

    std::atomic<double> dt;  // tempo ?
    unsigned int cur_time = 0;
    double next_click;
    int counter = 0;
    
};

#endif // METRONOME_H