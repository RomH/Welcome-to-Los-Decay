#pragma once
#include "stdafx.h"

//Commande clavier souris temps r�el
void Cmd_temps_reel(INGAME* _Ingame, UTILS* _Utils);

//Commande clavier souris temps �v�nementiel
void Cmd_evenementiel(INGAME* _Ingame, UTILS* _Utils);

//Regroupement des fonctions commandes temps r�el/ �v�nementiel
void Commande(INGAME* _Ingame, UTILS* _Utils);