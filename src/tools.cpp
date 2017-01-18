#include "tools.h"

// Conversions
// Convert int to string
std::string convertIntToString( int number){
  std::stringstream ss;
  ss << number;
  return ss.str();
}

// Convert string to int
int convertStringToInt( std::string newString){
  int result;
  std::stringstream(newString) >> result;
  return result;
}


// Scores
// Check highscores
bool check_highscore( std::string scoreCopy[][2], int newScore){
  if( newScore > atoi(scoreCopy[9][1].c_str()))
    return true;
  return false;
}

// Read High Scores
void updateScores( std::string scoreCopy[][2]){
  std::ifstream read( "data/scores.dat");
  for (int i = 0; i < 10; i++){
    for( int t = 0; t < 2; t++){
      read >> scoreCopy[i][t];
    }
  }
  read.close();
}

// Add score
void addScore( std::string scoreCopy[][2], int newScore, std::string name){
  //Update table
  updateScores( scoreCopy);

  //Prevent crashing
  if( name == "")
    name = "player";

  //Update List
  for( int i = 0; i < 10; i++){
    if( newScore > (atoi(scoreCopy[i][1].c_str()))){
      for( int t = 9; t > i; t--){
        scoreCopy[t][1] = scoreCopy[t - 1][1];
        scoreCopy[t][0] = scoreCopy[t - 1][0];
      }
      scoreCopy[i][1] = convertIntToString(newScore);
      scoreCopy[i][0] = name;
      break;
    }
  }

  //Save Scores
  std::ofstream saveFile;
  saveFile.open("data/scores.dat");

  for (int i = 0; i < 10; i++)
    for( int t = 0; t < 2; t++)
      saveFile << scoreCopy[i][t] << " ";

  saveFile.close();
}


// Iterates through the number of buttons in a joystick and returns true if any buttons are pressed
bool joy_buttonpressed(){
  bool buttonpressed = false;
  for( int i = 0; i < joy[0].num_buttons; i++)
    if( joy[0].button[i].b)buttonpressed = true;
  return buttonpressed;
}

// Iterates through the number of buttons in a joystick and returns true if any keys are pressed
bool keyboard_keypressed(){
  for( int i = 0; i < 125; i++)
    if( key[i])
      return true;
  return false;
}


// Error handling loading functions
// Checks if file exists
BITMAP *load_bitmap_ex( std::string file){
  BITMAP *temp1 = NULL;
  BITMAP *temp2 = NULL;

  // convert the sprite to current format, unless it would lose alpha information
  set_color_conversion( COLORCONV_KEEP_ALPHA);
  if ( !(temp1 = load_bitmap( file.c_str(), NULL)))
    abort_on_error( std::string("Cannot find image " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));

  // create a video bitmap of the same size and same color depth as the sprite
  //allegro_gl_set_video_bitmap_color_depth( bitmap_color_depth( temp1));
  temp2 = create_video_bitmap( temp1 -> w, temp1 -> h);
  //allegro_gl_set_video_bitmap_color_depth( -1);

  // blit a memory sprite to a video bitmap
  blit( temp1, temp2, 0, 0, 0, 0, temp1 -> w, temp1 -> h);
  destroy_bitmap( temp1);

  return temp2;
}

// Checks if file exists
SAMPLE *load_sample_ex( std::string file){
  SAMPLE *temp_sample = NULL;
  if ( !(temp_sample = load_sample( file.c_str())))
    abort_on_error( std::string("Cannot find sample " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));
  return temp_sample;
}

// Checks if file exists
SAMPLE *logg_load_ex( std::string file){
  SAMPLE *temp_sample = NULL;
  if ( !(temp_sample = logg_load( file.c_str())))
    abort_on_error( std::string("Cannot find sample " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));
  return temp_sample;
}

// A function to streamline error reporting in file loading
void abort_on_error( std::string message){
	 set_window_title("Error!");
	 if (screen != NULL){
	    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 }
	 allegro_message("%s.\n %s\n", message.c_str(), allegro_error);
	 exit(-1);
}

// Checks if file exists
FONT *load_font_ex( std::string file){
  FONT *f1, *f2, *f3, *f4, *f5, *temp_font;
  if ( (f1 = load_font( file.c_str(), NULL, NULL))){
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    temp_font = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5);
  }
  else{
    abort_on_error( std::string("Cannot find font " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));
  }
  return temp_font;
}

// Drawing hardware accelerated
void draw_sprite_hw( BITMAP *image, int x, int y){
  masked_blit( image, screen, 0, 0, x, y, image -> w, image -> h);
}


// Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest){
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber; // this doens't work on linux = lowest+int(range*rand()/(RAND_MAX + 1.0));
  randomNumber = rand() % range + lowest;
  return randomNumber;
}


// Math related functions
// Get distance between 2 points
float Get2dDistance(float x1, float y1, float x2, float y2){
	return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}

// Function to check for collision
bool collision(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2){
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1){
    return true;
  }
  return false;
}


// Fades
// Fade in
void fade_in(BITMAP* bmp_orig, int speed){
  BITMAP* bmp_buff;

  if((bmp_buff=create_bitmap(SCREEN_W,SCREEN_H))){
    int a;
    if (speed<=0)speed=16;

    for(a=0;a<256;a+=speed){
      clear(bmp_buff);
      set_trans_blender(0,0,0,a);
      draw_trans_sprite(bmp_buff,bmp_orig,0,0);
      blit(bmp_buff,screen,0,0,0,0,SCREEN_W,SCREEN_H);
      //allegro_gl_flip();
    }
    destroy_bitmap(bmp_buff);
  }
  blit(bmp_orig,screen,0,0,0,0,SCREEN_W,SCREEN_H);
  //allegro_gl_flip();
}

// Fade out
void fade_out(int speed){
  BITMAP* bmp_orig, *bmp_buff;

  if((bmp_orig=create_bitmap(SCREEN_W,SCREEN_H))){
    if((bmp_buff=create_bitmap(SCREEN_W,SCREEN_H))){
      int a;
      blit(screen,bmp_orig,0,0,0,0,SCREEN_W,SCREEN_H);
      if (speed<=0)speed=16;

      for(a=255-speed;a>0;a-=speed){
         clear(bmp_buff);
         set_trans_blender(0,0,0,a);
         draw_trans_sprite(bmp_buff,bmp_orig,0,0);
         blit(bmp_buff,screen,0,0,0,0,SCREEN_W,SCREEN_H);
         //allegro_gl_flip();
      }
    destroy_bitmap(bmp_buff);
    }
    destroy_bitmap(bmp_orig);
  }
  rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
  //allegro_gl_flip();
}
