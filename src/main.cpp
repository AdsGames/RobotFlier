/*
 * Robot Flier
 * A.D.S. Games
 * 03/01/2016
 * Robots in space!
 */
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

#include "constants/globals.h"
#include "engine/Core.h"
#include "engine/Locator.h"
#include "engine/assets/AssetManager.h"
#include "engine/audio/DefaultAudioService.h"
#include "engine/audio/NullAudioService.h"
#include "engine/input/JoystickListener.h"
#include "engine/input/KeyListener.h"
#include "engine/input/MouseListener.h"
#include "scenes/Game.h"
#include "scenes/Init.h"
#include "scenes/Intro.h"
#include "scenes/Menu.h"

// Events
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;

const float UPDATES_PER_SECOND = 60;

// Closing or naw
bool closing = false;

// Current scene object
Scene* current_scene = nullptr;

// Input listener wrapper classes
MouseListener m_listener;
KeyListener k_listener;
JoystickListener j_listener;

// Functions
void clean_up();
void change_scene();
void setup();
void update();
void draw();

// Change game screen
void change_scene() {
  // If the scene needs to be changed
  if (Scene::nextScene != SCENE_NULL) {
    // Delete the current scene
    if (Scene::nextScene != SCENE_EXIT) {
      delete current_scene;
    }

    // Change the scene
    switch (Scene::nextScene) {
      case SCENE_INIT:
        current_scene = new init();
        break;

      case SCENE_INTRO:
        current_scene = new intro();
        break;

      case SCENE_MENU:
        current_scene = new menu();
        break;

      case SCENE_GAME:
        current_scene = new Game();
        break;

      case SCENE_EXIT:
        closing = true;
        break;

      default:
        current_scene = new menu();
    }

    // Change the current scene ID
    Scene::sceneId = Scene::nextScene;

    // NULL the next scene ID
    Scene::nextScene = SCENE_NULL;
  }
}

// Sets up game
void setup() {
  // Init allegro 5
  al_init();

  // Setup display
  Engine::window.setMode(DISPLAY_MODE::WINDOWED);
  Engine::window.setTitle("Loading");

  // Input
  al_install_keyboard();
  al_install_mouse();
  al_install_joystick();

  // Fonts
  al_init_font_addon();
  al_init_ttf_addon();

  // Graphics
  al_init_image_addon();
  al_init_primitives_addon();

  // Audio
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(20);

  // Events
  event_queue = al_create_event_queue();

  al_register_event_source(
      event_queue, al_get_display_event_source(Engine::window.getDisplay()));
  timer = al_create_timer(1.0 / UPDATES_PER_SECOND);
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_joystick_event_source());

  al_start_timer(timer);

  // Window title
  Engine::window.setTitle("Robot Flier");

  // Setup service locator
  Locator::initialize();
  Locator::provideAudio(new NullAudioService());
}

// Universal update
void update() {
  // Event checking
  ALLEGRO_EVENT ev;
  al_wait_for_event(event_queue, &ev);

  // Timer
  if (ev.type == ALLEGRO_EVENT_TIMER) {
    // Change scene (if needed)
    change_scene();

    // Update listeners
    m_listener.update();
    k_listener.update();
    j_listener.update();

    // Update scene
    current_scene->update();

    // Debug console toggle
    if (k_listener.keyPressed[ALLEGRO_KEY_F12]) {
      Engine::settings.set("debug",
                           !Engine::settings.get<bool>("debug", false));
    }
  }
  // Exit
  else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    closing = true;
  }
  // Scaling
  else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
    Engine::window.resize(ev.display.width, ev.display.height);
  }
  // Keyboard
  else if (ev.type == ALLEGRO_EVENT_KEY_DOWN ||
           ev.type == ALLEGRO_EVENT_KEY_UP) {
    k_listener.on_event(ev.type, ev.keyboard.keycode);
  }
  // Joystick
  else if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN ||
           ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP) {
    j_listener.on_event(ev.type, ev.joystick.button);
  }
  // Joystick plugged or unplugged
  else if (ev.type == ALLEGRO_EVENT_JOYSTICK_CONFIGURATION) {
    al_reconfigure_joysticks();
    joystick_enabled = (al_get_num_joysticks() > 0);
  }

  // Queue empty? Lets draw
  if (al_is_event_queue_empty(event_queue)) {
    Engine::window.draw(current_scene);
  }
}

// main function of program
int main(int argc, char** argv) {
  (void)(argc);
  (void)(argv);

  // Setup game
  setup();

  // Set the current scene ID
  Scene::sceneId = SCENE_INIT;

  // Set the current game scene object
  current_scene = new init();

  // Loop
  while (!closing) {
    update();
  }

  return 0;
}
