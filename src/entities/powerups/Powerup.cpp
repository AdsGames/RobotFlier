#include "Powerup.h"

#include "../../constants/globals.h"

// Constructor
Powerup::Powerup(afk::Scene& scene, const float x, const float y, const int z)
    : Sprite(scene, x, y, z), timer_length(0) {}

void Powerup::setTimerLength(const int length) {
  timer_length = length;
}

int Powerup::getTimerLength() {
  return timer_length;
}
