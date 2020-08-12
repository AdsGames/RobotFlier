#include "Init.h"

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../helpers/tools.h"

// Construct state
init::init() {
  // Joystick detector
  joystick_enabled = bool(al_get_num_joysticks() > 0);

  // Backgrounds
  Engine::asset_manager.loadImage("background_0",
                                  "images/backgrounds/background_0.png");
  Engine::asset_manager.loadImage("background_1",
                                  "images/backgrounds/background_1.png");
  Engine::asset_manager.loadImage("background_2",
                                  "images/backgrounds/background_2.png");
  Engine::asset_manager.loadImage("background_3",
                                  "images/backgrounds/background_3.png");
  Engine::asset_manager.loadImage("intro", "images/backgrounds/intro.png");
  Engine::asset_manager.loadImage("space", "images/backgrounds/space.png");

  // Ground overlays
  Engine::asset_manager.loadImage("groundOverlay_dark",
                                  "images/ground/groundOverlay_dark.png");
  Engine::asset_manager.loadImage("groundOverlay_mars",
                                  "images/ground/groundOverlay_mars.png");
  Engine::asset_manager.loadImage("groundOverlay_moon",
                                  "images/ground/groundOverlay_moon.png");
  Engine::asset_manager.loadImage("groundOverlay_sun",
                                  "images/ground/groundOverlay_sun.png");

  // Ground underlays
  Engine::asset_manager.loadImage("groundUnderlay_dark",
                                  "images/ground/groundUnderlay_dark.png");
  Engine::asset_manager.loadImage("groundUnderlay_mars",
                                  "images/ground/groundUnderlay_mars.png");
  Engine::asset_manager.loadImage("groundUnderlay_moon",
                                  "images/ground/groundUnderlay_moon.png");
  Engine::asset_manager.loadImage("groundUnderlay_sun",
                                  "images/ground/groundUnderlay_sun.png");

  // Paralax
  Engine::asset_manager.loadImage("paralax_dark",
                                  "images/ground/paralax_dark.png");
  Engine::asset_manager.loadImage("paralax_mars",
                                  "images/ground/paralax_mars.png");
  Engine::asset_manager.loadImage("paralax_moon",
                                  "images/ground/paralax_moon.png");
  Engine::asset_manager.loadImage("paralax_sun",
                                  "images/ground/paralax_sun.png");

  // GUI
  Engine::asset_manager.loadImage("controls", "images/gui/controls.png");
  Engine::asset_manager.loadImage("credits", "images/gui/credits.png");
  Engine::asset_manager.loadImage("debug", "images/gui/debug.png");
  Engine::asset_manager.loadImage("helpScreen", "images/gui/helpScreen.png");
  Engine::asset_manager.loadImage("highscores", "images/gui/highscores.png");
  Engine::asset_manager.loadImage("highscores_table",
                                  "images/gui/highscores_table.png");
  Engine::asset_manager.loadImage("keyboardButton",
                                  "images/gui/keyboardButton.png");
  Engine::asset_manager.loadImage("lose", "images/gui/lose.png");
  Engine::asset_manager.loadImage("mouse", "images/gui/mouse.png");
  Engine::asset_manager.loadImage("mouse_rocket",
                                  "images/gui/mouse_rocket.png");
  Engine::asset_manager.loadImage("options", "images/gui/options.png");
  Engine::asset_manager.loadImage("pauseMenu", "images/gui/pauseMenu.png");
  Engine::asset_manager.loadImage("start", "images/gui/start.png");
  Engine::asset_manager.loadImage("title", "images/gui/title.png");
  Engine::asset_manager.loadImage("ui_a", "images/gui/ui_a.png");
  Engine::asset_manager.loadImage("ui_b", "images/gui/ui_b.png");
  Engine::asset_manager.loadImage("ui_back", "images/gui/ui_back.png");
  Engine::asset_manager.loadImage("ui_control_auto",
                                  "images/gui/ui_control_auto.png");
  Engine::asset_manager.loadImage("ui_control_keyboard",
                                  "images/gui/ui_control_keyboard.png");
  Engine::asset_manager.loadImage("ui_control_xbox",
                                  "images/gui/ui_control_xbox.png");
  Engine::asset_manager.loadImage("ui_controls", "images/gui/ui_controls.png");
  Engine::asset_manager.loadImage("ui_credits", "images/gui/ui_credits.png");
  Engine::asset_manager.loadImage("ui_exit", "images/gui/ui_exit.png");
  Engine::asset_manager.loadImage("ui_game_end", "images/gui/ui_game_end.png");
  Engine::asset_manager.loadImage("ui_help", "images/gui/ui_help.png");
  Engine::asset_manager.loadImage("ui_music_off",
                                  "images/gui/ui_music_off.png");
  Engine::asset_manager.loadImage("ui_music_on", "images/gui/ui_music_on.png");
  Engine::asset_manager.loadImage("ui_options", "images/gui/ui_options.png");
  Engine::asset_manager.loadImage("ui_options_small",
                                  "images/gui/ui_options_small.png");
  Engine::asset_manager.loadImage("ui_particle_off",
                                  "images/gui/ui_particle_off.png");
  Engine::asset_manager.loadImage("ui_particle_pixel",
                                  "images/gui/ui_particle_pixel.png");
  Engine::asset_manager.loadImage("ui_particle_square",
                                  "images/gui/ui_particle_square.png");
  Engine::asset_manager.loadImage("ui_particle_circle",
                                  "images/gui/ui_particle_circle.png");
  Engine::asset_manager.loadImage("ui_screenshake_high",
                                  "images/gui/ui_screenshake_high.png");
  Engine::asset_manager.loadImage("ui_screenshake_low",
                                  "images/gui/ui_screenshake_low.png");
  Engine::asset_manager.loadImage("ui_screenshake_medium",
                                  "images/gui/ui_screenshake_medium.png");
  Engine::asset_manager.loadImage("ui_screenshake_none",
                                  "images/gui/ui_screenshake_none.png");
  Engine::asset_manager.loadImage("ui_screenshot_notification",
                                  "images/gui/ui_screenshot_notification.png");
  Engine::asset_manager.loadImage("ui_sound_off",
                                  "images/gui/ui_sound_off.png");
  Engine::asset_manager.loadImage("ui_sound_on", "images/gui/ui_sound_on.png");
  Engine::asset_manager.loadImage("ui_up", "images/gui/ui_up.png");
  Engine::asset_manager.loadImage("ui_window_fullscreen",
                                  "images/gui/ui_window_fullscreen.png");
  Engine::asset_manager.loadImage("ui_window_windowed",
                                  "images/gui/ui_window_windowed.png");
  Engine::asset_manager.loadImage("xbox_start", "images/gui/xbox_start.png");

  // Objects
  Engine::asset_manager.loadImage("asteroid_christmas",
                                  "images/objects/asteroid_christmas.png");
  Engine::asset_manager.loadImage("asteroid_dark",
                                  "images/objects/asteroid_dark.png");
  Engine::asset_manager.loadImage("asteroid_mars",
                                  "images/objects/asteroid_mars.png");
  Engine::asset_manager.loadImage("asteroid_moon",
                                  "images/objects/asteroid_moon.png");
  Engine::asset_manager.loadImage("asteroid_sun",
                                  "images/objects/asteroid_sun.png");
  Engine::asset_manager.loadImage("bomb", "images/objects/bomb.png");
  Engine::asset_manager.loadImage("bomb_christmas",
                                  "images/objects/bomb_christmas.png");
  Engine::asset_manager.loadImage("comet", "images/objects/comet.png");
  Engine::asset_manager.loadImage("energy", "images/objects/energy.png");
  Engine::asset_manager.loadImage("powerMagnet",
                                  "images/objects/powerMagnet.png");
  Engine::asset_manager.loadImage("powerMagnetFour",
                                  "images/objects/powerMagnetFour.png");
  Engine::asset_manager.loadImage("powerMagnetThree",
                                  "images/objects/powerMagnetThree.png");
  Engine::asset_manager.loadImage("powerMagnetTwo",
                                  "images/objects/powerMagnetTwo.png");
  Engine::asset_manager.loadImage("powerStar", "images/objects/powerStar.png");

  // Robot
  Engine::asset_manager.loadImage("christmas_hat",
                                  "images/robot/christmas_hat.png");
  Engine::asset_manager.loadImage("robot", "images/robot/robot.png");
  Engine::asset_manager.loadImage("robotDie", "images/robot/robotDie.png");
  Engine::asset_manager.loadImage("robotfire", "images/robot/robotfire.png");
  Engine::asset_manager.loadImage("robotInvincible",
                                  "images/robot/robotInvincible.png");
  Engine::asset_manager.loadImage("robotInvincibleFire",
                                  "images/robot/robotInvincibleFire.png");
  Engine::asset_manager.loadImage("robotInvincibleTop",
                                  "images/robot/robotInvincibleTop.png");

  // Load streams
  Engine::asset_manager.loadStream("death", "audio/music_death.ogg");
  Engine::asset_manager.loadStream("in_game", "audio/music_ingame.ogg");
  Engine::asset_manager.loadStream("mainmenu", "audio/music_mainmenu.ogg");
  Engine::asset_manager.loadStream("mainmenu_2", "audio/music_mainmenu_2.ogg");

  // Load audio
  Engine::asset_manager.loadAudio("asteroid", "audio/sound_asteroid.wav");
  Engine::asset_manager.loadAudio("bomb", "audio/sound_bomb.wav");
  Engine::asset_manager.loadAudio("flame", "audio/sound_flame.wav");
  Engine::asset_manager.loadAudio("hitground", "audio/sound_hitground.wav");
  Engine::asset_manager.loadAudio("magnet", "audio/sound_magnet.wav");
  Engine::asset_manager.loadAudio("orb", "audio/sound_orb.wav");
  Engine::asset_manager.loadAudio("snap", "audio/sound_snap.wav");
  Engine::asset_manager.loadAudio("star", "audio/sound_star.wav");

  // Fonts
  Engine::asset_manager.loadFont("orbitron_12", "fonts/orbitron_ttf.ttf", 12);
  Engine::asset_manager.loadFont("orbitron_18", "fonts/orbitron_ttf.ttf", 18);
  Engine::asset_manager.loadFont("orbitron_24", "fonts/orbitron_ttf.ttf", 24);
  Engine::asset_manager.loadFont("orbitron_30", "fonts/orbitron_ttf.ttf", 30);
  Engine::asset_manager.loadFont("orbitron_36", "fonts/orbitron_ttf.ttf", 36);

  // Load settings
  Engine::settings.load("data/settings.dat");
  Engine::settings.setAutosave(true);

  // Go to menu
  set_next_state(STATE_MENU);
}

// Destruct state
init::~init() {}

// Draw
void init::draw() {}
