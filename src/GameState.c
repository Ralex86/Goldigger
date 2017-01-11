#if defined (__APPLE__)
  #include "SDL.h"
  #include "SDL_image.h"
  #include <assert.h>
#else
  #include "SDL2/SDL.h"
  #include "SDL2/SDL_image.h"
  #include <assert.h>
#endif

#include <stdio.h>
#include <time.h>
#include "MapObject.h"
#include "player.h"
#include "module.h"
#include "GameState.h"

int game_getLedgeX(GameState *game, int i)
{
  return Ledge_getX(&game->ledges[i]);
}

void updateManPosition(GameState *game)
{
  //deplacement man
  Man *man = &game->man;
  man->x += man->dx;
  man->y += man->dy; // on recoit les deplacements elementaires de Eventprocess

  if(!game->man.climbing)
  {
    if(man->onLedge && !man->slowingDown)
    {
      if(game->time % 2 == 0)
      {
        //sheet
        man->animFrame %=11;
        man->animFrame++;
      }
    }

    if(!game->man.onLedge && !man->slowingDown)
    {
      if(game->time % 4 == 0)
      {
        //printf("%d\n",man->animFrame);
        man->animFrame %=4;
        man->animFrame++;
      }
    }

    man->dy += game->mapGravity;
  }

  if(game->man.climbing && game->man.onLadder)
  {
    if(game->time % 3 == 0)
    {
      man->animFrame_onLadder %=3;

      man->animFrame_onLadder++;
    }
  }
}


void loadMap(char *name, GameState *game)
{
  int** tile = createArray(game->mapDimX, game->mapDimY);
  int i=0;
  int j=0; // les compteurs pour les tableaux dechelles ou de ledges
  int k=0;
  int l=0;
  int m=0;

  int x, y;
  FILE *fp;

  fp = fopen(name, "r");

  if (fp == NULL)
  {
    printf("Erreur de lecture de la map %s\n", name);

    exit(1);
  }

  for (y=0;y<game->mapDimY;y++)
  {
    for (x=0;x<game->mapDimX;x++)
    {
      fscanf(fp, "%d", &tile[y][x]);
      if (tile[y][x] == 1 || tile[y][x] == 2 || tile[y][x] == 7) {game->nbLedges++;}
      if (tile[y][x] == 3 || tile[y][x] == 8 ) {game->nbLadders++;} // on compte le nombre dechelles
      if (tile[y][x] == 4) {game->nbGolds++;} // on compte le nombre de lingots
      if (tile[y][x] == 6) {game->nbLava_blocks++;} // on compte le nombre de lava
      if (tile[y][x] == 9) {game->nbEnemies++;} // on compte le nombre de snakes

    }
  }

  game->ledges = (Ledge*) malloc(game->nbLedges*sizeof(Ledge)); 
  assert(game->ledges != NULL);
  game->ladders = (Ladder*) malloc(game->nbLadders*sizeof(Ladder));
  assert(game->ladders!= NULL); 
  game->golds = (Gold*) malloc(game->nbGolds*sizeof(Gold)); 
  assert(game->golds != NULL);
  game->lava_blocks = (Lava*) malloc(game->nbLava_blocks*sizeof(Lava)); 
  assert(game->lava_blocks != NULL);
  game->snake = (Enemy*) malloc(game->nbEnemies*sizeof(Enemy)); 
  assert(game->snake != NULL);

  for (y=0;y<game->mapDimY;y++)
  {
    for (x=0;x<game->mapDimX;x++)
    {
      if (tile[y][x] == 1 || tile[y][x] == 2 || tile[y][x] == 7)  // ledges dirt ou grass ou snow
      {
        game->ledges[i].w = 64;
        game->ledges[i].h = 64;
        game->ledges[i].x = x*64;
        game->ledges[i].y = y*64;
        game->ledges[i].ledgeType = tile[y][x];
        game->ledges[i].destroyed = 0;
        i++;
      }

      if (tile[y][x] == 3 || tile[y][x] == 8)  // ladder
      {
        game->ladders[j].w = 64;
        game->ladders[j].h = 64;
        game->ladders[j].x = x*64;
        game->ladders[j].y = y*64;
        game->ladders[j].ladderType = tile[y][x];
        j++;
      }

      if (tile[y][x] == 4)  // gold
      {
        game->golds[k].w = 64;
        game->golds[k].h = 64;
        game->golds[k].x = x*64;
        game->golds[k].y = y*64;
        game->golds[k].display = 1;
        //printf("gx:%f g:y%f\n",game->golds[k].x,game->golds[k].y );
        k++;
      }

      if (tile[y][x] == 5)  // gate
      {
        game->gate.w = 64;
        game->gate.h = 128;
        game->gate.x = x*64;
        game->gate.y = y*64-64;
        game->gate.open = 0;
      }

      if (tile[y][x] == 9)  // Snake
      {
        game->snake[m].w = 64;
        game->snake[m].h = 64;
        game->snake[m].x = x*64;
        game->snake[m].y = y*64;
        game->snake[m].enemy_animFrame = 0;
        game->snake[m].facingLeft = 0;
        m++;
      }


      if (tile[y][x] == 6)  // lava
      {
        game->lava_blocks[l].w = 64;
        game->lava_blocks[l].h = 64;
        game->lava_blocks[l].x = x*64;
        game->lava_blocks[l].y = y*64;
        game->lava_blocks[l].lava_anim = 0;
        //printf("lx:%f l:y%f\n",game->lava_blocks[l].x,game->lava_blocks[l].y );
        l++;
      }
    }
  }


  fclose(fp);
  destroyArray(tile);
}

