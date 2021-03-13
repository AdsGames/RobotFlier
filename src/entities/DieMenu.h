/*
 * Die Menu
 * Allan Legemaate
 * In game pause menu
 * 12/08/2020
 */

#ifndef SRC_ENTITIES_DIEMENU_H_
#define SRC_ENTITIES_DIEMENU_H_

#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

#include "../entities/menu/ScoreTable.h"

class DieMenu : public afk::GameObject {
 public:
  // Constructor
  explicit DieMenu(afk::Scene& scene);

  // Update pause menu
  void update(Uint32 delta) override;

 private:
  // Score table
  ScoreTable highscores;

  // Objects
  ObjId inp_name_id;
  ObjId lbl_stat_1_id;
  ObjId lbl_stat_2_id;
  ObjId lbl_stat_3_id;
  ObjId lbl_stat_4_id;
  ObjId lbl_stat_5_id;
};

#endif  // SRC_ENTITIES_DIEMENU_H_
