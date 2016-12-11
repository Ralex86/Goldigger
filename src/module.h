/**
 @file module.h
 @brief Fichier entête du module module.c.
 @author Alexandre HASSLER Idir DJEMAOUNE Eloi POYET
 @date 23 MAI 2016
 */


#ifndef _MODULE_h
#define _MODULE_h

/**
 @fn int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
 @brief collide2d: "fonction de collision en entre le joueur les ledges" 
 @param [in] x1 y1 x2 y2 wt1 ht1 wt2 ht2 de type float 
 @return int
 */
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
/**
 @fn int collide2dLadder(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
 @brief collide2dLadder: "fonction de collision entre le joueur et les echelles" 
 @param [in] x1 y1 x2 y2 wt1 ht1 wt2 ht2 de type float
 @return int
 */
int collide2dLadder(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
/**
 @fn int** createArray(int m, int n)
 @brief createArray: "création d'un tableau 2D" 
 @param [in] n m de type int
 @return int**
 */
int** createArray(int m, int n);
/**
 @fn void destroyArray(int** arr)
 @brief doRender: "testament pour la destruction du tableau 2D " 
 @param [in, out] arr double pointeur(tableau 2D)
 @return void
 */
void destroyArray(int** arr);

#endif