void initLevel(GameState *game, int level)
{
  game->nbLedges = 0;
  game->nbLadders = 0;
  game->nbLava_blocks = 0;
  game->nbGolds = 0;
  game->nbDynamites = 0;
  game->dynamites = (Dynamite*) malloc(10*sizeof(Dynamite));
  assert(game->dynamites!= NULL); 
  game->nbEnemies = 0;
  game->mapGravity = 0.55;
  game->mapDimX = 20;
  game->mapDimY = 10;
  game->time = 0;
  
  if(level == 1)
  {
    setLevelBackground(game, "files/images/cave-background.jpg");
    initManLevel(&game->man);
    game->man.x = 220;
  }
  else if(level == 2)
  {
    setLevelBackground(game, "files/images/snowy-background.jpg");
    initManLevel(&game->man);
    game->man.facingLeft = 1;
  }
  else if(level == 3)
  {
    setLevelBackground(game, "files/images/snowy-background.jpg"); 
    initManLevel(&game->man);
    game->man.y = 380;
    game->man.facingLeft = 1;
  }
  else if(level == 4)
  {
    setLevelBackground(game, "files/images/cave-background2.jpg");
    initManLevel(&game->man);
    game->man.y = 320;
  }
}

void SetStageNum(GameState *game, int stageNum)
{
  game->stageNum = stageNum;
}

void loadGame(GameState *game)
{
  SDL_Surface *surface = NULL;
  surface = IMG_Load("files/images/Sprites.png");
  
  if(surface == NULL)
  {
    printf("Cannot find Sprites.png !\n\n");
    SDL_Quit();
    exit(1);
  }
  
  game->sheetTexture = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  game->bgMusic = Mix_LoadWAV("files/audio/indiana.wav");
  
  if(game->bgMusic != NULL)
  {
    Mix_VolumeChunk(game->bgMusic, 16);
  }
  
  game->bombSound = Mix_LoadWAV("files/audio/Bomb.wav");
  game->goldSound = Mix_LoadWAV("files/audio/gold.wav");

  initLevel(game,game->stageNum);

  char levelPath[20];
  sprintf(levelPath,"files/levels/level%d",game->stageNum);

  loadMap(levelPath,game);
}

void process(GameState *game)
{
  for(int i = 0; i < game->nbEnemies; i++)
  { 
    game->snake[i].y += game->mapGravity*10;
    if(game->time % 5 == 0)
    { 
      if(game->snake[i].facingLeft == 0)
      {game->snake[i].x += 10;}
      else
      {game->snake[i].x -= 10;}
      game->snake[i].enemy_animFrame ++;
      game->snake[i].enemy_animFrame %=5;
    }
  }

  for(int i = 0 ; i < game->nbLava_blocks;i++)
  {
    if(game->time % 3 == 0)
    {
      game->lava_blocks[i].lava_anim ++;
      game->lava_blocks[i].lava_anim %=38;
    }
  }

  for(int i = 0 ; i < game->nbDynamites;i++)
  {
    if(!game->dynamites[i].used)
    {
      if(game->time % 8 == 0)
      {
        if(game->dynamites[i].countdown < 14)
        {
          printf("%d\n",game->dynamites[i].countdown );
          game->dynamites[i].countdown++;
        }
        if(game->dynamites[i].countdown > 13)
        {
          Mix_PlayChannel(-1, game->bombSound, 0);
          game->dynamites[i].used = 1;
          for(int k = 0 ; k < game->nbLedges;k++)
          {
            if(collide2dLadder(game->ledges[k].x,game->ledges[k].y,game->dynamites[i].x,game->dynamites[i].y,game->ledges[k].w,game->ledges[k].h,game->dynamites[i].w,game->dynamites[i].h) == 1)
            {
              game->ledges[k].destroyed = 1;
            }
          }
        }
      }
    }
  }

  updateManPosition(game);

  //add time
  game->time++;
}

