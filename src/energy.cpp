#include "energy.h"

// Constructor
energy::energy( ALLEGRO_BITMAP* newImage, ALLEGRO_SAMPLE* newSoundEffect, int newX, int newY) : game_object( newImage, newSoundEffect, newX, newY, 0){

}

// Game logic
void energy::logic(int newMotion, robot *ourRobot){
  x -= newMotion;

  if( !isDead && collision(x, x + width , ourRobot -> getX(), ourRobot -> getX() + ourRobot -> getWidth(), y, y + height, ourRobot -> getY(), ourRobot -> getY() + ourRobot -> getHeight())){
    score += 5;
    stats[STAT_ENERGY] += 1;
		if( ourRobot -> getHealth() < 100)
      ourRobot -> addHealth( 1);

    if( settings[SETTING_SOUND])
      al_play_sample( soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    isDead = true;
  }
}

// Move towards robot
void energy::move_towards( float mov_x, float mov_y, float speed){
  y += (speed * ( mov_y - y)) / 20000;
  x += (speed * ( mov_x - x)) / 20000;
}
