#include "stdafx.h"

// FORMAT SVG


//Collision PERSO / DECOR
void Colisions_Perso_Color(INGAME* _Ingame, UTILS* _Utils, sfColor _Color_Perso, int* _BoucleForI, int* _BoucleForJ, int _X_Perso, int _Y_Perso, int Direction_Deplacement_Perso, int _idle)
{
	if (_Color_Perso.r == 255 && _Color_Perso.g == 255 && _Color_Perso.b == 255 && _Color_Perso.a == 255)
	{
		
		_Ingame->Joueur.Direction_Perso_Joueur = Direction_Deplacement_Perso;
	}
	else
	{
		_Ingame->Joueur.Direction_Perso_Joueur = _idle;

		*_BoucleForI = _X_Perso;
		*_BoucleForJ = _Y_Perso;
	}
}



void Colisions_Mob_Color(INGAME* _Ingame, UTILS* _Utils, sfColor _Color_Zombie, int* _BoucleForI, int* _BoucleForJ, int _posX, int _posy, int _id, int Sens_marche)
{

	//LEs zombies normaux / boomer / toxic marchent dans les ZONES BLANCHES
	if (_Ingame->Zombie[_id].iIA == eZombie || _Ingame->Zombie[_id].iIA == eBoomer || _Ingame->Zombie[_id].iIA == eToxic)
	{
		if (_Color_Zombie.r == 255 && _Color_Zombie.g == 255 && _Color_Zombie.b == 255 && _Color_Zombie.a == 255)
		{
			//printf("Bouge\n");
			_Ingame->Zombie[_id].Sens_Marche = Sens_marche;
		}
		else
		{
			_Ingame->Zombie[_id].Recherche = TRUE;

			*_BoucleForI = _posX;
			*_BoucleForJ = _posy;
		}
	}
}



void Contournement_Zombie(INGAME* _Ingame, UTILS* _Utils, sfColor _Color_Zombie, int* _BoucleForI, int* _BoucleForJ, int _posX, int _posy, int _id, int Contournement)
{

	//Les zombie normaux / boomer / toxic ne collisione que sur les couleur rouge / bleu / noir
	if (_Ingame->Zombie[_id].iIA == eZombie || _Ingame->Zombie[_id].iIA == eBoomer || _Ingame->Zombie[_id].iIA == eToxic)
	{
		if (_Color_Zombie.r == 0 && _Color_Zombie.g == 0 && _Color_Zombie.b == 0 && _Color_Zombie.a == 255 ||
			_Color_Zombie.r == 255 && _Color_Zombie.g == 0 && _Color_Zombie.b == 0 && _Color_Zombie.a == 255 ||
			_Color_Zombie.r == 0 && _Color_Zombie.g == 0 && _Color_Zombie.b == 255 && _Color_Zombie.a == 255)
		{
			_Ingame->Zombie[_id].Sens_Contournement = Contournement;

			if (_Ingame->Zombie[_id].Sens_Contournement == Contourne_Haut)
			{
				//printf("Haut\n");
				_Ingame->Zombie[_id].Cible.x = _Ingame->Zombie[_id].position.x + (10000 - rand() % 20000);
				_Ingame->Zombie[_id].Cible.y = _Ingame->Zombie[_id].position.y + (100 + rand() % 100);
			}
			else if (_Ingame->Zombie[_id].Sens_Contournement == Contourne_Bas)
			{
				//printf("Bas\n");
				_Ingame->Zombie[_id].Cible.x = _Ingame->Zombie[_id].position.x + (10000 - rand() % 20000);
				_Ingame->Zombie[_id].Cible.y = _Ingame->Zombie[_id].position.y - (100 + rand() % 100);
			}
			else if (_Ingame->Zombie[_id].Sens_Contournement == Contourne_Gauche)
			{
				//printf("Gauche\n");
				_Ingame->Zombie[_id].Cible.x = _Ingame->Zombie[_id].position.x + (100 + rand() % 100);
				_Ingame->Zombie[_id].Cible.y = _Ingame->Zombie[_id].position.y + (10000 - rand() % 20000);
			}
			else if (_Ingame->Zombie[_id].Sens_Contournement == Contourne_Droite)
			{
				//printf("Droite\n");
				_Ingame->Zombie[_id].Cible.x = _Ingame->Zombie[_id].position.x - (100 + rand() % 100);
				_Ingame->Zombie[_id].Cible.y = _Ingame->Zombie[_id].position.y + (10000 - rand() % 20000);
			}
		}
	}	
}
