#include "Powerup.h"

#include "../../constants/globals.h"
#include "../../engine/Core.h"

// Constructor
Powerup::Powerup(const int x, const int y)
    : GameObject(x, y), timer_length(0) {}

void Powerup::setTimerLength(const int length) {
  timer_length = length;
}

int Powerup::getTimerLength() {
  return timer_length;
}