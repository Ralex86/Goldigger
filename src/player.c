#if defined (__APPLE__)
	#include "SDL.h"
	#include "SDL_image.h"
#else
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif
#include <stdio.h>
#include <time.h>
#include "MapObject.h"
#include "player.h"
#include "GameState.h"
#include "module.h"

void initMan(Man *man) {
  man->dieSound = Mix_LoadWAV("files/audio/die.wav");
  Mix_VolumeChunk(man->dieSound, 40);
  man->ouchSound = Mix_LoadWAV("files/audio/ouch.wav");
  Mix_VolumeChunk(man->ouchSound, 40);
  man->jumpSound = Mix_LoadWAV("files/audio/jump.wav");
  man->lifes = 3;
}
  
void initManLevel(Man *man) {
  man->x = 240;
  man->y = 540;
  man->dx = 0;
  man->dy = 0;
  man->w = 48;
  man->h = 64;
  man->onLedge = 0;
  man->onLadder = 0;
  man->animFrame = 0;
  man->animFrame_onLadder = 0;
  man->facingLeft = 0;
  man->slowingDown = 0;
  man->walking = 0;
  man->jumping = 0;
  man->climbing = 0;
  man->manGold = 0;
  man->manDynamites = 10;
  man->health = 3;
}

time_t manHurtOn;
time_t manHurtBuffer;

void manHurt(Man *man) {
  
  manHurtOn = time(0);

  if(manHurtOn > manHurtBuffer) {

    manHurtBuffer = manHurtOn + 1;

    printf("Man got hurt: Health Left: %hu\
        Lives Left: %hu\n", man->health, man->lifes);
    
    fflush(stdout);
    
    if(man->health) {
      if(man->health > 1) {
        Mix_PlayChannel(-1, man->ouchSound, 0);
      }
      man->health--;
    }
  }
}

void manDies(Man *man) {
  Mix_PlayChannel(-1, man->dieSound, 0);
  if(man->lifes) {
    man->lifes--;
  }
}
