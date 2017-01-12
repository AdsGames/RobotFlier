/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#ifndef MENU_H
#define MENU_H

#define MINISTATE_MENU 0
#define MINISTATE_TUTORIAL 1
#define MINISTATE_CREDITS 2
#define MINISTATE_OPTIONS 3
#define MINISTATE_CONTROLS 4
#define MINISTATE_SCORES 5

#include "state.h"
#include "globals.h"
#include "particle.h"
#include "mouseListener.h"

class menu : public state{
  public:
    // Construct/deconstruct
    menu();
    ~menu();

    // Override parent
    void update();
    void draw();

  protected:

  private:
    // Vars
    int animation_start_x;
    int animation_title_y;
    int animation_credits_y;

    int mouseMove;
    int mini_screen;
    bool startMove;
    bool startClicked;
    bool mouse_rocket_up;
    bool rocket;

    // Particles
    vector <particle> mousePart;
    vector <particle> menuPart;

    // Images
    BITMAP *buffer;

    // Screens
    BITMAP *img_menu;
    BITMAP *options;
    BITMAP *helpScreen;
    BITMAP *controls;
    BITMAP *credits;
    BITMAP *highscores_table;

    // Buttons
    BITMAP *start;
    BITMAP *title;

    // Mouse
    BITMAP *mouse;
    BITMAP *mouse_rocket;

    // Start button for xbox control
    BITMAP *xbox_start;

    // Options menu
    BITMAP *ui_sound[2];
    BITMAP *ui_music[2];
    BITMAP *ui_screenshake[4];
    BITMAP *ui_window[2];
    BITMAP *ui_particle[4];
    BITMAP *ui_control[3];

    BITMAP *ui_options;
    BITMAP *ui_options_small;
    BITMAP *ui_back;
    BITMAP *ui_credits;
    BITMAP *ui_exit;
    BITMAP *ui_help;
    BITMAP *ui_screenshot_notification;
    BITMAP *ui_controls;
};

#endif // MENU_H
