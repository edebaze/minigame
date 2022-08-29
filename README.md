# minigame - test

Bonjour,
Voici un petit récapitulatif des règles de ce jeu.

## Fonctionnement du jeu
#### Lancement du jeu

Pour lancer le jeu, lancez tout simplement le fichier "_src/main.cpp_"
Ce jeu ne devrait nécessiter aucune librairie externe.

#### Déroulement du jeu
Le jeu se déroule en tour par tour. Le joueur est représenté par le chevalier, et l'ordinateur par l'orc.
Le jeu est composé de 5 niveaux, à la fin de chacuns de ceux-ci, une amélioration sera proposée au joueur (*Boost de statistiques* ou *Nouvel Item*)
Lorsque le joueur (chevalier) décède, la partie prend fin, et le message de victoire s'affiche lorsque les 5 niveaux ont été complétés.
A la fin de chaque niveaux, le joueur possède le choix de continuer ou quitter le jeu.

#### Déroulement d'un niveau
Chaque tours (appelés _rounds_) l'attaquant (appelé *current_player*) change.

## Notes 

- Changements de statistiques volontaire du chevalier (hp : _~~20~~  ->  40_) : Chevalier trop faible par rapport à l'orc, le niveau 1 était trop compliqué à passer.
- Seules ces deux classes (Orc, Chevalier) ont été implémentées mais le système est conçut pour facilement en implémenter de nouvelles. 
- Le système n'est PAS prévu pour supporter du multi-player / multi targeting (à la Final Fantasy) ainsi les valeurs "current_player" et "current_target" sont automatiquement instanciées à chaque rounds.
