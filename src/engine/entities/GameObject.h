/*
 * Game Object
 * A collision object! Parent class for many others
 * Allan Legemaate
 * 03/01/2017
 */

#ifndef ENGINE_ENTITIES_GAME_OBJECT_H
#define ENGINE_ENTITIES_GAME_OBJECT_H

// ID type
using ObjId = unsigned int;

// Foreward declare
class Scene;

class GameObject {
 public:
  // Constructor
  explicit GameObject(Scene& scene,
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

  // Get size
  int getWidth() const;
  int getHeight() const;

  // Get position
  float getX() const;
  float getY() const;
  int getZ() const;

  // Sort operator
  bool operator<(const GameObject& obj) const { return (z < obj.getZ()); }

  // Get unique id
  ObjId getId() const;

 protected:
  // Current scene
  Scene& scene;

  // Position
  float x, y;
  int z;

  // Size
  int height, width;

 private:
  // Id
  ObjId id;

  // Id counter
  static ObjId index;
};

#endif  // ENGINE_ENTITIES_GAME_OBJECT_H
