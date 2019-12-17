## testjack


### require
libsndfile-devel


### compile
g++ testjack.cc -o build/testjack `pkg-config jack gtkmm-2.4 --cflags --libs`


## metronome

### compile
g++ metronome.cc -o build/metronome `pkg-config jack sndfile gtkmm-2.4 --cflags --libs`



### metronome sound from
https://www.rncbc.org/drupal/node/566
