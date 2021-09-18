#include "stdafx.h"

void New_Game(INGAME* _ingame, UTILS* _utils)
{
	_utils->fDeltatime = 0;

	_ingame->score_courant.Score = 0.0f;

	//Réinitialisation de toutes les valeurs 
	_utils->iCompteur_Zombie = 0;
	_utils->iCompteur_Vague = 1;
	_ingame->iCompteur_Kill = 0;

	Combo_Initialisation(_ingame, _utils);
	Bonus_initialisation(_ingame, _utils);

	Init_Munition(_ingame, _utils);

	Suppr_ALL_Zombies(_ingame, _utils);

	Initialisation_Spawner(_ingame, _utils);

	_ingame->Joueur.iPdv = PDV_JOUEUR_MAX;
	_ingame->Joueur.iLieux = eReserve_Bar;
	_ingame->Joueur.iEtat = NON_POISON;

	_ingame->Joueur.Position.x = 2300.0f;
	_ingame->Joueur.Position.y = 1500.0f;

	_ingame->Joueur.jauge_energie = 2.0f;		

	_ingame->tir.nbTir = 0;
	_ingame->tir.timer_tir = 0; // On initialise le timer à 0

	_ingame->Joueur.Timer_invulnerable = TIMER_INVULNERABLE;  //duré frame invincibilité
	_ingame->Joueur.Timer_clignotement = 0.2f;  // durée clignotement

	_ingame->Joueur.invulnerable = FALSE;

	_ingame->iArme_Choisie = Batte_de_baseball;
	_ingame->Hud.armes = Batte_de_baseball;
 
	_ingame->iNb_bonus = RESET;
	_ingame->Ammo.iNb_antidote = 0;

	//Le nom du prochain joueur est vide
	for (int i = 0; i <= CARACTERE_NOM ; i++)
	{
		_ingame->score_courant.chare[i] = NULL;
	}
}


void Defaite(INGAME* _ingame, UTILS* _utils)
{
	if (_ingame->Joueur.iPdv <= 0.00001)
	{
		_utils->iEtat = STATEDEFAITE;
	}
}