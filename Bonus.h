#pragma once
#include "stdafx.h"

void AddBonus(INGAME* _Ingame, UTILS* _Utils, struct BONUS bonus);

void RemoveBonusAt(INGAME* _Ingame, UTILS* _Utils, int id);

void Bonus_LoadSprite(INGAME* _Ingame);

void Bonus_initialisation(INGAME* _Ingame, UTILS* _Utils);

void Bonus_spawn(INGAME* _Ingame, UTILS* _Utils, int indice);

void Bonus_update(INGAME* _Ingame, UTILS* _Utils);

void Bonus_Display(INGAME* _Ingame, UTILS* _Utils);
