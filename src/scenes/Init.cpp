#include "Init.h"

#include "../constants/globals.h"

// Construct scene
Init::Init() {
  // Joystick detector
  joystick_enabled = bool(al_get_num_joysticks() > 0);

  // Backgrounds
  this->getAsset().loadImage("background_0",
                             "images/backgrounds/background_0.png");
  this->getAsset().loadImage("background_1",
                             "images/backgrounds/background_1.png");
  this->getAsset().loadImage("background_2",
                             "images/backgrounds/background_2.png");
  this->getAsset().loadImage("background_3",
                             "images/backgrounds/background_3.png");
  this->getAsset().loadImage("intro", "images/backgrounds/intro.png");
  this->getAsset().loadImage("space", "images/backgrounds/space.png");

  // Ground overlays
  this->getAsset().loadImage("groundOverlay_dark",
                             "images/ground/groundOverlay_dark.png");
  this->getAsset().loadImage("groundOverlay_mars",
                             "images/ground/groundOverlay_mars.png");
  this->getAsset().loadImage("groundOverlay_moon",
                             "images/ground/groundOverlay_moon.png");
  this->getAsset().loadImage("groundOverlay_sun",
                             "images/ground/groundOverlay_sun.png");

  // Ground underlays
  this->getAsset().loadImage("groundUnderlay_dark",
                             "images/ground/groundUnderlay_dark.png");
  this->getAsset().loadImage("groundUnderlay_mars",
                             "images/ground/groundUnderlay_mars.png");
  this->getAsset().loadImage("groundUnderlay_moon",
                             "images/ground/groundUnderlay_moon.png");
  this->getAsset().loadImage("groundUnderlay_sun",
                             "images/ground/groundUnderlay_sun.png");

  // Paralax
  this->getAsset().loadImage("paralax_dark", "images/ground/paralax_dark.png");
  this->getAsset().loadImage("paralax_mars", "images/ground/paralax_mars.png");
  this->getAsset().loadImage("paralax_moon", "images/ground/paralax_moon.png");
  this->getAsset().loadImage("paralax_sun", "images/ground/paralax_sun.png");

  // GUI
  this->getAsset().loadImage("controls", "images/gui/controls.png");
  this->getAsset().loadImage("credits", "images/gui/credits.png");
  this->getAsset().loadImage("debug", "images/gui/debug.png");
  this->getAsset().loadImage("helpScreen", "images/gui/helpScreen.png");
  this->getAsset().loadImage("highscores", "images/gui/highscores.png");
  this->getAsset().loadImage("highscores_table",
                             "images/gui/highscores_table.png");
  this->getAsset().loadImage("keyboardButton", "images/gui/keyboardButton.png");
  this->getAsset().loadImage("lose", "images/gui/lose.png");
  this->getAsset().loadImage("mouse", "images/gui/mouse.png");
  this->getAsset().loadImage("mouse_rocket", "images/gui/mouse_rocket.png");
  this->getAsset().loadImage("options", "images/gui/options.png");
  this->getAsset().loadImage("pauseMenu", "images/gui/pauseMenu.png");
  this->getAsset().loadImage("start", "images/gui/start.png");
  this->getAsset().loadImage("title", "images/gui/title.png");
  this->getAsset().loadImage("ui_a", "images/gui/ui_a.png");
  this->getAsset().loadImage("ui_b", "images/gui/ui_b.png");
  this->getAsset().loadImage("ui_back", "images/gui/ui_back.png");
  this->getAsset().loadImage("ui_control_auto",
                             "images/gui/ui_control_auto.png");
  this->getAsset().loadImage("ui_control_keyboard",
                             "images/gui/ui_control_keyboard.png");
  this->getAsset().loadImage("ui_control_xbox",
                             "images/gui/ui_control_xbox.png");
  this->getAsset().loadImage("ui_controls", "images/gui/ui_controls.png");
  this->getAsset().loadImage("ui_credits", "images/gui/ui_credits.png");
  this->getAsset().loadImage("ui_exit", "images/gui/ui_exit.png");
  this->getAsset().loadImage("ui_game_end", "images/gui/ui_game_end.png");
  this->getAsset().loadImage("ui_help", "images/gui/ui_help.png");
  this->getAsset().loadImage("ui_music_off", "images/gui/ui_music_off.png");
  this->getAsset().loadImage("ui_music_on", "images/gui/ui_music_on.png");
  this->getAsset().loadImage("ui_options", "images/gui/ui_options.png");
  this->getAsset().loadImage("ui_options_small",
                             "images/gui/ui_options_small.png");
  this->getAsset().loadImage("ui_particle_off",
                             "images/gui/ui_particle_off.png");
  this->getAsset().loadImage("ui_particle_pixel",
                             "images/gui/ui_particle_pixel.png");
  this->getAsset().loadImage("ui_particle_square",
                             "images/gui/ui_particle_square.png");
  this->getAsset().loadImage("ui_particle_circle",
                             "images/gui/ui_particle_circle.png");
  this->getAsset().loadImage("ui_screenshake_high",
                             "images/gui/ui_screenshake_high.png");
  this->getAsset().loadImage("ui_screenshake_low",
                             "images/gui/ui_screenshake_low.png");
  this->getAsset().loadImage("ui_screenshake_medium",
                             "images/gui/ui_screenshake_medium.png");
  this->getAsset().loadImage("ui_screenshake_none",
                             "images/gui/ui_screenshake_none.png");
  this->getAsset().loadImage("ui_screenshot_notification",
                             "images/gui/ui_screenshot_notification.png");
  this->getAsset().loadImage("ui_sound_off", "images/gui/ui_sound_off.png");
  this->getAsset().loadImage("ui_sound_on", "images/gui/ui_sound_on.png");
  this->getAsset().loadImage("ui_up", "images/gui/ui_up.png");
  this->getAsset().loadImage("ui_window_fullscreen",
                             "images/gui/ui_window_fullscreen.png");
  this->getAsset().loadImage("ui_window_windowed",
                             "images/gui/ui_window_windowed.png");
  this->getAsset().loadImage("xbox_start", "images/gui/xbox_start.png");

  // Objects
  this->getAsset().loadImage("asteroid_christmas",
                             "images/objects/asteroid_christmas.png");
  this->getAsset().loadImage("asteroid_dark",
                             "images/objects/asteroid_dark.png");
  this->getAsset().loadImage("asteroid_mars",
                             "images/objects/asteroid_mars.png");
  this->getAsset().loadImage("asteroid_moon",
                             "images/objects/asteroid_moon.png");
  this->getAsset().loadImage("asteroid_sun", "images/objects/asteroid_sun.png");
  this->getAsset().loadImage("bomb", "images/objects/bomb.png");
  this->getAsset().loadImage("bomb_christmas",
                             "images/objects/bomb_christmas.png");
  this->getAsset().loadImage("comet", "images/objects/comet.png");
  this->getAsset().loadImage("energy", "images/objects/energy.png");
  this->getAsset().loadImage("powerMagnet", "images/objects/powerMagnet.png");
  this->getAsset().loadImage("powerMagnetFour",
                             "images/objects/powerMagnetFour.png");
  this->getAsset().loadImage("powerMagnetThree",
                             "images/objects/powerMagnetThree.png");
  this->getAsset().loadImage("powerMagnetTwo",
                             "images/objects/powerMagnetTwo.png");
  this->getAsset().loadImage("powerStar", "images/objects/powerStar.png");

  // Robot
  this->getAsset().loadImage("christmas_hat", "images/robot/christmas_hat.png");
  this->getAsset().loadImage("robot", "images/robot/robot.png");
  this->getAsset().loadImage("robotDie", "images/robot/robotDie.png");
  this->getAsset().loadImage("robotfire", "images/robot/robotfire.png");
  this->getAsset().loadImage("robotInvincible",
                             "images/robot/robotInvincible.png");
  this->getAsset().loadImage("robotInvincibleFire",
                             "images/robot/robotInvincibleFire.png");
  this->getAsset().loadImage("robotInvincibleTop",
                             "images/robot/robotInvincibleTop.png");

  // Load streams
  this->getAsset().loadStream("death", "audio/music_death.ogg");
  this->getAsset().loadStream("in_game", "audio/music_ingame.ogg");
  this->getAsset().loadStream("mainmenu", "audio/music_mainmenu.ogg");
  this->getAsset().loadStream("mainmenu_2", "audio/music_mainmenu_2.ogg");

  // Load audio
  this->getAsset().loadAudio("asteroid", "audio/sound_asteroid.wav");
  this->getAsset().loadAudio("bomb", "audio/sound_bomb.wav");
  this->getAsset().loadAudio("flame", "audio/sound_flame.wav");
  this->getAsset().loadAudio("hitground", "audio/sound_hitground.wav");
  this->getAsset().loadAudio("magnet", "audio/sound_magnet.wav");
  this->getAsset().loadAudio("orb", "audio/sound_orb.wav");
  this->getAsset().loadAudio("snap", "audio/sound_snap.wav");
  this->getAsset().loadAudio("star", "audio/sound_star.wav");

  // Fonts
  this->getAsset().loadFont("orbitron_12", "fonts/orbitron_ttf.ttf", 12);
  this->getAsset().loadFont("orbitron_18", "fonts/orbitron_ttf.ttf", 18);
  this->getAsset().loadFont("orbitron_24", "fonts/orbitron_ttf.ttf", 24);
  this->getAsset().loadFont("orbitron_30", "fonts/orbitron_ttf.ttf", 30);
  this->getAsset().loadFont("orbitron_36", "fonts/orbitron_ttf.ttf", 36);

  // Load settings
  this->getSettings().load("data/settings.dat");
  this->getSettings().setAutosave(true);

  // Go to menu
  Scene::setNextScene(SCENE_INTRO);
}

// Destruct scene
Init::~Init() {}

// Draw
void Init::draw() {}
