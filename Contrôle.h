#pragma once
#include "stdafx.h"

//Commande clavier souris temps réel
void Cmd_temps_reel(INGAME* _Ingame, UTILS* _Utils);

//Commande clavier souris temps évènementiel
void Cmd_evenementiel(INGAME* _Ingame, UTILS* _Utils);

//Regroupement des fonctions commandes temps réel/ évènementiel
void Commande(INGAME* _Ingame, UTILS* _Utils);