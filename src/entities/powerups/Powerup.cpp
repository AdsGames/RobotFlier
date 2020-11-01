#include "Powerup.h"

#include "../../constants/globals.h"

// Constructor
Powerup::Powerup(Scene& scene, const float x, const float y)
    : Sprite(scene, x, y), timer_length(0) {}

void Powerup::setTimerLength(const int length) {
  timer_length = length;
}

int Powerup::getTimerLength() {
  return timer_length;
}