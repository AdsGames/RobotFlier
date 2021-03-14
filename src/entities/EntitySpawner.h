/*
 * Entity Spawner
 * Allan Legemaate
 * Spawns entities
 * 31/10/2020
 */
#ifndef SRC_ENTITIES_ENTITYSPAWNER_H_
#define SRC_ENTITIES_ENTITYSPAWNER_H_

#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class EntitySpawner : public afk::GameObject {
 public:
  // Constructor
  EntitySpawner(afk::Scene& scene, ObjId robot_id);

  // Logic override
  void update(Uint32 delta) override;

 private:
  // Keep a ref to robot
  ObjId robot_id;
};

#endif  // SRC_ENTITIES_ENTITYSPAWNER_H_
