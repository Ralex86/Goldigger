/**
 @file GameSDL.h
 @brief Fichier entête du module GameSDL.c
 @author Alexandre HASSLER Idir DJEMAOUNE Eloi POYET
 @date 23 MAI 2016
 */


#ifndef _GAMESDL_h
/**
@def _GAMESDL_h
*/
#define _GAMESDL_h
 


/**
 @fn int processEvents(GameState *game)
 @brief processEvents: "Gestion des évenements associés au clavier dont la logique dépend de l'état dans le quel se trouve la structure Man."
 @param [in, out] game pointeur sur GameState
 @return int
 */
int processEvents(GameState *game);

/**
 @fn void doRender(GameState *game)
 @brief doRender: "Actualise le pointeur de rendu sur SDL et montre à l'ecran ce qu'on a dessiné" 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void doRender(GameState *game);

/**
 @fn void initSDL(GameState *gameState)
 @brief initSDL:" initialisation des variables propres a SDL. On declare une fenêtre, un pointeur sur rendu, on initialise la video et l'audio, on definie les caractèristiques de la fenetre: sa largeur et sa position, on passe le pointeur sur la fenêtre et sur le rendu a la structure centrale GameState"
 @param [in, out] gameState pointeur sur GameState
 @return void
 */
void initSDL(GameState *gameState);

/**
 @fn void gameLoop(GameState *gameState, int levelMAX)
 @brief gameLoop:" On commence au niveau'1', on charge l'etat du jeu, on initialise la musique de fond. Tant qu'on a pas atteint le dernier niveau on boucle dans une sous boucle évenementielle. Celci contient quatre étapes:Les evénements du clavier, les événements du niveau, les détections de collisions, enfin le rendu a l'ecran . L'IHM gère des déplacements élémentaires qui sont verifiers et eventuellement corrigés par la fonction de détection de collision"
 @param [in, out] gameState pointeur sur GameState
 @param [in] nombre de niveaux du jeu de type entier
 @return void
 */
void gameLoop(GameState *gameState, int levelMAX);
//je susi la
/**
 @fn void destroyLevel(GameState *gameState)
 @brief destroyLevel:"Testament d'un niveau et de ses allocations dynamiques, déstruction également de la texture SDL de fond."  
 @param [in, out] gameState pointeur sur GameState
 @return void
 */
void destroyLevel(GameState *gameState);

/**
 @fn void destroySDL(GameState *gameState)
 @brief destroySDL:"Testament de l'IHM SDL"
  @param [in, out] gameState pointeur sur GameState
 @return void
 */
void destroySDL(GameState *gameState);

/**
 @fn void doRenderLedges(GameState *gameState)
 @brief doRenderLedges:"affichage des sprites associés au platformes" 
  @param [in, out] gameState pointeur sur GameState
 @return void
 */
void doRenderLedges(GameState *game);

/**
 @fn void doRenderLava_blocks(GameState *gameState)
 @brief doRenderLava_blocks:"affichage des sprites associés au bloques de lave" 
  @param [in, out] game pointeur sur GameState
 @return void
 */
void doRenderLava_blocks(GameState *game);

/**
 @fn void  doRenderLadder(GameState *game)
 @brief doRenderLadder:"affichage des sprites associés au échelles" 
  @param [in, out] game pointeur sur GameState
 @return void
 */
void doRenderLadder(GameState *game);

/**
 @fn void doRenderGold(GameState *game)
 @brief doRenderGold:"affichage des sprites associés au lingos d'or" 
  @param [in, out] game pointeur sur GameState
 @return void
 */
void doRenderGold(GameState *game);

/**
 @fn void doRenderPortal(GameState *game)
 @brief doRenderPortal:"affichage des sprites associés au portails" 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void doRenderPortal(GameState *game);

/**
 @fn void doRenderMan(GameState *game)
 @brief doRenderMan:"affichage des sprites associés au Man"
  @param [in, out] game pointeur sur GameState
 @return void
 */
void doRenderMan(GameState *game);

/**
 @fn void doRenderDynamite(GameState *game)
 @brief doRenderDynamite:"affichage des sprites associés au dynamites"  
 @param [in, out] im pointeur sur game
 */
void doRenderDynamite(GameState *game);
/**
 @fn void doRenderEnemies(GameState *game)
 @brief doRenderEnemies:"affichage des sprites associés au enemis" 
  @param [in, out] game pointeur sur GameState
 @return void
 */
void doRenderEnemies(GameState *game);
#endif
