// This file will create the extra live class
#ifndef EXTRALIVE_H
#define EXTRALIVE_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#include "PowerUp.h"
// Creating class that inherits from PowerUp
class ExtraLive : public PowerUp {
 private:
  int AddLive;
 public:
 
 //Position of item
  ExtraLive(float pos_x, float pos_y);
  ExtraLive();
  int powerUpEffect();
 
// Game Dynamics and Data handeling
  void update();
  ~ExtraLive();
};
#endif
