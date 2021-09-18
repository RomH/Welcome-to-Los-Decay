#include "stdafx.h"

//Commande clavier souris temps réel
void Cmd_temps_reel(INGAME* _Ingame, UTILS* _Utils)
{
	
	//printf("%d, %d \n", _Utils->Mouse.x, _Utils->Mouse.y);


	if (_Utils->iEtat == STATEPLAY)
	{
		if (sfKeyboard_isKeyPressed(sfKeyLShift) && _Ingame->Joueur.jauge_energie > 0)
		{
			_Ingame->Joueur.courir = TRUE;
		}
		else
		{
			_Ingame->Joueur.courir = FALSE;
			_Ingame->Joueur.ValeurSprint = 1;
		}
		//printf("%f %d\n", _Ingame->Joueur.jauge_energie, _Ingame->Joueur.ValeurSprint);

		Deplacement_Joueur(_Ingame, _Utils);

		Control_Armes(_Utils, _Ingame);
	}
}

//_______________________________________________________________________________________________________________________________________________________


//Commande clavier souris temps évènementiel
void Cmd_evenementiel(INGAME* _Ingame, UTILS* _Utils)
{
	while (sfRenderWindow_pollEvent(_Utils->window, &_Utils->event))
	{
		if (_Utils->event.type == sfEvtKeyPressed)
		{
			//TOUCHE PAUSE  avec P
			if (_Utils->event.key.code == sfKeyP && _Utils->iEtat == STATEPLAY)
			{
				_Utils->iEtat = STATEPAUSE;
			}
			else if(_Utils->event.key.code == sfKeyP && _Utils->iEtat == STATEPAUSE)
			{
				_Utils->iEtat = STATEPLAY;
			}

			//Retour au Menu avec ECHAP
			else if (_Utils->event.key.code == sfKeyEscape && _Utils->iEtat == STATEDEFAITE)
			{
				if (_Utils->iEtat = STATEMENU);
				{
					sfSound_stop(_Ingame->musique.musique_jeu);		
					sfSound_stop(_Ingame->musique.Mort);			
					_Ingame->Lancement_musique = 0;			
					New_Game(_Ingame, _Utils);
				}
			}
			else if (_Utils->event.key.code == sfKeyEscape && _Utils->iEtat == STATEPLAY)
			{
				New_Game(_Ingame, _Utils);
				_Ingame->Lancement_musique = 0;
				sfSound_stop(_Ingame->musique.musique_jeu);

				if (_Utils->iEtat == STATEMENU)
				{
					sfSound_play(_Ingame->musique.musique_menu);
				}
			}

			if (_Utils->event.key.code == sfKeyA && _Utils->iEtat == STATEPLAY && _Ingame->Joueur.iEtat == POISON && _Ingame->Ammo.iNb_antidote > 0)
			{
				_Ingame->Ammo.iNb_antidote -= 1;
				_Ingame->Joueur.iEtat = NON_POISON;
			}

			EnterName(_Ingame, _Utils); //Entrée du nom pour la table de score

			Action_Decor(_Ingame, _Utils); //Fonction regroupant l'ensemble des intéractions avec le decor
		}

		//Gestion de l'animation en accors avec les contrôles
		ControlAnimEvenementiel(_Ingame, _Utils);
	
		//Contrôle Menu
		Menu_Contrôle(_Ingame, _Utils);

		//Contrôle Arme HUD
		Weapon_Select(_Utils, _Ingame);
	}
}


//_______________________________________________________________________________________________________________________________________________________


//Regroupement des fonctions commandes temps réel/ évènementiel
void Commande(INGAME* _Ingame, UTILS* _Utils)
{
	Cmd_temps_reel(_Ingame, _Utils);
	Cmd_evenementiel(_Ingame, _Utils);
}