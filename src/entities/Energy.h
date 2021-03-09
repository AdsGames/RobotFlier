/*
 * Energy
 * Gives the player health
 * A.D.S. Games
 */
#ifndef ENTITIES_ENERGY_H
#define ENTITIES_ENERGY_H

#include <afk/assets/Sound.h>
#include <afk/entities/Sprite.h>

class Energy : public afk::Sprite {
 public:
  // Constructor
  Energy(afk::Scene& scene, const float x, const float y);

  // Logic override
  void update(Uint32 delta) override;

  // Move towards point
  void moveTowards(const float x, const float y, const float speed);

  void onCollide(const GameObject& other) override;

 private:
  // Load assets
  void loadAssets();

  // Sound effect
  afk::Sound sound_orb;
};

#endif  // ENTITIES_ENERGY_H
