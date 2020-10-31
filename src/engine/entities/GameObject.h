/*
 * Game Object
 * A collision object! Parent class for many others
 * Allan Legemaate
 * 03/01/2017
 */

#ifndef ENGINE_ENTITIES_GAME_OBJECT_H
#define ENGINE_ENTITIES_GAME_OBJECT_H

// Foreward declare
class Scene;

class GameObject {
 public:
  // Constructor
  GameObject(const Scene& scene,
             const float x = 0.0f,
             const float y = 0.0f,
             const int z = 0);

  // Destructor
  virtual ~GameObject();

  // Updates game object
  virtual void update();

  // Draws the object to screen
  virtual void draw();

  // Is colliding with game object
  bool colliding(const GameObject& other);

  // On collide
  virtual void onCollide(const GameObject& other);

  // Has it been hit?
  bool dead() const;

  // Has it passed the screen bounds?
  bool offScreen() const;

  // Get z index
  int getZ() const;

  // Sort operator
  bool operator<(const GameObject& obj) const { return (z < obj.getZ()); }

 protected:
  // Current scene
  const Scene& scene;

  // Position
  float x, y;
  int z;

  // Size
  int height, width;

  // Dead or naw
  bool isDead;
};

#endif  // ENGINE_ENTITIES_GAME_OBJECT_H
