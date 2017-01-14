/*
 * Robot Flier
 * A.D.S. Games
 * 03/01/2016
 * Robots in space!
 */
#include <allegro.h>
#include <alpng.h>
#include <logg.h>
#include <string>
#include <time.h>

#include "state.h"
#include "init.h"
#include "intro.h"
#include "menu.h"
#include "game.h"
#include "mouseListener.h"
#include "keyListener.h"

// FPS System
volatile int ticks = 0;
int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

// Mouse Updater
mouseListener m_listener;
keyListener k_listener;

void ticker(){
  ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
  game_time++;
}
END_OF_FUNCTION(ticker)

// Current state object
state *currentState = NULL;

// Delete game state and free state resources
void clean_up(){
  delete currentState;
}

// Close button handler
volatile int close_button_pressed = FALSE;
void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)


// Change game screen
void change_state(){
  //If the state needs to be changed
  if( nextState != STATE_NULL ){
    //Delete the current state
    if( nextState != STATE_EXIT ){
      delete currentState;
    }

    //Change the state
    switch( nextState ){
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
        close_button_pressed = true;
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
void setup(){
  // Initializing
  allegro_init();
  alpng_init();
  install_keyboard();
  install_mouse();
  install_timer();
  install_joystick(JOY_TYPE_AUTODETECT);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_color_depth(32);

  // Creates a random number generator (based on time)
  srand( time(NULL));

  // Setup for FPS system
  LOCK_VARIABLE(ticks);
  LOCK_FUNCTION(ticker);
  install_int_ex( ticker, BPS_TO_TIMER(updates_per_second));

  LOCK_VARIABLE(game_time);
  LOCK_FUNCTION(game_time_ticker);
  install_int_ex( game_time_ticker, BPS_TO_TIMER(10));

  // Close button
  LOCK_FUNCTION(close_button_handler);
  set_close_button_callback(close_button_handler);

  // Game state
  stateID = STATE_NULL;
  nextState = STATE_NULL;

  // Clear settings
  for( int i = 0; i < 11; i++){
    settings[i] = false;
  }
}

// Universal update
void update(){
  // Update mouse listener vars
  m_listener.update();
  k_listener.update();

  // Debug console toggle
  if( keyListener::keyPressed[KEY_F12])
    settings[SETTING_DEBUG] = (settings[SETTING_DEBUG] + 1) % 2;
}

// main function of program
int main( int argc, char* argv[]){
  // Setup game
  setup();

  // Copy over the command line args
  for (int i = 1; i < argc; i++){
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

  // Handles exit
  while(!close_button_pressed){
    // Runs FPS system
    while(ticks == 0){
      rest(1);
    }
    while(ticks > 0){
      int old_ticks = ticks;
      // Check for state change
      change_state();

      // Update always
      currentState -> update();

      // Update
      update();

      ticks--;
      if(old_ticks <= ticks){
        break;
      }
    }
    if(game_time - old_time >= 10){
      fps = frames_done;
      frames_done = 0;
      old_time = game_time;
    }
    // Update every set amount of frames
    currentState -> draw();
  }

  return 0;
}
END_OF_MAIN();
