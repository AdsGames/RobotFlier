/*
 * Robot Flier
 * A.D.S. Games
 * 03/01/2016
 * Robots in space!
 */
#include <string>
#include <time.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "state.h"
#include "init.h"
#include "intro.h"
#include "menu.h"
#include "game.h"
#include "mouseListener.h"
#include "keyListener.h"
#include "joystickListener.h"
#include "globals.h"

// Events
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;

// Mouse Updater
mouseListener m_listener;
keyListener k_listener;
joystickListener j_listener;

// Fps timer
double old_time = 0;
const float MAX_FPS = 60;
int frames_array[100];
int frame_index = 0;

// Closing or naw
bool closing = false;

// Current state object
state *currentState = nullptr;

// Functions
void clean_up();
void change_state();
void setup();
void update();
void draw();

// Delete game state and free state resources
void clean_up() {
  delete currentState;
}

// Change game screen
void change_state() {
  //If the state needs to be changed
  if( nextState != STATE_NULL ) {
    //Delete the current state
    if( nextState != STATE_EXIT ) {
      delete currentState;
    }

    //Change the state
    switch( nextState ) {
      case STATE_INIT:
        currentState = new init();
        break;

      case STATE_INTRO:
        currentState = new intro();
        break;

      case STATE_MENU:
        currentState = new menu();
        break;

      case STATE_GAME:
        currentState = new game();
        break;

      case STATE_EXIT:
        closing = true;
        break;

      default:
        currentState = new menu();
    }

    //Change the current state ID
    stateID = nextState;

    //NULL the next state ID
    nextState = STATE_NULL;
  }
}

// Sets up game
void setup() {
  // Init allegro 5
  al_init();

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
  al_reserve_samples( 20);

  // Initializing
  timer = al_create_timer(1.0 / MAX_FPS);
  display = al_create_display( SCREEN_W, SCREEN_H);

  // Events
  event_queue = al_create_event_queue();
  al_register_event_source( event_queue, al_get_display_event_source(display));
  al_register_event_source( event_queue, al_get_timer_event_source(timer));
  al_register_event_source( event_queue, al_get_keyboard_event_source());
  al_register_event_source( event_queue, al_get_joystick_event_source());

  al_clear_to_color( al_map_rgb(0, 0, 0));
  al_flip_display();
  al_start_timer(timer);

  // Creates a random number generator (based on time)
  srand( time(nullptr));

  // Game state
  stateID = STATE_NULL;
  nextState = STATE_NULL;

  // Clear settings
  for( int i = 0; i < 11; i++)
    settings[i] = false;

  // Clear frams array
  for( int i = 0; i < 100; i++)
    frames_array[i] = 0;
}

// Universal update
void update() {
  // Event checking
  ALLEGRO_EVENT ev;
  al_wait_for_event( event_queue, &ev);

  // Timer
  if( ev.type == ALLEGRO_EVENT_TIMER) {
    // Change state (if needed)
    change_state();

    // Update listeners
    k_listener.update();
    m_listener.update();
    j_listener.update();

    // Update state
    currentState -> update();

    // Debug console toggle
    if( keyListener::keyPressed[ALLEGRO_KEY_F12])
      settings[SETTING_DEBUG] = (settings[SETTING_DEBUG] + 1) % 2;
  }
  // Exit
  else if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    closing = true;
  }
  // Keyboard
  else if( ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {
    k_listener.on_event( ev.type, ev.keyboard.keycode);
  }
  // Joystick
  else if( ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP) {
    j_listener.on_event( ev.type, ev.joystick.button);
  }
  // Joystick plugged or unplugged
  else if( ev.type == ALLEGRO_EVENT_JOYSTICK_CONFIGURATION) {
    al_reconfigure_joysticks();
    joystick_enabled = (al_get_num_joysticks() > 0);
  }

  // Queue empty? Lets draw
  if( al_is_event_queue_empty(event_queue)) {
    al_clear_to_color( al_map_rgb(0, 0, 0));
    currentState -> draw();
    al_flip_display();

    // Update fps buffer
    for( int i = 99; i > 0; i--)
      frames_array[i] = frames_array[i - 1];

    frames_array[0] = (1.0 / (al_get_time() - old_time));
    old_time = al_get_time();

    int fps_total = 0;

    for( int i = 0; i < 100; i++)
      fps_total += frames_array[i];

    // FPS = average
    fps = fps_total / 100;
  }
}

// main function of program
int main( int argc, char *argv[]) {
  // Setup game
  setup();

  // Copy over the command line args
  for (int i = 1; i < argc; i++) {
    if( strcmp(argv[i], "mega") == 0)
      settings[SETTING_MEGA] = true;
    else if( strcmp(argv[i], "supershake") == 0)
      settings[SETTING_SUPERSHAKE] = true;
    else if( strcmp(argv[i], "merrychristmas") == 0)
      settings[SETTING_CHRISTMAS] = true;

    std::cout << argv[i];
  }

  //Set the current state ID
  stateID = STATE_INIT;

  //Set the current game state object
  currentState = new init();

  // Loop
  while( !closing) {
    update();
  }

  return 0;
}
