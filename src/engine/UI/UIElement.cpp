#include "UIElement.h"

#include "../scene/Scene.h"

// Constructor
UIElement::UIElement(Scene& scene,
                     const float x,
                     const float y,
                     const int z,
                     const std::string& text,
                     const std::string& font)
    : GameObject(scene, x, y, z), visible(true), text(text) {
  setFont(font);
}

void UIElement::setVisible(const bool visible) {
  this->visible = visible;
}

void UIElement::setFont(const std::string& text) {
  this->font = scene.getAsset().getFont(text);
}

void UIElement::setText(const std::string& text) {
  this->text = text;
}

// Draw
void UIElement::draw() {}

// On click
void UIElement::setOnClick(std::function<void(void)> func) {
  this->onClick = func;
}