void collide2dSnakes(GameState *game)
{
  float mw = game->man.w, mh = game->man.h; 
  float mx = game->man.x, my = game->man.y; 

  for(int j=0;j<game->nbEnemies;j++)
  {
    float sw = game->snake[j].w, sh = game->snake[j].h; 
    float sx = game->snake[j].x, sy = game->snake[j].y; 

    if(collide2d(mx,my,sx,sy,mw,mh,sw,sh))
    {
      manHurt(&game->man);
    }

    //control movement of the snakes 
    for(int i = 0; i < game->nbLedges; i++)
    {
      float bx = game->ledges[i].x, by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h;

      if(game->ledges[i].destroyed == 0)
      {
        if(sx+sw > bx && sx <bx+bw)
        {
          //somme nous sur ledge ?
          if(sy+sh > by && sy < by)
          {
            //correct y
            game->snake[j].y = by-sh;
            sy = by-sh;
          }
        }

        if(sy+sh > by && sy<by+bh)
        {
          //bumps on right edge
          if(sx < bx+bw && sx+sw > bx+bw)
          {
            //correct x
            game->snake[j].x = bx+bw;
            sx = bx+bw;

            game->snake[j].facingLeft = 0;
          }
          //bumps on left edge
          else if(sx+sw > bx && sx < bx)
          {
            //correct x
            game->snake[j].x = bx-sw;
            sx = bx-sw;

            game->snake[j].facingLeft = 1;
          }
        }
      }
    }
  }
}

void collisionDetect(GameState *game)
{
  float mw = game->man.w, mh = game->man.h; // a mettre dans la structure gamestate
  float mx = game->man.x, my = game->man.y; // a mettre get (mutateur)

  //verifie chute
//  if(game->man.y > 700)
//  {
//    manDies(&game, &man);
//  }

  // est ce quon ramasse un lingot
  for(int i = 0; i < game->nbGolds; i++)
  {
    float gx = game->golds[i].x, gy = game-> golds[i].y, gw = game-> golds[i].w, gh = game-> golds[i].h;

    if(collide2d(mx,my,gx,gy,mw,mh,gw,gh) && game->golds[i].display == 1)
    {
      Mix_PlayChannel(-1, game->goldSound, 0);
      game->golds[i].display = 0;
      game->man.manGold ++;
    }
  }
  // est ce qu'on est sur une echelle ?
  //printf("%d \n\n\n",game->nbLadders);

  game->man.onLadder = 0;
  for(int i = 0; i < game->nbLadders; i++)
  {
    float lx = game->ladders[i].x, ly = game->ladders[i].y, lw = game->ladders[i].w, lh = game->ladders[i].h;
    if(collide2dLadder(mx,my,lx,ly,mw,mh,lw,lh))
    {
      //printf("mx:%f my:%f lx:%f ly:%f ladder:%d\n",mx,my,lx,ly,game->man.onLadder);
      game->man.onLadder = 1;
      break;
    }
  } 

  //game->man.onLedge = 0;
  // verifie collision avec snakes/ledges
  if(game->nbEnemies>0)
  {
    collide2dSnakes(game);
  }

  //verifie collision avec Ledges
  for(int i = 0; i < game->nbLedges; i++)
  {
    float bx = game_getLedgeX(game,i), by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h; //game_getLedgeX(game,i)


    if(game->ledges[i].destroyed == 0)
    {
      if(mx+mw/2 > bx && mx+mw/2<bx+bw)
      {
        //on se cogne la tete ?
        if(my < by+bh && my > by && game->man.dy < 0)
        {
          //correct y
          game->man.y = by+bh;
          my = by+bh;

          //tete cogné, stop velocite
          game->man.dy = 0;
          game->man.onLedge = 1;
          //game->man.jumping = 0;
        }
      }
      if(mx+mw > bx && mx <bx+bw)
      {
        //on est sur ledge ?
        if(my+mh > by && my < by && game->man.dy > 0)
        {
          //correct y
          game->man.y = by-mh;
          my = by-mh;

          //sur legdge, stop velocite
          game->man.dy = 0;
          game->man.onLedge = 1;
          game->man.jumping = 0;
        }
      }

      if(my+mh > by && my<by+bh)
      {
        //se cogne sur bord droit
        if(mx < bx+bw && mx+mw > bx+bw && game->man.dx < 0)
        {
          //correct x
          game->man.x = bx+bw;
          mx = bx+bw;
          game->man.dx = 0;
        }
        //se cogne sur bord gauche
        else if(mx+mw > bx && mx < bx && game->man.dx > 0)
        {
          //correct x
          game->man.x = bx-mw;
          mx = bx-mw;
          game->man.dx = 0;
        }
      }
    }
  }//for
}

void setLevelBackground(GameState *game, char* bgImagePath){
  SDL_Surface *bg = IMG_Load(bgImagePath);
  game->backgroundTexture = SDL_CreateTextureFromSurface(game->renderer, bg);
  SDL_FreeSurface(bg);
}

