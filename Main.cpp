// TestCSFML.cpp�: d�finit le point d'entr�e pour l'application console.
//
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	INGAME* Ingame = (INGAME*)calloc(1, sizeof(INGAME)); //Initiatlisation de la structure Ingame

	UTILS* Utils = (UTILS*)calloc(1, sizeof(UTILS));		//Initiatlisation de la structure Utils
	
	LoadSpritePack(Ingame, Utils);	//Fonction chargement du SpritePack complet

	Initialisation(Ingame, Utils);  //Fonction initialisation des variables

	//Boucle de jeu  regroupant : affichage , les commandes(tps reel, evenementiel), mise � jour des variables et divers �l�ment du jeu
	Update(Ingame, Utils); 

	return 0;
}

