/**
 @file player.h
 @brief Fichier entête du module player.c
 @author Alexandre HASSLER Idir DJEMAOUNE Eloi POYET
 @date 23 MAI 2016
 */

#ifndef _PLAYER_H
#define _PLAYER_H
#if defined (__APPLE__)
  #include "SDL_mixer.h"
#else
  #include "SDL2/SDL_mixer.h"
#endif

/**
@struct Man
@brief Man: Structure du joueur contenant ces positions, ces status,compteur de dynamites et de lingos d'or ainsi que les frames.

*/
typedef struct
{
  float x, y, w, h;
  float dx, dy;

  int onLedge;
  int onLadder;

  int animFrame;
  int animFrame_onLadder;

  int facingLeft;
  int slowingDown;

  int walking;
  int jumping;
  int climbing;
  int falling;

  int manGold;
  int manDynamites;

  unsigned short int health;
  unsigned short int lifes;

  Mix_Chunk *ouchSound;
  Mix_Chunk *dieSound;
  Mix_Chunk *jumpSound;

} Man;


void initMan(Man *man);
void initManLevel(Man *man);
void manHurt(Man *man);
void manDies(Man *man);

#endif
