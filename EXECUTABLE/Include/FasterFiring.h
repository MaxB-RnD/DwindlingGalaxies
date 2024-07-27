// Creating file that will create the FasterFiring class
#ifndef FASTERFIRING_H
#define FASTERFIRING_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#include "PowerUp.h"
class FasterFiring : public PowerUp {
 private:
    // Initilising the function
  int FiringFaster;
 public:
    // Initilising Position and PowerUp
  FasterFiring(float pos_x, float pos_y);
  FasterFiring();
  int powerUpEffect();

    
  // Deconstructor
  void update();
  ~FasterFiring();
};
#endif
