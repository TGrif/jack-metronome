## metronome


### require
jack
gtkmm 3
libsndfile-devel



### compile
g++ main.cc -o build/metronome `pkg-config jack sndfile gtkmm-3.0 --cflags --libs`



### metronome sound from
https://www.rncbc.org/drupal/node/566


### inspired by
https://github.com/harryhaaren/openAudioProgrammingTutorials/tree/master/loopedSample
https://github.com/jmage619/jmetro
