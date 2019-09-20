/*
 * Debris
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef DEBRIE_H
#define DEBRIE_H

#include "GameObject.h"

class Debris : public GameObject {
  public:
    // Constructor
    Debris(
      ALLEGRO_BITMAP *sprite,
      ALLEGRO_SAMPLE *sound,
      const int x,
      const int y,
      const int damage,
      const float motionMultiplier = 1.0f,
      const float acceleration = 0.0f,
      const int size = -1
    );

    // Logic override
    void logic(const int motion, Robot *robot);
  private:
    // Motion multiplier
    float motionMultiplier;
    float acceleration;

    // Sound
    ALLEGRO_SAMPLE *sound;
};

#endif
