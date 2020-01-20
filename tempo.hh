#ifndef TEMPO_H
#define TEMPO_H

#include <map>
#include <string>


typedef std::pair<int, int> tempo_min_max;

const int BPM_min = 40;
const int BPM_max = 208;


static std::map<tempo_min_max, std::string> tempo = {
  { { 40, 60 }, "Largo" },
  { { 60, 66 }, "Larghetto" },
  { { 66, 76 }, "Adagio" },
  { { 76, 108 }, "Andante" },
  { { 108, 120 }, "Moderato" },
  { { 120, 168 }, "Allegro" },
  { { 168, 200 }, "Presto" },
  { { 200, 208 }, "Prestissimo" }
};


static std::string get_tempo (int bpm) {
  for (auto const& t : tempo) {
    if (bpm < t.first.second) {
      return t.second;
    }
  }
}

static double get_bpm (auto tempo_name) {
  for (auto const& t : tempo) {
    if (tempo_name == t.second) {
      return (t.first.first + t.first.second) / 2;
    }
  }
}

int get_index (auto value) {
  int i = 0;
  for (auto const& t : tempo) {
    if (value <= t.first.second) {
      return i;
    }
    i++;
  }
}

#endif // TEMPO_H