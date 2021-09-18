#pragma once
#include "stdafx.h"

sfSound* LoadSound(char* _sNom);

void LoadSound_Pack(UTILS* _utils, INGAME* _ingame);

void lecture_musique(UTILS* _utils, INGAME* _ingame, sfSound* sound, float volume, sfBool is_boocle);

void UpdateMusique(INGAME* _ingame, UTILS* _utils);

void initialisation_sonsZombie(UTILS* _utils, INGAME* _ingame);

void bruitage_des_zombies(UTILS* _utils, INGAME* _ingame);

void SonMarche(INGAME* _ingame, UTILS* _utils);

void protection_son(INGAME* _ingame, UTILS* _utils);


