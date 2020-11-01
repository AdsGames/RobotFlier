/*
 * Entity Spawner
 * Allan Legemaate
 * Spawns entities
 * 31/10/2020
 */
#ifndef ENTITIES_ENTITY_SPAWNER_H
#define ENTITIES_ENTITY_SPAWNER_H

#include "../engine/entities/GameObject.h"
#include "../engine/scene/Scene.h"

class EntitySpawner : public GameObject {
 public:
  // Constructor
  EntitySpawner(Scene& scene,
                const unsigned int robotId,
                const unsigned int pauseMenuId);

  // Logic override
  virtual void update() override;

 private:
  unsigned int robot_id;
  unsigned int pause_menu_id;
};

#endif  // ENTITIES_ENTITY_SPAWNER_H
