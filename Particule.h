#pragma once
#include "stdafx.h"

void AjouteParticule(int _posX, int _posY, struct PARTICLE** _first);

void RetireParticule(struct PARTICLE* _current, struct PARTICLE** _first);

void Load_Particle(INGAME* _ingame, UTILS* _utils);

void Display_Particles(INGAME* _Ingame, UTILS* _Utils);
