#ifndef DIAL_H
#define DIAL_H

using std::map;
using std::pair;

typedef pair<int, int> coor;

map<int, coor>::iterator it;


static map<int, coor> coordinates = {
  { 40, { 164, 348 } },
  { 42, { 146, 345 } },
  { 44, { 133, 338 } },
  { 46, { 121, 327 } },
  { 48, { 108, 317 } },
  { 50, { 99, 305 } },
  { 52, { 91, 289 } },
  { 54, { 83, 275 } },
  { 56, { 78, 262 } },
  { 58, { 74, 243 } },
  { 60, { 70, 228 } },
  { 63, { 69, 209 } },
  { 66, { 74, 189 } },
  { 69, { 78, 175 } },
  { 72, { 84, 158 } },
  { 76, { 93, 141 } },
  { 80, { 106, 129 } },
  { 84, { 119, 117 } },
  { 88, { 135, 107 } },
  { 92, { 153, 97 } },
  { 96, { 172, 91 } },
  { 100, { 195, 90 } },
  { 104, { 218, 93 } },
  { 108, { 241, 96 } },
  { 112, { 268, 105 } },
  { 116, { 287, 121 } },
  { 120, { 300, 135 } },
  { 126, { 309, 152 } },
  { 132, { 320, 170 } },
  { 138, { 326, 190 } },
  { 144, { 328, 211 } },
  { 152, { 331, 232 } },
  { 160, { 328, 253 } },
  { 168, { 323, 275 } },
  { 176, { 315, 292 } },
  { 184, { 303, 310 } },
  { 192, { 282, 326 } },
  { 200, { 266, 337 } },
  { 208, { 246, 346 } },
  
  { 440, { 201, 355 } }  // A440
};


static auto nearest_upper_tempo(int tempo) {
  return coordinates.lower_bound(tempo)->second;
}

static auto nearest_lower_tempo(int tempo) {
  // std::cout << tempo << std::endl;
  
  it = coordinates.lower_bound(tempo);
  // std::cout << it->first << std::endl;
  auto prev = *--it;

  return prev.second;
}

static auto get_coordinate(int tempo) {
  for (auto const &c: coordinates) {
    if (tempo == c.first) {
      return c.second;
    }
  }
  nearest_upper_tempo(tempo);
}

#endif  // DIAL_H