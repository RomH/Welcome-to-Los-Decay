#include "stdafx.h"

void Action_Decor(INGAME* _ingame, UTILS* _utils)
{
	if (_utils->event.key.code == sfKeyE) //Les actions envers l'environnement s'effectuent avec la touche E
	{
		if (_ingame->fDistance_Porte_Joueur <= 230.0f) // si le joueur est suffisament proche de la porte
		{
			if (_ingame->Joueur.iLieux != eReserve_Bar && _ingame->fTimer_Nouvelle_Vague > 2.0f) //il va dans la reserve si il n'y a pas de zombie
			{
				for (int i = 0; i < _ingame->tir.nbTir; i++)
				{
					RemoveTirAt(_utils, _ingame, i);
					i--;
				}
				_ingame->Joueur.iLieux = eReserve_Bar;
				_ingame->Joueur.Position.x = _ingame->Pos_Porte.x - 205.0f;
				_ingame->Joueur.Position.y = _ingame->Pos_Porte.y - 40.0f;
			}

			else if (_ingame->Joueur.iLieux != eBar) //il va dans le bar si il était dans la reserve
			{
				for (int i = 0; i < _ingame->tir.nbTir; i++)
				{
					RemoveTirAt(_utils, _ingame, i);
					i--;
				}
				_ingame->Joueur.iLieux = eBar;
				_ingame->Joueur.Position.x = _ingame->Pos_Porte.x + 180.0f;
				_ingame->Joueur.Position.y = _ingame->Pos_Porte.y - 40.0f;
			}
		}

		if (_ingame->fDistance_Distributeur_Joueur <= 150.0f && _ingame->Joueur.iLieux == eReserve_Bar) 
		{					
			//si le joueur est suffisament proche du distributeur (dans la reserve) il recupère toute sa vie
			lecture_musique(_utils, _ingame, _ingame->musique.canette, 5, 0);		//new
			_ingame->Joueur.iPdv = PDV_JOUEUR_MAX;
		}

		//Réservoir voiture

		//Voiture de gauche
		if (_ingame->fDistance_Reservoir1_Joueur <= 100.0f)
		{
			//_ingame->tir.fTimer_Reload -= _utils->fDeltatime;

			//if (_ingame->tir.fTimer_Reload <= 0.0f)
			//{
			if (_ingame->Ammo.iAmmo_fuel_Total < 500)
			{
				_ingame->Ammo.iAmmo_fuel_Total += 100;

			}
			//_ingame->tir.Reloading = FALSE;
			//_ingame->tir.fTimer_Reload = TIMER_RELOAD_PISTOL;
			//}
		}

		//voiture du milieu en bas
		if (_ingame->fDistance_Reservoir2_Joueur <= 100.0f)
		{
			//_ingame->tir.fTimer_Reload -= _utils->fDeltatime;

			//if (_ingame->tir.fTimer_Reload <= 0.0f)
			//{
			if (_ingame->Ammo.iAmmo_fuel_Total < 500)
			{
				_ingame->Ammo.iAmmo_fuel_Total += 100;

			}
			//_ingame->tir.Reloading = FALSE;
			//_ingame->tir.fTimer_Reload = TIMER_RELOAD_PISTOL;
			//}
		}

		//voiture intérieur
		if (_ingame->fDistance_Reservoir3_Joueur <= 100.0f)
		{
			//_ingame->tir.fTimer_Reload -= _utils->fDeltatime;

			//if (_ingame->tir.fTimer_Reload <= 0.0f)
			//{
			if (_ingame->Ammo.iAmmo_fuel_Total < 500)
			{
				_ingame->Ammo.iAmmo_fuel_Total += 100;
			}
			//_ingame->tir.Reloading = FALSE;
			//_ingame->tir.fTimer_Reload = TIMER_RELOAD_PISTOL;
			//}
		}

	}
}

void Update_Decor(INGAME* _ingame, UTILS* _utils)
{
	//calcul de la distance séparant le joueur des différent élements intéragibles
	_ingame->fDistance_Porte_Joueur = Distance_Euclidienne(_ingame->Joueur.Position, _ingame->Pos_Porte);
	_ingame->fDistance_Distributeur_Joueur = Distance_Euclidienne(_ingame->Joueur.Position, _ingame->Pos_Distributeur_Boisson);
	_ingame->fDistance_Reservoir1_Joueur = Distance_Euclidienne(_ingame->Joueur.Position, _ingame->Pos_Reservoir_Voiture1);
	_ingame->fDistance_Reservoir2_Joueur = Distance_Euclidienne(_ingame->Joueur.Position, _ingame->Pos_Reservoir_Voiture2);
	_ingame->fDistance_Reservoir3_Joueur = Distance_Euclidienne(_ingame->Joueur.Position, _ingame->Pos_Reservoir_Voiture3);

	//translation de la map et différent élements intéragibles selon le lieu
	

}

void Display_Action_Decor(INGAME* _ingame, UTILS* _utils)
{
	//AFFICHAGE FEEDBACK (pour action_decor.cpp) //new!
	if (_ingame->fDistance_Porte_Joueur <= 230.0 && _ingame->Joueur.iLieux == eReserve_Bar)
	{
		Afficher_Sprite(_ingame->Sprite.interact_door, _ingame->Pos_Porte.x - 140, _ingame->Pos_Porte.y - 30, 0.5, 0.3, 0, _utils->window);
	}
	if (_ingame->fDistance_Porte_Joueur <= 230.0 && _ingame->Joueur.iLieux == eBar)
	{
		Afficher_Sprite(_ingame->Sprite.interact_door, _ingame->Pos_Porte.x + 140, _ingame->Pos_Porte.y - 30, 0.5, 0.3, 0, _utils->window);
	}
	if (_ingame->fDistance_Distributeur_Joueur <= 150.0f && _ingame->Joueur.iLieux == eReserve_Bar)
	{
		Afficher_Sprite(_ingame->Sprite.interact_sodaMachine, _ingame->Pos_Distributeur_Boisson.x, _ingame->Pos_Distributeur_Boisson.y, 0.5, 0.3, 0, _utils->window);
	}

	//NEW RESERVOIR
	if (_ingame->fDistance_Reservoir1_Joueur <= 150.0f)
	{
		Afficher_Sprite(_ingame->Sprite.interact_door, _ingame->Pos_Reservoir_Voiture1.x, _ingame->Pos_Reservoir_Voiture1.y, 0.5, 0.3, 0, _utils->window);
	}
	if (_ingame->fDistance_Reservoir2_Joueur <= 150.0f)
	{
		Afficher_Sprite(_ingame->Sprite.interact_door, _ingame->Pos_Reservoir_Voiture2.x, _ingame->Pos_Reservoir_Voiture2.y, 0.5, 0.3, 0, _utils->window);
	}
	if (_ingame->fDistance_Reservoir3_Joueur <= 150.0f)
	{
		Afficher_Sprite(_ingame->Sprite.interact_door, _ingame->Pos_Reservoir_Voiture3.x, _ingame->Pos_Reservoir_Voiture3.y, 0.5, 0.3, 0, _utils->window);
	}

}