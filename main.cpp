// 2013(C) ADS Games
// Written in C++ using Allegro www.allegro.cc, Dev-C++ www.bloodshed.net, Freesound www.freesound.org, Paint.net www.getpaint.net,
// Special thanks to Allan Legemaate whom I owe my life to

#include "energy.h"
#include "asteroid.h"
#include "bomb.h"
#include "comet.h"
#include "powerup.h"
#include "particle.h"
#include "globals.h"

using namespace std;

// Game screens
#define SPLASH 0
#define MENU 1
#define TUTORIAL 2
#define GAME 3
#define EXIT 4

// Constants
// Maximum number of objects allowed onscreen at once
const int numberEnergys = 10;
const int numberBombs = 20;
const int numberAsteroids = 8;
const int numberPowers = 2;

const int screenParticles = 480000;
const int rocketParticles = 800;
const int mouseParticles = 400;
const int smokeParticles = 800;

// Close button
volatile int close_button_pressed = FALSE;

// Declare bitmaps
BITMAP* buffer;
BITMAP* intro;
BITMAP* menu;
BITMAP* start;
BITMAP* title;
BITMAP* screenshot;

// Game images
BITMAP* forceField;
BITMAP* space;
BITMAP* space2;
BITMAP* lose;
BITMAP* groundOverlay;

// GUI Images
BITMAP* mouse;
BITMAP* mouse_rocket;
BITMAP* debug;
BITMAP* options;
BITMAP* soundOn;
BITMAP* soundOff;
BITMAP* musicOn;
BITMAP* musicOff;
BITMAP* pauseMenu;
BITMAP* optionButton;
BITMAP* fullscreenToggle;
BITMAP* windowedToggle;
BITMAP* gearIcon;
BITMAP* backButton;
BITMAP* credits;
BITMAP* creditsButton;
BITMAP* resumeButton;
BITMAP* particleButton;
BITMAP* particleOffButton;
BITMAP* helpButton;
BITMAP* helpScreen;
BITMAP* highscores_table;
BITMAP* powerOff;
BITMAP* xbox_start;
BITMAP* control_xbox;
BITMAP* control_keyboard;
BITMAP* control_auto;

//Robot images
BITMAP* robot;
BITMAP* robotfire;
BITMAP* robotInvincible;
BITMAP* robotInvincibleFire;
BITMAP* robotInvincibleTop;
BITMAP* robotDie;

// Danger images
BITMAP* energyImage;
BITMAP* asteroidImage;
BITMAP* bombImage;
BITMAP* cometImage;

// Powerup Images
BITMAP* powerStar;
BITMAP* powerMagnet;
BITMAP* powerMagnetTwo;
BITMAP* powerMagnetThree;
BITMAP* powerMagnetFour;

// Declare ground bitmaps
BITMAP* ground[12];

// Declare sounds
SAMPLE* energySound;
SAMPLE* bombSound;
SAMPLE* asteroidSound;
SAMPLE* magnetSound;
SAMPLE* starSound;
SAMPLE* flame;
SAMPLE* groundSmash;
FSOUND_STREAM* ingame;
FSOUND_STREAM* menuMusic;
FSOUND_STREAM* dieAmbience;

// Declare fonts
FONT* f1;
FONT* f2;
FONT* f3;
FONT* f4;
FONT* f5;
FONT* finalFont;
FONT* arial;
FONT* arial_black;
FONT* orbitron;

// Define constistants
// You know ^^^^^^^^^^ Code::Blocks has a spell check right?
const int groundP = 13;

// Declare integers
int running;
int x_start_button;
int y_title;
int optionX;
int creditsY;
int mouseMove;
int loseCount;
int gravity, motion, speed;
int step;
int scroll1, scroll2;
int groundScroll;
int tutorialStage;
int gameScreen;
int forceFieldAppear = 10;
int control_mode;

// Declare booleans
bool mouse_rocketocket;
bool rocket;
bool startMove;
bool optionMenu;
bool fullScreen;
bool musicToggle;
bool paused;
bool alive;
bool onGround;
bool startClicked;
bool creditsMenu;
bool deadSoundSwitch;
bool tutorialAsked;
bool inTutorial;
bool mouse_down;
bool viewScores;
bool joystick_enabled;

string scores[10][2];

//Text input
string  edittext = "Player";
string::iterator iter = edittext.end();

// Declares that the void functions are there
void game();
void setup(bool first);
void changeTheme( int themeNumber);
void draw(bool toScreen);

// Structure of ground
struct ground{
  public:
    BITMAP* groundImage;
    int x;
    int y;
}groundPieces[20];

// Containers of objects
vector<energy> energys;
vector<asteroid> asteroids;
vector<bomb> bombs;
vector<comet> comets;
vector<powerup> powerups;

vector<particle> rocketPart;
vector<particle> mousePart;
vector<particle> menuPart;
vector<particle> smokePart;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 50;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

void ticker(){
  ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
  game_time++;
}
END_OF_FUNCTION(ticker)

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

//A function to streamline error reporting in file loading
void abort_on_error(const char *message){
	 set_window_title("Error!");
	 if (screen != NULL){
	    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 }
	 allegro_message("%s.\n %s\n", message, allegro_error);
	 exit(-1);
}

//Convert int to string
string convertInt(int number){
   stringstream ss;
   ss << number;
   return ss.str();
}

//Read High Scores
void updateScores(){
  ifstream read("data/scores.dat");
  for (int i = 0; i < 10; i++){
    for( int t = 0; t < 2; t++){
      read>>scores[i][t];
    }
  }
  read.close();
}

//Add score
void addScore(string name){
  //Update table
  updateScores();

  //Prevent crashing
  if(name == ""){
    name = "player";
  }

  //Update List
  for (int i = 0; i < 10; i++){
    if(score > atoi(scores[i][1].c_str())){
      for (int t = 9; t > i; t--){
        scores[t][1] = scores[t - 1][1];
        scores[t][0] = scores[t - 1][0];
      }
      scores[i][1] = convertInt(score);
      scores[i][0] = name;
      break;
    }
  }

  //Save Scores
  ofstream saveFile;
  saveFile.open("data/scores.dat");

  for (int i = 0; i < 10; i++){
    for( int t = 0; t < 2; t++){
      saveFile<<scores[i][t]<<" ";
    }
  }
  saveFile.close();
}

