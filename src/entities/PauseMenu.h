/*
 * Puase Menu
 * Allan Legemaate
 * In game pause menu
 * 12/08/2020
 */

#ifndef SRC_ENTITIES_PAUSEMENU_H_
#define SRC_ENTITIES_PAUSEMENU_H_

#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class PauseMenu : public afk::GameObject {
 public:
  // Constructor
  explicit PauseMenu(afk::Scene& scene);

  // Update pause menu
  void update(Uint32 delta) override;

 private:
  // Images
  ObjId lbl_stat_1_id;
  ObjId lbl_stat_2_id;
  ObjId lbl_stat_3_id;
  ObjId lbl_stat_4_id;
};

#endif  // SRC_ENTITIES_PAUSEMENU_H_
