/**
 @file GameState.h
 @brief Fichier entête du module GameState.
 @author Alexandre HASSLER Idir DJEMAOUNE Eloi POYET
 @date 23 MAI 2016
 */


#ifndef _GAMESTATE_H
#define _GAMESTATE_H
#if defined (__APPLE__)
	#include "SDL_mixer.h"
#else
	#include "SDL2/SDL_mixer.h"
#endif
/**
@struct GameState GameState.h
@brief GameState: c'est le module central qui gère le chargement des niveaux, des éléments du décors, gère les collisions et réajuste les déplacements élémentaires dx, dy . C'est le noyau du jeu qui traite les informations reçus par les modules périphiriques, ce module est composé d'une structure de tableau de structures ou de structures, ce qui a rendu complexe l'integration des mutatteurs et poser des problèmes de dépendance cerculaire dans l'inclusion des fichier headers. Ayant réalisé ce fait trop tardivement nous n'avons pas pu respecter les modalitées de conceptions. Néanmoins nous avons mit un exemple de muttateur qui accéde au champ  d'une des case de structure appartenent à une structure. Enfin l'avantage de passer par cette structure regroupant les sous structures est de pouvoir comprendre plus facilement le code a mesure qu'on le produit.

*/
typedef struct
{
  int stageNum;

	//MAP

	float mapGravity;
	float mapDimX;
	float mapDimY;

  //Players
  Man man;

  //Ledges
  Ledge *ledges;
  int nbLedges;

  //Ladder
  Ladder *ladders;
  int nbLadders;

  // Lava
  Lava *lava_blocks;
  int nbLava_blocks;

  //Gold
  Gold *golds;
  int nbGolds;

  Dynamite *dynamites;
  int nbDynamites;

  Enemy *snake;
  int nbEnemies;

  Portal gate;

  //Images

  SDL_Texture *sheetTexture;
  SDL_Texture *backgroundTexture;


  //Sounds
  int musicChannel;
  Mix_Chunk *bgMusic;
  Mix_Chunk *dieSound;
  Mix_Chunk *jumpSound;
  Mix_Chunk *bombSound;
  Mix_Chunk *goldSound;

  int time;

  //Renderer
  SDL_Renderer *renderer;
  SDL_Window *window;                    // Declare une fenetre

} GameState;

/**
 @fn  int game_getLedgeX(GameState *game, int i)
 @brief game_getLedgeX:Accesseur à une structure legde dans le tableau de structure Ledge 
 @param [in, out] game pointeur sur GameState
 @param [in] i la position dans le tableau de structure Ledge 
 @return int
 */
int game_getLedgeX(GameState *game, int i);


/**
 @fn  void SetStageNum(GameState *game, int stageNum)
 @brief SetStageNum:"Initialise le numéro du level chargé" 
 @param [in, out] game pointeur sur GameState
 @param [in] stageNum le numéro du level à charger
 @return void
 */
void SetStageNum(GameState *game, int stageNum);

/**
 @fn  void initLevel(GameState *game, int level)
 @brief initLevel:"Initialisation du level" 
 @param [in, out] game pointeur sur GameState
 @param [in] level le numéro du level à initialiser
 @return void
 */
void initLevel(GameState *game, int level);

/**
 @fn  loadMap(char *name, GameState *game)
 @brief loadMap:"charge dans un tableau 2D les entiers qui codent un élément du niveau, compte ce nombre d'éléments. Fait une allocation dynamique dans le tas de la taille de ce nombre d'elements * la taille de la structure asscosiée a cette élément. Initialise les tableaux de structures associés a ces éléments. Stocke dans les champs de ces structures la coordonnée * la largeur respectivement la hauteur d'un sprite élémentaire pour avoir une correspendance entre la position de cet élément dans le fichier avec résolution de la fenêtre. Initialise éventuellement le type du sprite pour le chargement d'une texture et le compteur pour les frames d'annimations. enfin ferme le fichier et efface le tableau 2D" 
 @param [in, out] name tableau de caractères
 @param [in, out] game pointeur sur GameState
 @return void
 */
void loadMap(char *name, GameState *game);


/**
 @fn  void loadGame(GameState *game)
 @brief loadGame:"charge la feuille de sprite, les son, et le chemin relatif vers le niveau a charger " 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void loadGame(GameState *game);


/**
 @fn  void process(GameState *game)
 @brief process:"Gère la gravité des éléments du niveau et leurs compteurs de frames d'animations (dynamites - serpents - blocks de laves), met a jour les coordonnées des enemis et du joueur, incrémente la variable de temps de l'état du jeu." 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void process(GameState *game);

/**
 @fn  void collisionDetect(GameState *game)
 @brief pcollisionDetect:"fonction importante de collision du personnage avec les éléments du décors: si le personnage ramasse un lingo - si le personnage passe sur une echelle - si le personnage se cogne la tête - s'il attirie sur une platforme - s'il se cogne contre un mur. Ces détéction de collision metent a jour les flages de la structure joueur(aussi celle des serpents ). les flages identifie un état dans lequel se trouve la structure." 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void collisionDetect(GameState *game);

/**
 @fn  void updateManPosition(GameState *game)
 @brief updateManPosition:"Prend en compte les deplacements élémentaire valider ou modifier par les fonctions précédentes pour mettre a jour les coordonnés du personnage et les compteurs de frames d'annimations en vue d'un raffrichissement de la fenetre d'affichage." 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void updateManPosition(GameState *game);

/**
 @fn  collide2dSnakes(GameState *game)
 @brief collide2dSnakes:"détections des collisions du serpent avec les éléments du décors" 
 @param [in, out] game pointeur sur GameState
 @return void
 */
void collide2dSnakes(GameState *game);

#endif