// Main game loop
void game(){
  // Splash screen
  if(gameScreen == SPLASH){
    fade_in(intro,8);
    rest(2000);
    if(musicToggle)
    	FSOUND_Stream_Play(0,menuMusic);
    fade_out(8);
    gameScreen = MENU;
    fade_in(menu,8);
    ticks = 0;
  }

  // Menu scripts
  if(gameScreen == MENU){
    //Menu animations
    if(x_start_button<1 && !startClicked)
      x_start_button=x_start_button+20;

    if(x_start_button>-399 && startClicked)
      x_start_button=x_start_button-20;

    if(y_title<20 && !startClicked)
      y_title=y_title+10;

    if(y_title>-119 && startClicked)
      y_title=y_title-10;

    if(creditsY>530 && !startClicked)
      creditsY=creditsY-5;

    if(creditsY<790 && startClicked)
      creditsY=creditsY+5;

    if(optionX>710 && !startClicked)
      optionX=optionX-5;

    if(optionX<790 && startClicked)
      optionX=optionX+5;


    // Start
    if(x_start_button<-399){
      if(!tutorialAsked){
        fade_out(8);
        changeTheme(0);
				FSOUND_Stream_Stop(menuMusic);
        if(musicToggle)
					FSOUND_Stream_Play(0,ingame);
        fade_in(space,8);
        gameScreen = GAME;
        ticks = 0;
      }
    }

    // Main Menu Buttons
    if(mouse_b & 1 && mouse_x>40 && mouse_x<260 && mouse_y>410 && mouse_y<510 && !optionMenu && !creditsMenu && !viewScores || joy[0].button[1].b){
      startClicked=true;
    }
    //Controlling menu with xbox controller
    if(control_mode==3 || joystick_enabled){
       if(joy[0].button[7].b){
        startClicked=true;
       }
    }
    if(mouse_b & 1 && mouse_x>600 && mouse_x<760 && mouse_y>20 && mouse_y<180 && !optionMenu && !creditsMenu){
      while(mouse_b & 1){ }
      if(viewScores){
        viewScores = false;
      }
      else{
        viewScores = true;
        updateScores();
      }
    }
    // Credits menu
    if(mouse_b & 1 && mouse_x>600 && mouse_x<690 && mouse_y>creditsY && mouse_y<creditsY+50 && !optionMenu && !viewScores){
      while(mouse_b & 1){ }
      if(creditsMenu){
        creditsMenu = false;
      }
      else{
        creditsMenu=true;
      }
    }
    // Help screen
    if(mouse_b & 1 && mouse_x > 500 && mouse_x < 570 && mouse_y > creditsY - 30 && mouse_y < creditsY + 60 && !optionMenu && !viewScores){
      fade_out(8);
			gameScreen = TUTORIAL;
			fade_in(helpScreen, 8);
    }
    // Options menu
    if(mouse_b & 1 && collision(mouse_x,mouse_x, 715, 785, mouse_y, mouse_y, 515, 585) && !viewScores && !creditsMenu){
      while(mouse_b & 1){ }
      if(optionMenu){
        optionMenu = false;
      }
      else{
        optionMenu = true;
      }
    }
    else if(mouse_b & 1 && !optionMenu){
      viewScores = false;
      creditsMenu = false;
      optionMenu = false;
    }
  }

  // Tutorial screen
  if(gameScreen == TUTORIAL){
    if(key[KEY_ENTER] || key[KEY_SPACE] || mouse_b & 1 || joy[0].button[1].b){
    	fade_out(8);
			gameScreen = MENU;
			draw(false);
			fade_in(buffer, 8);
    }
  }

  // Game screen
  if(gameScreen == GAME){
    if(!paused){
      // Update robots y position
      robotY += gravity - speed;

      // Changes speed
      motion = (score/30) + 4;

      // Add to distance travelled
      if( alive)
        robotDistance += motion;

      // Scroll ground
      if( !onGround && motion != 0){
        groundScroll -= motion;
      }
      if( groundScroll < -799)
        groundScroll = 0;

      // Scrolls background
      if( alive && motion!=0){
        scroll1--;
        scroll2--;
      }
      if( !alive && !onGround){
        scroll1--;
        scroll2--;
      }
      if( scroll1 <-799){
        scroll1 = scroll2 + 800;
      }
      if( scroll2 <-799){
        scroll2 = scroll1 + 800;
      }

      //No negative scores
      if( score < 0)
        score = 0;

      // Moving controls
      if(alive){
        //Controls movement up and down
          bool has_mr_robot_moved_yet;

          if(key[KEY_W] || key[KEY_UP] || mouse_b & 1){
            if(!has_mr_robot_moved_yet){
                has_mr_robot_moved_yet=true;
                if( game_time %2 == 0){
                    if(sound)
                        play_sample( flame, 20, 155, 1000, 0);
                }
                if( speed < 14){
                    rocket = false;
                    speed += 1;
                }
             }
          }
          if(joy[0].button[0].b && control_mode!=2){
            if(!has_mr_robot_moved_yet){
                has_mr_robot_moved_yet=true;
                if( game_time %2 == 0){
                    if(sound)
                        play_sample( flame, 20, 155, 1000, 0);
                }
                if( speed < 14){
                    rocket = false;
                    speed += 1;
                }
             }

          }
          //If no keys pressed
          if( !key[KEY_W] && !key[KEY_UP] && control_mode==2 && !mouse_b & 1 ||  !mouse_b & 1 && !key[KEY_W] && !key[KEY_UP] && !joy[0].button[0].b){
            rocket = true;
            if( speed > -14){
              speed -= 1;
            }

          }
        }


      //Die
      if( health < 1){
        alive = false;
      }

      // Lose scripts
      if( onGround){
        loseCount++;
        //Name input
        if(keypressed()){
          int  newkey   = readkey();
          char ASCII    = newkey & 0xff;
          char scancode = newkey >> 8;

          // a character key was pressed; add it to the string
          if(ASCII >= 32 && ASCII <= 126 && edittext.length() < 14 && scancode != KEY_SPACE){
            // add the new char
            iter = edittext.insert(iter, ASCII);
            // increment both the caret and the iterator
            iter++;
          }
          // some other, "special" key was pressed; handle it here
          else{
            if(scancode == KEY_DEL){
              if(iter != edittext.end()){
                iter = edittext.erase(iter);
              }
            }
            if(scancode == KEY_BACKSPACE){
              if(iter != edittext.begin()){
                 iter--;
                 iter = edittext.erase(iter);
              }
            }
            if(scancode == KEY_RIGHT){
              if(iter != edittext.end()){
                iter++;
              }
            }
            if(scancode == KEY_LEFT){
              if(iter != edittext.begin()){
                iter--;
              }
            }
            if(scancode == KEY_ENTER || joy[0].button[1].b){
              addScore(edittext);
              setup(false);
              paused = false;
              optionMenu = false;
              fade_out(8);
              FSOUND_Stream_Stop(dieAmbience);
              smokePart.clear();
              rocketPart.clear();
              if(musicToggle)
								FSOUND_Stream_Play(0,menuMusic);
              gameScreen = MENU;
              fade_in(menu,8);
              ticks = 0;
            }
          }
        }
      }
      if( !alive && !deadSoundSwitch){
        deadSoundSwitch = true;
        FSOUND_Stream_Stop( ingame);
        if(musicToggle)
					FSOUND_Stream_Play( 0, dieAmbience);
      }

      //Change theme
	    if( score == 200){
				BITMAP* white_fade = create_bitmap( 800, 600);
				rectfill( white_fade, 0, 0, 800, 600, makecol(255,255,255));
				fade_in( white_fade, 32);
				energys.clear();
				asteroids.clear();
				bombs.clear();
				comets.clear();
				powerups.clear();
				changeTheme(1);
  			score += 10;
				draw( false);
				fade_in( buffer, 32);
				game_time = old_time;
	    }
	    else if( score == 400){
				BITMAP* white_fade = create_bitmap( 800, 600);
				rectfill( white_fade, 0, 0, 800, 600, makecol(255,255,255));
				fade_in( white_fade, 32);
				energys.clear();
				asteroids.clear();
				bombs.clear();
				comets.clear();
				powerups.clear();
				changeTheme(2);
				score += 10;
				draw( false);
				fade_in( buffer, 32);
				game_time = old_time;
	    }
	    else if( score == 600){
				BITMAP* white_fade = create_bitmap( 800, 600);
				rectfill( white_fade, 0, 0, 800, 600, makecol(255,255,255));
				fade_in( white_fade, 32);
				energys.clear();
				asteroids.clear();
				bombs.clear();
				comets.clear();
				powerups.clear();
				changeTheme(3);
				score += 10;
				draw( false);
				fade_in( buffer, 32);
				game_time = old_time;
	    }

      // Dying animation
      if( robotY < 550 && !alive && !onGround){
        clear_keybuf();
        robotY += 10;
        speed = 0;
      }
      else if( robotY >= 550 && !alive){
        robotY = 550;
        onGround = true;
        clear_keybuf();
      }

      // Touching top or bottom
      if( robotY < 1 && alive){
        speed = -10;
        forceFieldAppear=0;
      }
      forceFieldAppear++;
      if( onGround && !alive && motion>0){
        motion = 0;
      }
      if( robotY > 550 && alive){
        speed = 14;
        if( !invincible){
            health -= 5;
            play_sample( groundSmash, 255, 125, 1000, 0);
         }
      }

      // Power up scripts
      if( invincibleTimer>0){
        invincibleTimer--;
        invincible = true;
      }
      else{
        invincible = false;
      }

      if( magneticTimer>0){
        magneticTimer--;
        magnetic = true;
      }
      else{
        magnetic = false;
      }

      // Energy
      // Counts up for every energy and runs script with ball number as i
      for( int i = 0; i < energys.size(); i++){
        energys.at(i).logic(motion);
        if( energys.at(i).offScreen()){
          energys.erase(energys.begin() + i);
          i--;
        }
      }
      // Energy ball spawning
      if( random(0,50) == 0){
        energy newEnergyBall( energyImage, energyImage, energySound, 800, random(30,550));
        energys.push_back( newEnergyBall);
      }

      // Asteroids
      // Counts up for every asteroid and runs script with ball number as i
      for( int i = 0; i < asteroids.size(); i++){
        asteroids.at(i).logic(motion);
        if( asteroids.at(i).offScreen()){
          asteroids.erase(asteroids.begin() + i);
          i--;
        }
      }
      // Asteroids spawning
      if( score>100){
        if( random(0,50) == 0){
          asteroid newAsteroid( asteroidImage, asteroidImage, asteroidSound, 800, random(30,550), random(4,20));
          asteroids.push_back( newAsteroid);
        }
      }

      // Bombs
      // Counts up for every bomb and runs script with ball number as i
      for(int i = 0; i < bombs.size(); i++){
        bombs.at(i).logic(motion);
        if(bombs.at(i).offScreen()){
          bombs.erase(bombs.begin() + i);
          i--;
        }
      }
      // Bomb spawning
      if(score > 200){
        if(random(0,80) == 0){
          bomb newBomb( bombImage, bombImage, bombSound, 800, random(30,550));
          bombs.push_back( newBomb);
        }
      }

      // Comets
      // Counts up for every comet and runs script with ball number as i
      for(int i = 0; i < comets.size(); i++){
        comets.at(i).logic(motion);
        if(comets.at(i).offScreen()){
          comets.erase(comets.begin() + i);
          i--;
        }
      }
      // Comets spawning
      if(score > 300){
        if(random(0,200) == 0){
          comet newComet( cometImage, cometImage, asteroidSound, 800, random(30,550));
          comets.push_back( newComet);
        }
      }

      // Powerups
      // Counts up for every powerup and runs script with ball number as i
      for(int i = 0; i < powerups.size(); i++){
        powerups.at(i).logic(motion);
        if(powerups.at(i).dead()){
          powerups.erase(powerups.begin() + i);
          i--;
        }
      }
      // Powerup spawning
      if(score > 0){
        if(random(0,3000) == 0 && score > 100){
          powerup newPowerup( powerStar, powerStar, starSound, 800, random(30,600), 500, 1, 0);
          powerups.push_back( newPowerup);
        }
        if(random(0,750) == 0 && score > 100){
          powerup newPowerup( powerMagnet, powerMagnet, magnetSound, 800, random(30,600), 500, 10, 3);
          powerups.push_back( newPowerup);
        }
        if(random(0,1000) == 0 && score > 200){
          powerup newPowerup( powerMagnetTwo, powerMagnetTwo, magnetSound, 800, random(30,600), 500, 11, 4);
          powerups.push_back( newPowerup);
        }
        if(random(0,2000) == 0 && score > 300){
          powerup newPowerup( powerMagnetThree, powerMagnetThree, magnetSound, 800, random(30,600), 500, 12, 5);
          powerups.push_back( newPowerup);
        }
        if(random(0,3000) == 0 && score > 500){
          powerup newPowerup( powerMagnetFour, powerMagnetFour, magnetSound, 800, random(30,600), 500, 13, 6);
          powerups.push_back( newPowerup);
        }
      }

      // Move the ground
      for(int i=0;i<groundP;i++){
        groundPieces[i].x -= motion;
        if(groundPieces[i].x <= -70){
          groundPieces[i].x = 840 + (groundPieces[i].x + 70);
        }
      }
      //Death smoke
      if( !particlesOn){
        smokePart.clear();
      }
      if( particlesOn && gameScreen==GAME && !alive){
        for( int i = 0; i < smokeParticles; i++){
          if( random(0,10) == 0){
            int randnum=random(0,255);
            particle newParticle(robotX+20, robotY+20, makecol(randnum,randnum,randnum), -2, 2, 0, -8, CIRCLE, 1);
            smokePart.push_back( newParticle);
          }
        }
      }
      for( int i = 0; i < smokePart.size(); i++){
        smokePart.at(i).logic();
        if( random(0,10) == 0){
          smokePart.erase( smokePart.begin() + i);
        }
      }

      // Rocket particles
      if( !particlesOn){
        rocketPart.clear();
      }
      if( particlesOn){
        if( !rocket){
          for( int i = 0; i < rocketParticles; i++){
            if( random(0,10) == 0){
              particle newParticle1( robotX + 21, robotY + 55, makecol( 255, random(0,255), 0), -3, 3, 0, 4, CIRCLE, 1);
              particle newParticle2( robotX + 52, robotY + 55, makecol( 255, random(0,255), 0), -3, 3, 0, 4, CIRCLE, 1);
              rocketPart.push_back( newParticle1);
              rocketPart.push_back( newParticle2);
            }
          }
        }
        for( int i = 0; i < rocketPart.size(); i++){
          rocketPart.at(i).logic();
          if( random(0,2) == 0){
            rocketPart.erase( rocketPart.begin() + i);
          }
        }
      }

      // Death
      if(!alive){
        FSOUND_Stream_Stop(ingame);
      }
    }

    if(key[KEY_O])gameScreen = GAME;
    if(key[KEY_I])score=score+500;
    if(key[KEY_U])score=score+50;
    if(key[KEY_Q])health=health-1;
    if(key[KEY_E])health=0;
    if(key[KEY_Y])robotDistance=robotDistance+500;
    if(key[KEY_T])score=score-2;
    if(key[KEY_R])health=100;

    // Pause loop code
    if(step > 10){
      if(key[KEY_P] || mouse_b & 2 || key[KEY_SPACE] || key[KEY_ENTER]){
        if(paused){
          optionMenu=false;
          paused=false;
          mouse_b = false;
          clear_keybuf();
          step=0;
        }
        else if( alive){
          paused = true;
          mouse_b = false;
          clear_keybuf();
          step=0;
        }
      }
    }

    // Pause Menu Scripts
    if(paused){
      if(mouse_b & 1 && collision( 220, 240, mouse_x, mouse_x, 435, 475, mouse_y, mouse_y) && !optionMenu){
        optionMenu = true;
        step = 0;
      }
      if(mouse_b & 1 && collision( 450, 540, mouse_x, mouse_x, 435, 460, mouse_y, mouse_y) && !optionMenu){
        paused = false;
        step = 0;
      }
    }


  }

  // THIS CODE WILL RUN NO MATTER THE gameScreen TOGGLE!


    //Joystick detector
    if(num_joysticks>0 && control_mode!=2)joystick_enabled=true;
    if(num_joysticks==0 || control_mode==2)joystick_enabled=false;

    // Debug console toggle
    if(key[KEY_F12] && debugMode && step > 10){
      debugMode = false;
      step = 0;
    }
    if(key[KEY_F12] && !debugMode && step > 10){
      debugMode = true;
      step = 0;
    }

	// Option Menu Scripts
  if(key[KEY_ESC]){
    while(key[KEY_ESC]){ }
    if(paused && gameScreen==GAME){
      optionMenu = false;
      paused = false;
    }else if(!paused && gameScreen==GAME){
        paused=true;
    }else if( gameScreen == TUTORIAL){
      optionMenu = false;
      viewScores = false;
    }else if(gameScreen==MENU && !optionMenu && !viewScores && !paused) gameScreen=EXIT;
    else if(gameScreen==MENU && optionMenu) optionMenu=false;
  }

  if(optionMenu){
    if(mouse_b & 1 && collision(580,630,mouse_x,mouse_x,450,500,mouse_y,mouse_y) && gameScreen == GAME){
      optionMenu = false;
    }
    if(step > 10){
      // Sound button toggle
      if(mouse_b & 1 && collision(120,200,mouse_x,mouse_x,180,260,mouse_y,mouse_y)){
        sound = !sound;
        step = 0;
      }

      // Music button toggle
      if(mouse_b & 1 && collision(280,360,mouse_x,mouse_x,180,260,mouse_y,mouse_y)){
        musicToggle = !musicToggle;
        if(musicToggle){
          if(gameScreen == GAME){
          	if(alive)
							FSOUND_Stream_Play(0,ingame);
						else
							FSOUND_Stream_Play(0,dieAmbience);
          }

          if(gameScreen != GAME)
            	FSOUND_Stream_Play(0,menuMusic);
        }
        else{
          FSOUND_Stream_Stop(ingame);
          FSOUND_Stream_Stop(dieAmbience);
          FSOUND_Stream_Stop(menuMusic);
        }
        step = 0;
      }

      // Control Toggle
      if(mouse_b & 1 && collision(120,200,mouse_x,mouse_x,290,370,mouse_y,mouse_y)){
        if(control_mode==1 && step>10){control_mode = 2; step = 0;}
        if(control_mode==2 && step>10){control_mode = 3; step = 0;}
        if(control_mode==3 && step>10){control_mode = 1; step = 0;}


      }

      // Fullscreen toggle
      if(mouse_b & 1 && collision(120,200,mouse_x,mouse_x,400,480,mouse_y,mouse_y)){
        fullScreen = !fullScreen;
        step = 0;
        if(fullScreen){
          set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, 800, 600, 0, 0);
        }
        else{
          set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
        }
      }

      // Particles toggle
      if(mouse_b & 1 && collision(280,360,mouse_x,mouse_x,400,480,mouse_y,mouse_y)){
        particlesOn = false;
        rocketPart.clear();
        mousePart.clear();
        smokePart.clear();
        step = 0;
      }

      // Power off
      if(mouse_b & 1 && collision(540,620,mouse_x,mouse_x,180,260,mouse_y,mouse_y)){
      	close_button_pressed = true;
      }
    }
  }

  // Mouse drawing routines
  if(gameScreen != GAME || optionMenu || paused){
    // Draw mouse particles
    if( !particlesOn){
      mousePart.clear();
    }
    if( particlesOn){
      if( mouse_rocketocket){
        for( int i = 0; i < mouseParticles; i++){
          if( random(0,10) == 0){
            particle newParticle( mouse_x+10, mouse_y+16, makecol(255,random(0,255),0), -2, 2, 0, 8, CIRCLE, 1);
            mousePart.push_back( newParticle);
          }
        }
      }
      for( int i = 0; i < mousePart.size(); i++){
        mousePart.at(i).logic();
        if( random(0,10) == 0){
          mousePart.erase( mousePart.begin() + i);
        }
      }
    }

    // Draw mouse
    draw_sprite( buffer, mouse, mouse_x, mouse_y);
    if( mouse_y < mouseMove){
      mouse_rocketocket = true;
    }
    else{
      mouse_rocketocket = false;
    }
    mouseMove = mouse_y;
  }


  /*// Explode screen! (almost)
  if(key[KEY_Z]){
    int iteratorX = 0;
    int iteratorY = 0;
    for(int i = 0; i < screenParticles; i++){
      if(iteratorX < 799){
        iteratorX ++;
      }
      else{
        iteratorX = 0;
        iteratorY ++;
      }
      particle newParticle( iteratorX, iteratorY, getpixel(buffer, iteratorX, iteratorY), -2, 2, -2, 2, PIXEL, 2);
      menuPart.push_back( newParticle);
    }
  }
  if(key[KEY_X]){
    for(int i = 0; i < menuPart.size(); i++){
     menuPart.at(i).logic();
    }
  }*/

  // Screenshots!
  if(key[KEY_F11]){
  	while(key[KEY_F11]){ }

  	int screenshotNumber;

  	ifstream read("screenshots/screenshot.dat");
	  read >> screenshotNumber;
  	read.close();

  	ofstream write;
	  write.open("screenshots/screenshot.dat");
	  write << screenshotNumber + 1;
	  write.close();

    save_bitmap((string("screenshots/screenshot_") + convertInt(screenshotNumber).c_str() + string(".png")).c_str(), buffer, NULL);
  }
  poll_joystick();
  step++;
}

