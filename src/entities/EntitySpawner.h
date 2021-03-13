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
  EntitySpawner(afk::Scene& scene);

  // Logic override
  void update(Uint32 delta) override;

 private:
  ObjId robot_id;
  ObjId pause_menu_id;
};

#endif  // SRC_ENTITIES_ENTITYSPAWNER_H_
