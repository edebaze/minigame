# minigame - test

Bonjour,
Voici un petit récapitulatif des règles de ce jeu.

## Fonctionnement du jeu
#### Lancement du jeu

Pour lancer le jeu, lancez tout simplement le fichier "_src/main.cpp_"
Ce jeu ne devrait nécessiter aucune librairie externe.

#### Déroulement du jeu
Le jeu se déroule en tour par tour. Le joueur est représenté par le chevalier, et l'ordinateur par l'orc. 

Le jeu est composé de 5 niveaux, à la fin de chacuns de ceux-ci, une amélioration sera proposée au joueur (*Boost de statistiques* ou *Nouvel Item*) \
Lorsque le joueur (chevalier) décède, la partie prend fin, et le message de victoire s'affiche lorsque les 5 niveaux ont été complétés.\
A la fin de chaque niveaux, le joueur possède le choix de continuer ou quitter le jeu.

#### Déroulement d'un niveau
Chaque tours (appelés _rounds_) l'attaquant (appelé *current_player*) change :
  1. Lancement des capacités spéciales (message d'erreur si capacité en cooldown)
  2. Attaque
  3. Affichage des dommages reçus par la cible 

## Notes 

- Changements de statistiques volontaire du chevalier (hp : _~~20~~  ->  40_) : Chevalier trop faible par rapport à l'orc, le niveau 1 était trop compliqué à passer.
- Ajout d'une nouvelle stat appelée "resistance" qui réduit les dommages de manières fixe.
- Seules ces deux classes (Orc, Chevalier) ont été implémentées mais le système est conçut pour facilement en implémenter de nouvelles. 
- Le système n'est PAS prévu pour supporter du multi-player / multi targeting (à la Final Fantasy) ainsi les valeurs "current_player" et "current_target" sont automatiquement instanciées à chaque rounds.

#### Nomenclature

Je suis actuellement entrain d'essayer de trouver de nouvelles nomenclatures / règles d'écritures & architectures qui me sieds davantage dans mes projets personnels. Je profite donc de projets comme celui ci pour effectuer des tests.
Je précise cela car certains choix peuvent sembler incongrues (voir chaotiques), cela est dût au fait que je n'utilise pas mes règles habituelles.
Voici les règles que j'ai essayé au cours de ce projet :

- variable : camelCase
- fonction : snake_case
- class : PascalCase
- getter/setter : camelCase
- constant : UPPER_SNAKE_CASE 
- filename: lowercase