// Draw images onto the screen
void draw( bool toScreen){
  // Splash screen
  if(gameScreen == SPLASH){

  }

  // Menu drawing
  if(gameScreen == MENU){
    //Draw back drop
    rectfill( buffer, 0, 0, 800, 600, makecol( 0, 0, 0));
    draw_sprite(buffer,menu,0,0);
    draw_sprite(buffer,start,x_start_button,400);
    if(joystick_enabled || control_mode==3)draw_sprite(buffer,xbox_start,x_start_button+225,430);
    draw_sprite(buffer,title,20,y_title);
    if(!creditsMenu)draw_sprite(buffer,helpButton,490,creditsY - 30);

    if(creditsMenu){
      draw_sprite(buffer,credits,0,0);
    }
    if(!creditsMenu)draw_sprite(buffer,creditsButton,600,creditsY);

    if(!optionMenu){
      if(!creditsMenu)draw_sprite_v_flip(buffer,optionButton,optionX,500);
    }
    else{
      if(!creditsMenu)draw_sprite(buffer,optionButton,optionX,500);
    }

    //Draw scores if neccisary
    //Seriously Allan?^^^^^^^^That's a new all-time low, dude, read a dictionary or something
    if(viewScores){
      //rectfill( buffer, 200, 50, 600, 550, makecol( 255, 255, 255));
      draw_sprite( buffer, highscores_table, 200, 50);
      textout_centre_ex(buffer, orbitron, "Highscores", 400, 75, makecol(0,0,0), -1);
      for(int i = 0; i < 10; i++){
        string name = scores[i][0];
        textout_ex(buffer, orbitron, name.c_str(), 225, (i * 40) + 120, makecol(0,0,0), -1);
        name = scores[i][1];
        textout_right_ex(buffer, orbitron, name.c_str(), 575, (i * 40) + 120, makecol(0,0,0), -1);
      }
    }
  }

  // Tutorial screen
  if(gameScreen == TUTORIAL){
  	draw_sprite( buffer, helpScreen, 0, 0);
  }

  // Game screen
  if(gameScreen == GAME){
    // Draw backgrounds and Ground Overlay
    draw_sprite( buffer, space, scroll1, 0);
    draw_sprite( buffer, space, scroll2, 0);

    // Mountain Paralax
    draw_sprite( buffer, space2, scroll1 * 2, 0);
    draw_sprite( buffer, space2, scroll1 * 2 + 800, 0);
    draw_sprite( buffer, space2, scroll2 * 2, 0);
    draw_sprite( buffer, space2, scroll2 * 2 + 800, 0);

    // Ground
    draw_sprite( buffer, groundOverlay, groundScroll, 580);
    draw_sprite( buffer, groundOverlay, groundScroll + 800, 580);

    // Draw info
    if( alive){
      // Info
      textprintf_ex( buffer, orbitron, 10, 2, makecol(255,255,255), -1, "Score:%i", score);
      rectfill( buffer, 10, 70, 10 + (health * 1.4), 65, makecol( 255 - health * 2.5, 0 + health * 2.5, 0));
      textprintf_ex( buffer, orbitron, 10, 27, makecol(255,255,255), -1, "Health:%i", health);

      // Power up timers
      if( invincibleTimer > 0){
        circlefill( buffer, 45, 105, 20, makecol(255,255,255));
        draw_sprite( buffer, powerStar, 20, 80);
        textprintf_centre_ex( buffer, arial_black, 43, 88, makecol(255,255,255), -1, "%i", invincibleTimer/5);
        textprintf_centre_ex( buffer, arial_black, 45, 90, makecol(0,0,0), -1, "%i", invincibleTimer/5);
      }
      if( magneticTimer > 0){
        circlefill( buffer, 105, 105, 20, makecol(255,255,255));
        draw_sprite( buffer, powerMagnet, 80, 80);
        textprintf_centre_ex( buffer, arial_black, 103, 88, makecol(255,255,255), -1, "%i", magneticTimer/5);
        textprintf_centre_ex( buffer, arial_black, 105, 90, makecol(0,0,0), -1, "%i", magneticTimer/5);
      }
    }

    // Draw rocket particles
    if( !particlesOn){
      if( !rocket){
        draw_sprite( buffer, robotfire, robotX, robotY);
      }
    }
    if( particlesOn){
      for( int i = 0; i < rocketPart.size(); i++){
        rocketPart.at(i).draw( buffer);
      }
    }

    for( int i = 0; i < smokePart.size(); i++){
        smokePart.at(i).draw( buffer);
      }

    // Robot Invincible
    if( !rocket && alive && invincible && particlesOn)
      draw_sprite(buffer,robotInvincible,robotX,robotY);
    if( rocket && alive && invincible)
      draw_sprite(buffer,robotInvincible,robotX,robotY);
    if( !rocket && alive && invincible && !particlesOn)
      draw_sprite(buffer,robotInvincibleFire,robotX,robotY);

    // Energy
    // Counts up for every energy and runs script with ball number as i
    for( int i = 0; i < energys.size(); i++){
      energys.at(i).draw(buffer);
    }

    // Asteroids
    // Counts up for every asteroid and runs script with ball number as i
    for( int i = 0; i < asteroids.size(); i++){
      asteroids.at(i).draw(buffer);
    }

    // Bombs
    // Counts up for every bomb and runs script with ball number as i
    for(int i = 0; i < bombs.size(); i++){
      bombs.at(i).draw(buffer);
    }

    // Comets
    // Counts up for every comets and runs script with ball number as i
    for(int i = 0; i < comets.size(); i++){
      comets.at(i).draw(buffer);
    }

    // Powerups
    // Counts up for every powerup and runs script with ball number as i
    for(int i = 0; i < powerups.size(); i++){
      powerups.at(i).draw(buffer);
    }

    // Draw robot sprite
    if( !rocket && alive && !invincible && particlesOn)
      draw_sprite(buffer,robot,robotX,robotY);
    if( rocket && alive && !invincible)
      draw_sprite(buffer,robot,robotX,robotY);
    if( !rocket && alive && !invincible && !particlesOn)
      draw_sprite(buffer,robotfire,robotX,robotY);

    // Draw the scrolling ground
    for(int i=0;i<groundP;i++){
      draw_sprite(buffer,groundPieces[i].groundImage,groundPieces[i].x,groundPieces[i].y);
    }

    // Pause Menu Scripts
    if(paused){
      if(!optionMenu && alive){
        draw_sprite(buffer,pauseMenu,130,140);
        textprintf_ex(buffer,arial,220,250,makecol(255,250,250),-1,"Distance Flown: %i ft",robotDistance/25);
        textprintf_ex(buffer,arial,220,280,makecol(255,250,250),-1,"Energy Collected: %i",energyCollected);
        textprintf_ex(buffer,arial,220,310,makecol(255,250,250),-1,"Powerups Received: %i",powerupsCollected);
        textprintf_ex(buffer,arial,220,340,makecol(255,250,250),-1,"Debris Collided: %i",debrisCollided);

        draw_sprite( buffer, gearIcon, 220, 435);
        draw_sprite( buffer, resumeButton, 450, 445);
      }
    }

    // Debug console


    // Lose scripts
    if( onGround){
      if( loseCount > 20){

        draw_sprite( buffer, lose, 170, 170);
        textprintf_ex( buffer, finalFont, 375, 375, makecol(255,255,97), -1, "%i", score);
        textprintf_ex( buffer, finalFont, 455, 405, makecol(255,255,97), -1, "%i", robotDistance/10);
      }
      //Input rectangle
      rectfill(buffer, 300, 508, 500, 552, makecol(0,0,0));
      rectfill(buffer, 302, 510, 498, 550, makecol(255,255,255));

      // output the string to the screen
      textout_ex(buffer, arial_black, edittext.c_str(), 306, 510, makecol(0,0,0), -1);

      // draw the caret
      vline(buffer, text_length(arial_black, edittext.c_str()) + 306, 512, 548, makecol(0,0,0));
    }

    // Death image
    if(!alive){
      draw_sprite(buffer,robotDie,robotX,robotY);
    }

    //Show force field
    if(forceFieldAppear<8)
      draw_sprite(buffer,forceField,0,0);

    //See through invincibility
    if(alive && invincible)
      draw_sprite(buffer,robotInvincibleTop,robotX,robotY);
  }

	// Option Menu Scripts
  if(optionMenu){
    draw_sprite(buffer,options,0,0);

    // Audio
    textprintf_ex(buffer,orbitron,110,146,makecol(255,250,250),-1,"Sounds   Music           Exit");
    if(sound)stretch_sprite(buffer,soundOn,120,180,80,80);
    if(!sound)stretch_sprite(buffer,soundOff,120,180,80,80);
    if(musicToggle)stretch_sprite(buffer,musicOn,280,180,80,80);
    if(!musicToggle)stretch_sprite(buffer,musicOff,280,180,80,80);

    // Input
    textprintf_ex(buffer,orbitron,120,260,makecol(255,250,250),-1,"Input");
    if(control_mode==1)draw_sprite(buffer,control_auto,120,295);
    if(control_mode==2)draw_sprite(buffer,control_keyboard,120,295);
    if(control_mode==3)draw_sprite(buffer,control_xbox,120,295);


    // Videoif(control_mode==2)draw_sprite(buffer,control_keyboard,120,295);
    textprintf_ex(buffer,orbitron,110,375,makecol(255,250,250),-1,"Window Particles");
    if(!fullScreen)stretch_sprite(buffer,fullscreenToggle,120,405,80,80);
    if(fullScreen)stretch_sprite(buffer,windowedToggle,120,405,80,80);
    if(particlesOn)stretch_sprite(buffer,particleButton,280,405,80,80);
    if(!particlesOn)stretch_sprite(buffer,particleOffButton,280,405,80,80);

    // Power
    stretch_sprite(buffer,powerOff,540,180,80,80);

    if(gameScreen == GAME)draw_sprite(buffer,backButton,580,450);
  }

  // Mouse drawing routines
  if(optionMenu || paused || gameScreen != GAME){
    // Draw mouse particles
    if( !particlesOn){
      if( mouse_rocketocket){
        draw_sprite(buffer,mouse_rocket,mouse_x,mouse_y);
      }
    }
    if( particlesOn){
      if(gameScreen = GAME && !paused){
        for( int i = 0; i < mousePart.size(); i++){
          mousePart.at(i).draw( buffer);
        }
      }
     }
    // Draw mouse
    draw_sprite( buffer, mouse, mouse_x, mouse_y);
  }

  /*// Explode screen! (almost)
  if(key[KEY_X]){
    for(int i = 0; i < menuPart.size(); i+=10){
      menuPart.at(i).draw(buffer);
    }
  }*/

   if(debugMode){
      draw_sprite(buffer,debug,0,0);
      textprintf_ex(buffer,font,225,5,makecol(255,250,250),-1,"Gravity:%i",gravity);
      textprintf_ex(buffer,font,5,25,makecol(255,250,250),-1,"Speed:%i",speed);
      textprintf_ex(buffer,font,105,25,makecol(255,250,250),-1,"Score:%i",score);
      textprintf_ex(buffer,font,105,35,makecol(255,250,250),-1,"Running:%i",running);
      textprintf_ex(buffer,font,105,45,makecol(255,250,250),-1,"Mouse X:%i",mouse_x);
      textprintf_ex(buffer,font,105,55,makecol(255,250,250),-1,"Mouse Y:%i",mouse_y);
      textprintf_ex(buffer,font,5,35,makecol(255,250,250),-1,"Robot X:20");
      textprintf_ex(buffer,font,5,45,makecol(255,250,250),-1,"Robot Y:%i",robotY);
      textprintf_ex(buffer,font,5,55,makecol(255,250,250),-1,"Motion:%i",motion);
      textprintf_ex(buffer,font,5,65,makecol(255,250,250),-1,"Invincible:%i",invincible);
      textprintf_ex(buffer,font,225,15,makecol(255,250,250),-1,"OptionClicked:%i",optionMenu);
      textprintf_ex(buffer,font,225,25,makecol(255,250,250),-1,"Credits:%i",creditsMenu);
      textprintf_ex(buffer,font,225,35,makecol(255,250,250),-1,"smokeParticles:%i",smokePart.size());
    }

  // Draw background and buffer
  if( toScreen == true){
	  draw_sprite(screen,buffer,0,0);
	}
}

