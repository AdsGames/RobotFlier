#include "Powerup.h"

#include "../../constants/globals.h"
#include "../../engine/Core.h"

// Constructor
Powerup::Powerup(const Scene& scene, const int x, const int y)
    : Sprite(scene, x, y), timer_length(0) {}

void Powerup::setTimerLength(const int length) {
  timer_length = length;
}

int Powerup::getTimerLength() {
  return timer_length;
}