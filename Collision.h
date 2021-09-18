#pragma once
#include "stdafx.h"

//Collision PERSO / DECOR
void Colisions_Perso_Color(INGAME* _Ingame, UTILS* _Utils, sfColor _Color_Perso, int* _BoucleForI, int* _BoucleForJ, int _X_Perso, int _Y_Perso, int Direction_Deplacement_Perso, int _idle);


void Colisions_Mob_Color(INGAME* _Ingame, UTILS* _Utils, sfColor _Color_Zombie, int* _BoucleForI, int* _BoucleForJ, int _posX, int _posy, int _id, int Sens_marche);

void Contournement_Zombie(INGAME* _Ingame, UTILS* _Utils, sfColor _Color_Zombie, int* _BoucleForI, int* _BoucleForJ, int _posX, int _posy, int _id, int Contournement);
