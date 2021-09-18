#include "stdafx.h"

//Initialisation du jeu
void Initialisation(INGAME* _Ingame, UTILS* _Utils)
{
	sfVideoMode mode = { LONGUEUR, HAUTEUR, 32 };	//Déclaration du VideoMode qui contient la résolution et la profondeur de couleurs (32)
	_Utils->window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);      //sfFullscreen

	srand((unsigned int)time(NULL)); //Création d'une dimension aléatoire en fonction du temps

	_Utils->horloge = sfClock_create();	//Création d'une Horloge
	_Utils->fDeltatime = 0;

	Init_Camera(_Ingame, _Utils);

	_Ingame->iNbr_Zombie_Max = NB_ZOMBIE_INITIAL; // nombre de zombie à la premiere vague

	LectureFichier_Pack(_Ingame, _Utils); //Regroupe toutes les fonctions de lecture de fichier
	Chargement_score(_Utils, _Ingame); // lecture du fichier Score.bin

	LoadSound_Pack(_Utils, _Ingame);

	initialisation_sonsZombie(_Utils, _Ingame);


	//MENU
	Menu_initialisation(_Ingame, _Utils);

	Initialisation_score(_Ingame, _Utils);

	Combo_Initialisation(_Ingame, _Utils);

	Bonus_initialisation(_Ingame, _Utils);

	Init_Munition(_Ingame, _Utils);

	Load_Particle(_Ingame, _Utils);

	Initialisation_Spawner(_Ingame, _Utils);

	_Ingame->Joueur.iPdv = PDV_JOUEUR_MAX;
	_Ingame->Joueur.iLieux = eReserve_Bar;
	_Ingame->Joueur.iEtat = NON_POISON;			//new

	_Ingame->Joueur.Position.x = 2300.0f; //2300
	_Ingame->Joueur.Position.y = 1500.0f; //1600

	_Ingame->Joueur.jauge_energie = 2.0f;		//new

	_Ingame->Pos_Porte.x = 2980;
	_Ingame->Pos_Porte.y = 1260;

	_Ingame->Pos_Distributeur_Boisson.x = 2550.0f;
	_Ingame->Pos_Distributeur_Boisson.y = 920.0f;

	//NEW
	_Ingame->Pos_Reservoir_Voiture1.x = 670.0f;
	_Ingame->Pos_Reservoir_Voiture1.y = 3140.0f;
	_Ingame->Pos_Reservoir_Voiture2.x = 1600.0f;
	_Ingame->Pos_Reservoir_Voiture2.y = 4300.0f;
	_Ingame->Pos_Reservoir_Voiture3.x = 3740.0f;
	_Ingame->Pos_Reservoir_Voiture3.y = 3280.0f;

	_Ingame->tir.nbTir = 0;
	_Ingame->tir.timer_tir = 0; // On initialise le timer à 0

	_Ingame->Joueur.Timer_invulnerable = TIMER_INVULNERABLE;  //duré frame invincibilité
	_Ingame->Joueur.Timer_clignotement = TIMER_CLIGNOTEMENT;  // durée clignotement

	_Ingame->Joueur.invulnerable = FALSE; //le joueur est vulnérable aux attaques


}


