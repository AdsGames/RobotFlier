#include "Init.h"

#include "../constants/globals.h"

// Construct scene
void Init::start() {
  // Setup display
  display.setWindowSize(SCREEN_W, SCREEN_H);
  display.setBufferSize(SCREEN_W, SCREEN_H);
  display.setTitle("Robot Flier");

  display.setMode(afk::DisplayMode::WINDOWED);

  // Backgrounds
  assets.loadImage("background_0", "images/backgrounds/background_0.png");
  assets.loadImage("background_1", "images/backgrounds/background_1.png");
  assets.loadImage("background_2", "images/backgrounds/background_2.png");
  assets.loadImage("background_3", "images/backgrounds/background_3.png");
  assets.loadImage("intro", "images/backgrounds/intro.png");
  assets.loadImage("space", "images/backgrounds/space.png");

  // Ground overlays
  assets.loadImage("groundOverlay_dark",
                   "images/ground/groundOverlay_dark.png");
  assets.loadImage("groundOverlay_mars",
                   "images/ground/groundOverlay_mars.png");
  assets.loadImage("groundOverlay_moon",
                   "images/ground/groundOverlay_moon.png");
  assets.loadImage("groundOverlay_sun", "images/ground/groundOverlay_sun.png");

  // Ground underlays
  assets.loadImage("groundUnderlay_dark",
                   "images/ground/groundUnderlay_dark.png");
  assets.loadImage("groundUnderlay_mars",
                   "images/ground/groundUnderlay_mars.png");
  assets.loadImage("groundUnderlay_moon",
                   "images/ground/groundUnderlay_moon.png");
  assets.loadImage("groundUnderlay_sun",
                   "images/ground/groundUnderlay_sun.png");

  // Paralax
  assets.loadImage("paralax_dark", "images/ground/paralax_dark.png");
  assets.loadImage("paralax_mars", "images/ground/paralax_mars.png");
  assets.loadImage("paralax_moon", "images/ground/paralax_moon.png");
  assets.loadImage("paralax_sun", "images/ground/paralax_sun.png");

  // GUI
  assets.loadImage("controls", "images/gui/controls.png");
  assets.loadImage("credits", "images/gui/credits.png");
  assets.loadImage("debug", "images/gui/debug.png");
  assets.loadImage("helpScreen", "images/gui/helpScreen.png");
  assets.loadImage("highscores", "images/gui/highscores.png");
  assets.loadImage("highscores_table", "images/gui/highscores_table.png");
  assets.loadImage("keyboardButton", "images/gui/keyboardButton.png");
  assets.loadImage("lose", "images/gui/lose.png");
  assets.loadImage("mouse", "images/gui/mouse.png");
  assets.loadImage("mouse_rocket", "images/gui/mouse_rocket.png");
  assets.loadImage("options", "images/gui/options.png");
  assets.loadImage("pauseMenu", "images/gui/pauseMenu.png");
  assets.loadImage("start", "images/gui/start.png");
  assets.loadImage("title", "images/gui/title.png");
  assets.loadImage("ui_a", "images/gui/ui_a.png");
  assets.loadImage("ui_b", "images/gui/ui_b.png");
  assets.loadImage("ui_back", "images/gui/ui_back.png");
  assets.loadImage("ui_control_auto", "images/gui/ui_control_auto.png");
  assets.loadImage("ui_control_keyboard", "images/gui/ui_control_keyboard.png");
  assets.loadImage("ui_control_xbox", "images/gui/ui_control_xbox.png");
  assets.loadImage("ui_controls", "images/gui/ui_controls.png");
  assets.loadImage("ui_credits", "images/gui/ui_credits.png");
  assets.loadImage("ui_exit", "images/gui/ui_exit.png");
  assets.loadImage("ui_game_end", "images/gui/ui_game_end.png");
  assets.loadImage("ui_help", "images/gui/ui_help.png");
  assets.loadImage("ui_music_off", "images/gui/ui_music_off.png");
  assets.loadImage("ui_music_on", "images/gui/ui_music_on.png");
  assets.loadImage("ui_options", "images/gui/ui_options.png");
  assets.loadImage("ui_options_small", "images/gui/ui_options_small.png");
  assets.loadImage("ui_particle_off", "images/gui/ui_particle_off.png");
  assets.loadImage("ui_particle_pixel", "images/gui/ui_particle_pixel.png");
  assets.loadImage("ui_particle_square", "images/gui/ui_particle_square.png");
  assets.loadImage("ui_particle_circle", "images/gui/ui_particle_circle.png");
  assets.loadImage("ui_screenshake_high", "images/gui/ui_screenshake_high.png");
  assets.loadImage("ui_screenshake_low", "images/gui/ui_screenshake_low.png");
  assets.loadImage("ui_screenshake_medium",
                   "images/gui/ui_screenshake_medium.png");
  assets.loadImage("ui_screenshake_none", "images/gui/ui_screenshake_none.png");
  assets.loadImage("ui_screenshot_notification",
                   "images/gui/ui_screenshot_notification.png");
  assets.loadImage("ui_sound_off", "images/gui/ui_sound_off.png");
  assets.loadImage("ui_sound_on", "images/gui/ui_sound_on.png");
  assets.loadImage("ui_up", "images/gui/ui_up.png");
  assets.loadImage("ui_window_fullscreen",
                   "images/gui/ui_window_fullscreen.png");
  assets.loadImage("ui_window_windowed", "images/gui/ui_window_windowed.png");
  assets.loadImage("xbox_start", "images/gui/xbox_start.png");

  // Objects
  assets.loadImage("asteroid_christmas",
                   "images/objects/asteroid_christmas.png");
  assets.loadImage("asteroid_dark", "images/objects/asteroid_dark.png");
  assets.loadImage("asteroid_mars", "images/objects/asteroid_mars.png");
  assets.loadImage("asteroid_moon", "images/objects/asteroid_moon.png");
  assets.loadImage("asteroid_sun", "images/objects/asteroid_sun.png");
  assets.loadImage("bomb", "images/objects/bomb.png");
  assets.loadImage("bomb_christmas", "images/objects/bomb_christmas.png");
  assets.loadImage("comet", "images/objects/comet.png");
  assets.loadImage("energy", "images/objects/energy.png");
  assets.loadImage("energy_christmas", "images/objects/energy_christmas.png");
  assets.loadImage("powerMagnet", "images/objects/powerMagnet.png");
  assets.loadImage("powerMagnetFour", "images/objects/powerMagnetFour.png");
  assets.loadImage("powerMagnetThree", "images/objects/powerMagnetThree.png");
  assets.loadImage("powerMagnetTwo", "images/objects/powerMagnetTwo.png");
  assets.loadImage("powerStar", "images/objects/powerStar.png");

  // Robot
  assets.loadImage("christmas_hat", "images/robot/christmas_hat.png");
  assets.loadImage("robot", "images/robot/robot.png");
  assets.loadImage("robotDie", "images/robot/robotDie.png");
  assets.loadImage("robotfire", "images/robot/robotfire.png");
  assets.loadImage("robotInvincible", "images/robot/robotInvincible.png");
  assets.loadImage("robotInvincibleFire",
                   "images/robot/robotInvincibleFire.png");
  assets.loadImage("robotInvincibleTop", "images/robot/robotInvincibleTop.png");

  // Particles
  assets.loadImage("fuzzball", "images/particles/fuzzball.png");

  // Load streams
  assets.loadStream("death", "audio/music_death.ogg");
  assets.loadStream("in_game", "audio/music_ingame.ogg");
  assets.loadStream("mainmenu", "audio/music_mainmenu.ogg");
  assets.loadStream("mainmenu_2", "audio/music_mainmenu_2.ogg");

  // Load audio
  assets.loadAudio("asteroid", "audio/sound_asteroid.wav");
  assets.loadAudio("bomb", "audio/sound_bomb.wav");
  assets.loadAudio("flame", "audio/sound_flame.wav");
  assets.loadAudio("hitground", "audio/sound_hitground.wav");
  assets.loadAudio("magnet", "audio/sound_magnet.wav");
  assets.loadAudio("orb", "audio/sound_orb.wav");
  assets.loadAudio("snap", "audio/sound_snap.wav");
  assets.loadAudio("star", "audio/sound_star.wav");

  // Fonts
  assets.loadFont("orbitron_12", "fonts/orbitron_ttf.ttf", 12);
  assets.loadFont("orbitron_18", "fonts/orbitron_ttf.ttf", 18);
  assets.loadFont("orbitron_24", "fonts/orbitron_ttf.ttf", 24);
  assets.loadFont("orbitron_30", "fonts/orbitron_ttf.ttf", 30);
  assets.loadFont("orbitron_36", "fonts/orbitron_ttf.ttf", 36);

  // Load settings
  config.load("data/settings.dat");
  config.setAutosave(true);
}

// Update
void Init::update(Uint32 delta) {
  // Go to menu
  scene.setNextScene("intro");
}
