/*
 * Energy
 * Gives the player health
 * A.D.S. Games
 */
#ifndef SRC_ENTITIES_ENERGY_H_
#define SRC_ENTITIES_ENERGY_H_

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
};

#endif  // SRC_ENTITIES_ENERGY_H_
