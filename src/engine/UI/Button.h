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
  Button(Scene& scene,
         const int x,
         const int y,
         const int z,
         std::string text,
         std::string font);

  virtual void draw() override;
};

#endif  // ENGINE_UI_BUTTON_H
