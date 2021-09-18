#pragma once
#include "stdafx.h"

//Chargement du texte
sfText* LoadText(char* _sNom);

//Charge l'image du sprite
sfSprite* LoadSprite(char* _sNom, int _isCentered);

//Charge tous les sprites (utilise la fonction LoadSprite)
void LoadSpritePack(INGAME* _Ingame, UTILS* _Utils);

//Affiche un sprite
void Afficher_Sprite(sfSprite* _sprite, float _posX, float _posY, float _scaleX, float _scaleY, float _rotation, sfRenderWindow* _window);

//Affichage de tous les sprites (utilise la fonction BlitSprite)
void Display(INGAME* _Ingame,  UTILS* _Utils);


