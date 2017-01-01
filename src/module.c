#if defined (__APPLE__)
	#include "SDL.h"
	#include "SDL_image.h"
	#include <assert.h>
#else
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
	#include <assert.h>
#endif
//#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include "MapObject.h"
#include "player.h"
#include "GameState.h"
#include "module.h"


int** createArray(int m, int n)
{
  int* values = calloc(m*n, sizeof(int));
  assert(values != NULL);
  int** rows = malloc(n*sizeof(int*));
  assert(rows != NULL);
  for (int i=0; i<n; ++i)
  {
    rows[i] = values + i*m;
  }
  return rows;
}

void destroyArray(int** arr)
{
  free(*arr);
  free(arr);
}

//useful utility function to see if two rectangles are colliding at all
int collide2dLadder(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
  //return ((x1 + wt1 >= x2) && (x1 + wt1 <= x2+wt2) && (y1 + ht1  >= y2) && (y1 +ht1 <= y2+wt2));
  return (((x1 + wt1/2 > x2)&&(x1 + wt1/2 < x2 + wt2)) && ((y1 <= y2 + ht2) && (y1 + ht1 >= y2)));
}

int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
  //printf(" %f %f %f %f %f %f %f %f inside collide \n\n", x1, y1, x2, y2, wt1, ht1, wt2, ht2);
  //return ((x1 + wt1 >= x2) && (x1 + wt1 <= x2+wt2) && (y1 + ht1  >= y2) && (y1 +ht1 <= y2+wt2));
  return (!((x1 >= (x2+wt2/3)) || (x2 >= (x1+wt1/3)) || (y1 >= (y2+ht2/3)) || (y2 >= (y1+ht1/3))));
}

