#pragma once
#include "stdafx.h"


void Distance_Joueur_Zombie(INGAME* _Ingame, UTILS* _Utils);

float Length(sfVector2f v);

sfVector2f Normalize(sfVector2f v);

float directionToAngle(sfVector2f v);

sfVector2f angleToDirection(float rotation);

float RotationPerso(INGAME* _ingame, UTILS* _utils);

float Distance_Euclidienne(sfVector2f _V1, sfVector2f _V2);

void Distance_Zombie_Cible(INGAME* _Ingame, UTILS* _Utils);
