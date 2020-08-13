/**
 * Button
 * Danny Van Stemp and Allan Legemaate
 * UI Button
 * 11/04/2017
 **/

#ifndef ENGINE_UI_BUTTON_H
#define ENGINE_UI_BUTTON_H

#include "UIElement.h"

class Button : public UIElement {
 public:
  Button();
  Button(const int x,
         const int y,
         std::string text,
         std::string id,
         ALLEGRO_FONT* font);
  inline virtual ~Button(){};

  virtual void draw() override;
  virtual void update() override;

  virtual bool canFocus() override;
};

#endif  // ENGINE_UI_BUTTON_H
