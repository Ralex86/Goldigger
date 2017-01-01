         ▄████  ▒█████   ██▓    ▓█████▄  ██▓  ▄████   ▄████ ▓█████  ██▀███  
        ██▒ ▀█▒▒██▒  ██▒▓██▒    ▒██▀ ██▌▓██▒ ██▒ ▀█▒ ██▒ ▀█▒▓█   ▀ ▓██ ▒ ██▒
       ▒██░▄▄▄░▒██░  ██▒▒██░    ░██   █▌▒██▒▒██░▄▄▄░▒██░▄▄▄░▒███   ▓██ ░▄█ ▒
       ░▓█  ██▓▒██   ██░▒██░    ░▓█▄   ▌░██░░▓█  ██▓░▓█  ██▓▒▓█  ▄ ▒██▀▀█▄  
       ░▒▓███▀▒░ ████▓▒░░██████▒░▒████▓ ░██░░▒▓███▀▒░▒▓███▀▒░▒████▒░██▓ ▒██▒
        ░▒   ▒ ░ ▒░▒░▒░ ░ ▒░▓  ░ ▒▒▓  ▒ ░▓   ░▒   ▒  ░▒   ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░
         ░   ░   ░ ▒ ▒░ ░ ░ ▒  ░ ░ ▒  ▒  ▒ ░  ░   ░   ░   ░  ░ ░  ░  ░▒ ░ ▒░
       ░ ░   ░ ░ ░ ░ ▒    ░ ░    ░ ░  ░  ▒ ░░ ░   ░ ░ ░   ░    ░     ░░   ░ 
             ░     ░ ░      ░  ░   ░     ░        ░       ░    ░  ░   ░     
                                 ░                                          


—————————————————————————————————————————————————————————————————————————————————————
I. Manuel.
—————————————————————————————————————————————————————————————————————————————————————

- Compilation: Depuis le terminale: "make" puis "make run"

- Exécution: "./build/goldigger"

- Règles du jeu: Le joueur doit ramasser des lingots d’or présents dans le niveau pour déverrouiller le portail lui ouvrant l’accès au niveau suivant. 
Il doit pour cela éviter des ennemis (serpent), et divers pièges (lave, vide à sauter, blocs à casser).
Le jeu se termine lorsque le joueur à parcouru tout les niveaux. Il y’a pour l’instant 4 niveaux, que l’on peut changer et augmenter via de nouveau fichiers texte.

- Utilisation:
	Les commandes sont :
	— flèche de gauche : se déplacer à gauche
	— flèche de droite : se déplacer à droite
	— flèche du haut : monter à l’échelle/escalader un bloc
	— echap : quitter le niveau (passer au niveau suivant)
	— Shift: poser une dynamite pour casser un bloc
	- Espace: sauter

—————————————————————————————————————————————————————————————————————————————————————
II. Fonctionnalités du jeu.
—————————————————————————————————————————————————————————————————————————————————————

- il s’agit d’un jeu de plateforme classique basé sur un TileMap classique smooth
- le moteur autorise un certain degré de liberté au joueur
- le système de collision repose sur le système AABB (Align Axis Bounding Box)
- les ennemis sont soumis à la gravité et aux tests de collisions
- le décors est destructible en posant des dynamites avec la touche left shift
- les niveaux sont chargés à partir de fichier texte suivant un format de donnée : un int = un sprite

—————————————————————————————————————————————————————————————————————————————————————
III. Organisation de l’archive.
—————————————————————————————————————————————————————————————————————————————————————

Les fichiers sources se trouvent dans le répertoire "src" de l’archive.
Les fichiers images/audio (assets) se trouvent dans le répertoire data.
La documentation se trouve dans le répertoire doc et comprend: une présentation pdf, le diagramme des modules, le diagramme de Gantt, ainsi que la documentation du code.
Le Makefile 

—————————————————————————————————————————————————————————————————————————————————————
IV. Auteurs.
—————————————————————————————————————————————————————————————————————————————————————
Alexandre Hassler
Idir Djemaoune
Eloi Poyet