void changeTheme( int themeNumber){
	string themeName;
	srand(time(NULL));

	if(themeNumber == 0){
		themeName = "moon";
	}
	else if(themeNumber == 1){
		themeName = "mars";
	}
	else if(themeNumber == 2){
		themeName = "sun";
	}
	else if(themeNumber == 3){
		themeName = "dark";
	}

	if (!(groundOverlay = load_bitmap((string("images/ground/groundOverlay_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/groundOverlay_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[0] = load_bitmap((string("images/ground/ground1_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground1_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[1] = load_bitmap((string("images/ground/ground2_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground2_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[2] = load_bitmap((string("images/ground/ground3_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground3_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[3] = load_bitmap((string("images/ground/ground4_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground4_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[4] = load_bitmap((string("images/ground/ground5_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground5_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[5] = load_bitmap((string("images/ground/ground6_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground6_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[6] = load_bitmap((string("images/ground/ground7_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground7_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[7] = load_bitmap((string("images/ground/ground8_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground8_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[8] = load_bitmap((string("images/ground/ground9_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground9_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[9] = load_bitmap((string("images/ground/ground10_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground10_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[10] = load_bitmap((string("images/ground/ground11_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground11_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(ground[11] = load_bitmap((string("images/ground/ground12_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/ground12_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(space2 = load_bitmap((string("images/ground/paralax_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/paralax_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }
  if (!(asteroidImage = load_bitmap((string("images/asteroid_") + themeName.c_str() + string(".png")).c_str(), NULL))){
    allegro_message((string("Cannot find image ground/asteroid_") + themeName.c_str() + string(".png\nPlease check your files and try again")).c_str());

  }


  // Setup ground pieces
  for(int i = 0; i < groundP; i++){
    groundPieces[i].x = i * 70;
    groundPieces[i].y = 530;
    groundPieces[i].groundImage = ground[random(0,11)];
  }
}

// Setup void
void setup(bool first){
	srand(time(NULL));

  // Declare integers
  gravity = 2;
  speed = 30;
  score = 0;
  running = 0;
  x_start_button = -400;
  y_title = -100;
  optionX = 800;
  creditsY = 600;
  mouseMove = 0;
  motion = 5;
  health = 100;
  loseCount = 0;
  robotDistance = 0;
  robotX = 80;
  robotY = 400;
  score = 0;

  magneticStrength = 0;
  invincibleTimer = 0;
  magneticTimer = 0;

  groundScroll = 0;
  scroll1 = 0;
  scroll2 = scroll1 + 800;

  // Decare booleans
  mouse_rocketocket = false;
  rocket = false;
  debugMode = false;
  startMove = false;
  optionMenu = false;
  paused = false;
  alive = true;
  onGround = false;
  startClicked = false;
  invincible = false;
  creditsMenu = false;
  deadSoundSwitch = false;
  magnetic = false;

  //Clears vectors for new game
  energys.clear();
  asteroids.clear();
  bombs.clear();
  comets.clear();
  powerups.clear();


  // Should execute only the first time
  if(first){
    // Ints that only need to be changed the first time
    //Sets the level to 1
    changeTheme( 0);

    //Sets the default menu values
    sound = true;
    musicToggle = true;
    fullScreen = false;
    particlesOn = true;
    control_mode=1;

     // Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex(game_time_ticker, BPS_TO_TIMER(10));

    // Close button
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);

    // Load sounds from file
    if (!(bombSound = load_sample( "audio/bombSound.wav")))
      abort_on_error("Cannot find sound bombSound.wav\nPlease check your files and try again");
    if (!(energySound = load_sample("audio/energySound.wav")))
      abort_on_error("Cannot find sound energySound.wav\nPlease check your files and try again");
    if (!(asteroidSound = load_sample( "audio/asteroidSound.wav")))
      abort_on_error("Cannot find sound asteroidSound.wav\nPlease check your files and try again");
    if (!(ingame = FSOUND_Stream_Open( "audio/ingame.mp3",2,0,0)))
      abort_on_error("Cannot find soundtrack ingame.mp3\nPlease check your files and try again");
    if (!(menuMusic = FSOUND_Stream_Open( "audio/menuMusic.mp3",2,0,0)))
      abort_on_error("Cannot find soundtrack menuMusic.mp3\nPlease check your files and try again");
    if (!(dieAmbience = FSOUND_Stream_Open( "audio/dieAmbience.mp3",2,0,0)))
      abort_on_error("Cannot find soundtrack dieAmbience.mp3\nPlease check your files and try again");
    if (!(magnetSound = load_sample( "audio/magnetSound.wav")))
      abort_on_error("Cannot find sound magnetSound.wav\nPlease check your files and try again");
    if (!(starSound = load_sample( "audio/starSound.wav")))
      abort_on_error("Cannot find sound starSound.wav\nPlease check your files and try again");
    if (!(flame = load_sample( "audio/flame.wav")))
      abort_on_error("Cannot find sound flame.wav\nPlease check your files and try again");
    if (!(groundSmash = load_sample( "audio/groundSmash.wav")))
      abort_on_error("Cannot find sound groundSmash.wav\nPlease check your files and try again");


    // Load bitmaps from file
    if (!(robot = load_bitmap("images/robot/robot.png", NULL)))
      abort_on_error("Cannot find image robot/robot.png\nPlease check your files and try again");
    if (!(robotfire = load_bitmap("images/robot/robotfire.png", NULL)))
      abort_on_error("Cannot find image robot/robotfire.png\nPlease check your files and try again");
    if (!(robotInvincible = load_bitmap("images/robot/robotInvincible.png", NULL)))
      abort_on_error("Cannot find image robot/robotInvincible.png\nPlease check your files and try again");
    if (!(robotInvincibleFire = load_bitmap("images/robot/robotInvincibleFire.png", NULL)))
      abort_on_error("Cannot find image robot/robotInvincibleFire.png\nPlease check your files and try again");
    if (!(robotDie = load_bitmap("images/robot/robotDie.png", NULL)))
      abort_on_error("Cannot find image robot/robotDie.png\nPlease check your files and try again");
    if (!(robotInvincibleTop = load_bitmap("images/robot/robotInvincibleTop.png", NULL)))
      abort_on_error("Cannot find image robotInvincibleTop.png\nPlease check your files and try again");
    if (!(menu = load_bitmap("images/backgrounds/menu.png", NULL)))
      abort_on_error("Cannot find image backgrounds/menu.png\nPlease check your files and try again");
    if (!(space = load_bitmap("images/backgrounds/space.png", NULL)))
      abort_on_error("Cannot find image backgrounds/space.png\nPlease check your files and try again");
    if (!(start = load_bitmap("images/gui/start.png", NULL)))
      abort_on_error("Cannot find image gui/start.png\nPlease check your files and try again");
    if (!(mouse = load_bitmap("images/gui/mouse.png", NULL)))
      abort_on_error("Cannot find image gui/mouse.png\nPlease check your files and try again");
    if (!(mouse_rocket = load_bitmap("images/gui/mouse_rocket.png", NULL)))
      abort_on_error("Cannot find image gui/mouse_rocket.png\nPlease check your files and try again");
    if (!(title = load_bitmap("images/gui/title.png", NULL)))
      abort_on_error("Cannot find image gui/title.png\nPlease check your files and try again");
    if (!(debug = load_bitmap("images/gui/debug.png", NULL)))
      abort_on_error("Cannot find image gui/debug.png\nPlease check your files and try again");
    if (!(options = load_bitmap("images/gui/options.png", NULL)))
      abort_on_error("Cannot find image gui/options.png\nPlease check your files and try again");
    if (!(soundOn = load_bitmap("images/gui/soundOn.png", NULL)))
      abort_on_error("Cannot find image gui/soundOn.png\nPlease check your files and try again");
    if (!(soundOff = load_bitmap("images/gui/soundOff.png", NULL)))
      abort_on_error("Cannot find image gui/soundOff.png\nPlease check your files and try again");
    if (!(musicOn = load_bitmap("images/gui/musicOn.png", NULL)))
      abort_on_error("Cannot find image gui/musicOn.png\nPlease check your files and try again");
    if (!(musicOff = load_bitmap("images/gui/musicOff.png", NULL)))
      abort_on_error("Cannot find image gui/musicOff.png\nPlease check your files and try again");
    if (!(pauseMenu = load_bitmap("images/gui/pauseMenu.png", NULL)))
      abort_on_error("Cannot find image gui/pauseMenu.png\nPlease check your files and try again");
    if (!(lose = load_bitmap("images/gui/lose.png", NULL)))
      abort_on_error("Cannot find image gui/lose.png\nPlease check your files and try again");
    if (!(optionButton = load_bitmap("images/gui/optionButton.png", NULL)))
      abort_on_error("Cannot find image gui/optionButton.png\nPlease check your files and try again");
    if (!(fullscreenToggle = load_bitmap("images/gui/fullscreenToggle.png", NULL)))
      abort_on_error("Cannot find image gui/fullscreenToggle.png\nPlease check your files and try again");
    if (!(windowedToggle = load_bitmap("images/gui/windowedToggle.png", NULL)))
      abort_on_error("Cannot find image gui/windowedToggle.png\nPlease check your files and try again");
    if (!(gearIcon = load_bitmap("images/gui/gearIcon.png", NULL)))
      abort_on_error("Cannot find image gui/gearIcon.png\nPlease check your files and try again");
    if (!(backButton = load_bitmap("images/gui/backButton.png", NULL)))
      abort_on_error("Cannot find image gui/backButton.png\nPlease check your files and try again");
    if (!(powerStar = load_bitmap("images/powerStar.png", NULL)))
      abort_on_error("Cannot find image images/powerStar.png\nPlease check your files and try again");
    if (!(credits = load_bitmap("images/gui/credits.png", NULL)))
      abort_on_error("Cannot find image gui/credits.png\nPlease check your files and try again");
    if (!(creditsButton = load_bitmap("images/gui/creditsButton.png", NULL)))
      abort_on_error("Cannot find image gui/creditsButton.png\nPlease check your files and try again");
    if (!(resumeButton = load_bitmap("images/gui/resumeButton.png", NULL)))
      abort_on_error("Cannot find image gui/resumeButton.png\nPlease check your files and try again");
    if (!(particleButton = load_bitmap("images/gui/particleButton.png", NULL)))
      abort_on_error("Cannot find image gui/particleButton.png\nPlease check your files and try again");
    if (!(particleOffButton = load_bitmap("images/gui/particleOffButton.png", NULL)))
      abort_on_error("Cannot find image gui/particleOffButton.png\nPlease check your files and try again");
    if (!(powerMagnet = load_bitmap("images/powerMagnet.png", NULL)))
      abort_on_error("Cannot find image powerMagnet.png\nPlease check your files and try again");
    if (!(powerMagnetTwo = load_bitmap("images/powerMagnetTwo.png", NULL)))
      abort_on_error("Cannot find image powerMagnetTwo.png\nPlease check your files and try again");
    if (!(powerMagnetThree = load_bitmap("images/powerMagnetThree.png", NULL)))
      abort_on_error("Cannot find image powerMagnetThree.png\nPlease check your files and try again");
    if (!(powerMagnetFour = load_bitmap("images/powerMagnetFour.png", NULL)))
      abort_on_error("Cannot find image powerMagnetFour.png\nPlease check your files and try again");
    if (!(intro = load_bitmap("images/backgrounds/intro.png", NULL)))
      abort_on_error("Cannot find image backgrounds/intro.png\nPlease check your files and try again");
    if (!(forceField = load_bitmap("images/forceField.png", NULL)))
      abort_on_error("Cannot find image images/forceField.png\nPlease check your files and try again");
    if (!(highscores_table = load_bitmap("images/gui/highscores_table.png", NULL)))
      abort_on_error("Cannot find image gui/highscores_table.png\nPlease check your files and try again");
    if (!(helpButton = load_bitmap("images/gui/helpButton.png", NULL)))
      abort_on_error("Cannot find image gui/helpButton.png\nPlease check your files and try again");
    if (!(helpScreen = load_bitmap("images/gui/helpScreen.png", NULL)))
      abort_on_error("Cannot find image gui/helpScreen.png\nPlease check your files and try again");
    if (!(powerOff = load_bitmap("images/gui/powerOff.png", NULL)))
      abort_on_error("Cannot find image gui/powerOff.png\nPlease check your files and try again");
    if (!(xbox_start = load_bitmap("images/gui/xbox_start.png", NULL)))
      abort_on_error("Cannot find image gui/xbox_start.png\nPlease check your files and try again");
    if (!(control_xbox = load_bitmap("images/gui/control_xbox.png", NULL)))
      abort_on_error("Cannot find image gui/control_xbox.png\nPlease check your files and try again");
    if (!(control_keyboard = load_bitmap("images/gui/control_keyboard.png", NULL)))
      abort_on_error("Cannot find image gui/control_keyboard.png\nPlease check your files and try again");
    if (!(control_auto = load_bitmap("images/gui/control_auto.png", NULL)))
      abort_on_error("Cannot find image gui/control_auto.png\nPlease check your files and try again");
    if (!(energyImage = load_bitmap("images/energy.png", NULL)))
      abort_on_error("Cannot find image energy.png\nPlease check your files and try again");
    if (!(bombImage = load_bitmap("images/bomb.png", NULL)))
      abort_on_error("Cannot find image bomb.png\nPlease check your files and try again");
    if (!(cometImage = load_bitmap("images/comet.png", NULL)))
      abort_on_error("Cannot find image comet.png\nPlease check your files and try again");



    // Loads fonts
    // Final Font
    f1 = load_font("fonts/finalFont.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    finalFont = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    // Arial
    f1 = load_font("fonts/arial.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    arial = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    // Arial Black
    f1 = load_font("fonts/arial_black.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    arial_black = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    // Orbitron font
    f1 = load_font("fonts/orbitron.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    orbitron = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    // Destroy temporary fonts
    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5);


    // Create buffer
    buffer = create_bitmap( 800, 600);


  }
}

//Main function
int main(){
  FSOUND_Init (44100, 32, 0);
  allegro_init();
  alpng_init();
  install_keyboard();
  install_joystick(JOY_TYPE_AUTODETECT);
  install_mouse();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");


  // Run setup function
  set_window_title("Robot Flier");
  setup(true);


  while( !close_button_pressed && gameScreen!=EXIT){
    while(ticks == 0){
      rest(1);
    }
    while(ticks > 0){
      int old_ticks = ticks;

      game();

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
    draw(true);
  }

  return 0;
}
END_OF_MAIN();



