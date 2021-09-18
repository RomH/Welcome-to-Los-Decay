#include "stdafx.h"

//BONUS
#define HITBOX_X 100.0f
#define HITBOX_Y 100.0f
#define HITBOX_SPAWN 50
#define SBOOST_NORMAL 40.0f
#define SBOOST_DIAG 29.0f

//BONUS TAUX DE LOOT
#define RAND_MAX_BONUS 5
//TIMER
#define TIMER_SUPPR 10.0f
#define TIMER_BOOST 5.0f
//Resize
#define AMMO_SIZE 0.25f

#define MAX_ANTIDOTE 3
#define NORMAL_VELOCITY 1.0f

//Fonction ajout/suppr version tableau
void AddBonus(INGAME* _Ingame, UTILS* _Utils, struct BONUS bonus)
{
	if (_Ingame->iNb_bonus < _Ingame->iNb_bonus_Max)
	{
		_Ingame->bonus[_Ingame->iNb_bonus] = bonus;
		_Ingame->iNb_bonus++;
	}
}
void RemoveBonusAt(INGAME* _Ingame, UTILS* _Utils, int id)
{
	_Ingame->iNb_bonus--;
	_Ingame->bonus[id] = _Ingame->bonus[_Ingame->iNb_bonus];
}

void Bonus_LoadSprite(INGAME* _Ingame)
{
	_Ingame->Sprite.Ammo = LoadSprite("../Sprite/Bonus/Ammo.png", 1);
	_Ingame->Sprite.Antidote = LoadSprite("../Sprite/Bonus/Antidote.png", 1);
}
void Bonus_initialisation(INGAME* _Ingame, UTILS* _Utils)
{
	_Ingame->iNb_bonus = RESET;
	_Ingame->iNb_bonus_Max = MAX_BONUS;
	//New
	
	_Ingame->Ammo.iNb_antidote = 0;	//new//
}

void Bonus_spawn(INGAME* _Ingame, UTILS* _Utils, int indice)
{
	struct BONUS updateB = { 0 }; //temp pour créer un bonus
	updateB.bonustype = rand() % RAND_MAX_BONUS;

	if (updateB.bonustype >= rand() % RAND_MAX_BONUS + 1)
	{
		updateB.position.x = _Ingame->Zombie[indice].position.x;
		updateB.position.y = _Ingame->Zombie[indice].position.y;
		updateB.timer_disappear = RESET;
		updateB.timer_disappear = _Utils->fDeltatime;
		AddBonus(_Ingame, _Utils, updateB);
		//printf("munitions afficher = %d\n", i);
	}
	else if (updateB.bonustype == eRien)
	{
		indice--;
	}
}

void Bonus_update(INGAME* _Ingame, UTILS* _Utils)
{
	for (int i = 0; i < _Ingame->iNb_bonus; i++)
	{
		//si timer = 0
		//Timer avant de delete les loots
		_Ingame->bonus[i].timer_disappear += 1.0f * _Utils->fDeltatime;
		//si timer_disappear est supérieur ou égale au temps du define "TIMER_SUPPR" alors ça disparait
		if (_Ingame->bonus[i].timer_disappear >= _Utils->fDeltatime + (TIMER_SUPPR))
		{
			RemoveBonusAt(_Ingame, _Utils, i);
			i--;
		}
		if (_Ingame->Joueur.iLieux != eBar)
		{
			RemoveBonusAt(_Ingame, _Utils, i);
		}

		//Hitbox de ramassage
		if (_Ingame->Joueur.Position.x <= _Ingame->bonus[i].position.x + (HITBOX_X + (HITBOX_X / 2)) && //droite * coeff sinon c'est trop proche de l'origin du bonus (pour x ou y raisons).
			_Ingame->Joueur.Position.x >= _Ingame->bonus[i].position.x - (HITBOX_X) && //gauche * coeff sinon c'est trop proche de l'origin du bonus (pour x ou y raisons).
			_Ingame->Joueur.Position.y <= _Ingame->bonus[i].position.y + (HITBOX_Y + (HITBOX_Y / 2)) && //bas
			_Ingame->Joueur.Position.y >= _Ingame->bonus[i].position.y - HITBOX_Y)
		{
			//ramassage antidote
			if (_Ingame->bonus[i].bonustype == eAntidote && _Ingame->Ammo.iNb_antidote <= MAX_ANTIDOTE)
			{
				_Ingame->Ammo.iNb_antidote += 1;
			}
			//ramassages des munitions
			if (_Ingame->bonus[i].bonustype != eAntidote &&
				_Ingame->bonus[i].bonustype != eRien)
			{
				Add_Munition(_Ingame, _Utils);
			}

			RemoveBonusAt(_Ingame, _Utils, i);
			i--;

		}
	}
}

void Bonus_Display(INGAME* _Ingame, UTILS* _Utils)
{
	for (int i = 0; i < _Ingame->iNb_bonus; i++)
	{
		//Munitions
		if (_Ingame->bonus[i].bonustype == eAmmo_Pistol || _Ingame->bonus[i].bonustype == eAmmo_Rifle || _Ingame->bonus[i].bonustype == eAmmo_Shotgun)
		{
			Afficher_Sprite(_Ingame->Sprite.Ammo, _Ingame->bonus[i].position.x, _Ingame->bonus[i].position.y, AMMO_SIZE, AMMO_SIZE, 0, _Utils->window); //caisse à munitions
		}

		//Antidote
		if (_Ingame->bonus[i].bonustype == eAntidote)
		{
			Afficher_Sprite(_Ingame->Sprite.Antidote, _Ingame->bonus[i].position.x, _Ingame->bonus[i].position.y, AMMO_SIZE, AMMO_SIZE, 0, _Utils->window);
		}
	}
}