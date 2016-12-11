/**
 @file player.h
 @brief Fichier entête du module player.c
 @author Alexandre HASSLER Idir DJEMAOUNE Eloi POYET
 @date 23 MAI 2016
 */

#ifndef _PLAYER_H
#define _PLAYER_H

/**
@struct Man
@brief Man: Structure du joueur contenant ces positions, ces status,compteur de dynamites et de lingos d'or ainsi que les frames.

*/
typedef struct
{
  float x, y, w, h;
  float dx, dy;

  int manGold;
  int manDynamites;

  int onLedge;
  int onLadder;

  int animFrame;
  int animFrame_onLadder;

  int facingLeft;
  int slowingDown;
  int climbing;
  int jumping;
  int falling;
  int walking;
} Man;


#endif
