/*
 * Robot Flier
 * A.D.S. Games
 * 03/01/2016
 * Robots in space!
 */
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdexcept>

#include "constants/globals.h"
#include "engine/Locator.h"
#include "engine/assets/AssetManager.h"
#include "engine/audio/DefaultAudioService.h"
#include "engine/input/JoystickListener.h"
#include "engine/input/KeyListener.h"
#include "engine/input/MouseListener.h"
#include "engine/settings/SettingManager.h"
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

// Change game screen
void changeScene() {
  // If the scene needs to be changed
  if (Scene::nextScene != SCENE_NULL) {
    // Delete the current scene
    if (Scene::nextScene != SCENE_EXIT) {
      delete current_scene;
    }

    // Change the scene
    switch (Scene::nextScene) {
      case SCENE_INIT:
        current_scene = new Init();
        break;

      case SCENE_INTRO:
        current_scene = new Intro();
        break;

      case SCENE_MENU:
        current_scene = new Menu();
        break;

      case SCENE_GAME:
        current_scene = new Game();
        break;

      case SCENE_EXIT:
      default:
        closing = true;
        break;
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
  if (!al_init()) {
    throw std::runtime_error("Could not allegro");
  }

  // Setup window
  Locator::provideWindow<Window>();
  Locator::getWindow().setWindowSize(1600, 1200);
  Locator::getWindow().setBufferSize(800, 600);
  Locator::getWindow().setMode(DISPLAY_MODE::WINDOWED);
  Locator::getWindow().setTitle("Loading");

  // Input
  if (!al_install_keyboard()) {
    throw std::runtime_error("Could not init keyboard");
  }
  if (!al_install_mouse()) {
    throw std::runtime_error("Could not init mouse");
  }
  if (!al_install_joystick()) {
    throw std::runtime_error("Could not init joystick");
  }

  // Fonts
  if (!al_init_font_addon()) {
    throw std::runtime_error("Could not init font addon");
  }
  if (!al_init_ttf_addon()) {
    throw std::runtime_error("Could not init ttf addon");
  }

  // Graphics
  if (!al_init_image_addon()) {
    throw std::runtime_error("Could not init image addon");
  }
  if (!al_init_primitives_addon()) {
    throw std::runtime_error("Could not init primitives addon");
  }

  // Audio
  if (!al_install_audio()) {
    throw std::runtime_error("Could not init audio addon");
  }
  if (!al_init_acodec_addon()) {
    throw std::runtime_error("Could not init acodec addon");
  }
  al_reserve_samples(20);

  // Events
  event_queue = al_create_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(
                                            Locator::getWindow().getDisplay()));
  timer = al_create_timer(1.0 / UPDATES_PER_SECOND);
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_joystick_event_source());

  al_start_timer(timer);

  // Window title
  Locator::getWindow().setTitle("Robot Flier");

  // Setup service locator
  Locator::provideAudio<DefaultAudioService>();

  // Setup asset manager
  Locator::provideAssetManager<AssetManager>();

  // Setup setting manager
  Locator::provideSettings<SettingManager>();
}

// Universal update
void update() {
  // Event checking
  ALLEGRO_EVENT ev;
  al_wait_for_event(event_queue, &ev);

  // Timer
  if (ev.type == ALLEGRO_EVENT_TIMER) {
    // Change scene (if needed)
    changeScene();

    // Update listeners
    m_listener.update();
    k_listener.update();
    j_listener.update();

    // Update scene
    current_scene->update();
    current_scene->updateInternal();

    // Debug console toggle
    if (k_listener.keyPressed[ALLEGRO_KEY_F12]) {
      Locator::getSettings().set(
          "debug", !Locator::getSettings().get<bool>("debug", false));
    }
  }
  // Exit
  else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    closing = true;
  }
  // Scaling
  else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
    Locator::getWindow().resize(ev.display.width, ev.display.height);
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
    JoystickListener::joystickEnabled = (al_get_num_joysticks() > 0);
  }

  // Queue empty? Lets draw
  if (al_is_event_queue_empty(event_queue)) {
    Locator::getWindow().draw(current_scene);
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
  current_scene = new Init();

  // Loop
  while (!closing) {
    update();
  }

  return 0;
}
