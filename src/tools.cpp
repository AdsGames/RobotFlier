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

// Error handling loading functions
// Checks if file exists
ALLEGRO_BITMAP *load_bitmap_ex( std::string file){
  ALLEGRO_BITMAP *temp_image = NULL;
  if( !(temp_image = al_load_bitmap( file.c_str())))
    abort_on_error( std::string("Cannot find image " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));
  return temp_image;
}

// Checks if file exists
ALLEGRO_SAMPLE *load_sample_ex( std::string file){
  ALLEGRO_SAMPLE *temp_sample = NULL;
  if( !(temp_sample = al_load_sample( file.c_str())))
    abort_on_error( std::string("Cannot find sample " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));
  return temp_sample;
}

// A function to streamline error reporting in file loading
void abort_on_error( std::string message){
  al_show_native_message_box( NULL, "Error", "Warning", "File not found!", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
	 //set_window_title("Error!");
	 //if (screen != NULL){
	 //   set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 //}
	 //allegro_message("%s.\n %s\n", message.c_str());

	 exit(-1);
}

// Checks if file exists
ALLEGRO_FONT *load_font_ex( std::string file){
  ALLEGRO_FONT *temp_font;
  if ( !(temp_font = al_load_bitmap_font( file.c_str()))){
    abort_on_error( std::string("Cannot find font " + file + "\nTry reinstalling from adsgames.net/download/robotflier"));
  }
  return temp_font;
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
void fade_in( ALLEGRO_BITMAP* bmp_orig, int speed){
  /*BITMAP* bmp_buff;

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
  //allegro_gl_flip();*/
}

// Fade out
void fade_out(int speed){
  /*BITMAP* bmp_orig, *bmp_buff;

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
  //allegro_gl_flip();*/
}
