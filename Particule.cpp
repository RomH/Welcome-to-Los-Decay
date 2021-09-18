#include "stdafx.h"

#define OLD_FLAME 750.0f
#define YOUNG_FLAME (250.0f)//250.0f
#define COEFF_DE_RESIZE_ANTI_LAG 0.003f

void AjouteParticule(int _posX, int _posY, struct PARTICLE** _first)
{
	struct PARTICLE* tempParticle = (struct PARTICLE*) calloc(sizeof(struct PARTICLE), 1);
	tempParticle->fPos.x = _posX;/* -20 + 40 * (rand() / (float)RAND_MAX);*/
	tempParticle->fPos.y = _posY;/* -20 + 40 * (rand() / (float)RAND_MAX);*/
	tempParticle->fTTLMax = 0.25f*(1 + (rand() / (float)RAND_MAX));
	tempParticle->fTTL = tempParticle->fTTLMax;
	tempParticle->fDeltaRotation = -100 + 200 * (rand() / (float)RAND_MAX);
	tempParticle->fRotation = rand();
	//Insertion de l'élément
	tempParticle->suivant = *_first;
	*_first = tempParticle;
}

void RetireParticule(struct PARTICLE* _current, struct PARTICLE** _first)
{
	struct PARTICLE* tempParticle = *_first;

	if (tempParticle == _current) //Cas particulier du premier élément
	{
		*_first = _current->suivant;
		free(_current);
	}
	else //Si ce n'est pas le premier élément
	{
		while (tempParticle != 0) //On cherche l'élément précédent celui qu'on veut supprimer
		{
			if (tempParticle->suivant == _current)
			{
				tempParticle->suivant = tempParticle->suivant->suivant;
				free(_current);
				return;
			}
			tempParticle = tempParticle->suivant;
		}
	}
}

void Load_Particle(INGAME* _ingame, UTILS* _utils)
{
	for (int i = 0; i < FLAMME_SIZE; i++)
	{
		char LanceFlamme[50] = { 0 };
		sprintf(LanceFlamme, "../Animation/Effect/Flamme/%d.png", i + 1);
		_ingame->Sprite.TabFlamme[i] = LoadSprite(LanceFlamme, 1);
	}
	for (int i = 0; i < VOMI_SIZE; i++)
	{
		char Vomi[50] = { 0 };
		sprintf(Vomi, "../Animation/Effect/Vomi/%d.png", i + 1);
		_ingame->Sprite.TabVomi[i] = LoadSprite(Vomi, 1);
	}
}



void Display_Particles(INGAME* _Ingame, UTILS* _Utils)
{
	PARTICLE* tempParticle = _Ingame->Particle.iFirstParticle;
	float size; //taille temporaire pour le sprite
	//coeff d'ajustement de portée par rapport à la durée de vie des particules.
	//(qui est modifiée dans les améliorations du lance-flamme).
	float ajusteur;

	while (tempParticle != 0)
	{

		int current_case;

		current_case = (1 - tempParticle->fTTL / tempParticle->fTTLMax) * FLAMME_SIZE;

		//New
		//Combo
		if (_Ingame->Upgrade.toggle_growing_fire == TRUE) //quand l'amélioration "Growing Fire" est débloquée.
		{
			//calcul de direction de la particule
			sfVector2f direction;
			direction.x = tempParticle->fPos.x - _Ingame->Joueur.Position.x;
			direction.y = tempParticle->fPos.y - _Ingame->Joueur.Position.y;
			//calcul de distance entre la particule et le joueur
			float distance = Length(direction);

			//permet d'adapter la taille de la particule par rapport à sa distance entre elle et le joueur.
			//la particule ne subit pas le coeff anti-lag en milieu/fin de vie.
			if (distance < OLD_FLAME && distance > YOUNG_FLAME)
			{
				_Ingame->Upgrade.flamethrower_growing_fire = (distance / YOUNG_FLAME)*FLAMETHROWER_WIDTH;
				_Ingame->Upgrade.flamethrower_width = FLAMETHROWER_WIDTH + (0.25f*FLAMETHROWER_WIDTH) + (_Ingame->Upgrade.flamethrower_growing_fire*FLAMETHROWER_WIDTH);
				size = _Ingame->Upgrade.flamethrower_width;
			}
			//la particule subit le coeff anti-lag en début de vie.
			if (distance <= YOUNG_FLAME)
			{
				_Ingame->Upgrade.flamethrower_growing_fire = (distance / 250)*FLAMETHROWER_WIDTH;
				_Ingame->Upgrade.flamethrower_width = FLAMETHROWER_WIDTH + (0.25f*FLAMETHROWER_WIDTH) + (_Ingame->Upgrade.flamethrower_growing_fire*FLAMETHROWER_WIDTH) + ((_Utils->iCompteur_Zombie - _Ingame->iCompteur_Kill)*COEFF_DE_RESIZE_ANTI_LAG);
				size = _Ingame->Upgrade.flamethrower_width;
			}
		}
		else //quand l'amélioration "Growing Fire" n'est pas débloquée.
		{
			//calcul de direction de la particule
			sfVector2f direction;
			direction.x = tempParticle->fPos.x - _Ingame->Joueur.Position.x;
			direction.y = tempParticle->fPos.y - _Ingame->Joueur.Position.y;
			//calcul de distance entre la particule et le joueur
			float distance = Length(direction);

			if (_Ingame->combo.iMilestone < 36)
			{
				ajusteur = 0.5f; //avant la 1ère amélioration de portée
			}
			else if (_Ingame->combo.iMilestone < 40 && _Ingame->combo.iMilestone >= 36)
			{
				ajusteur = 0.75f; //avant la 2èm amélioration de portée
			}
			else
			{
				ajusteur = 1.0f; //après l'amélioration max de portée
			}
			//printf("ajusteur %f\n", ajusteur);

			//permet d'adapter la taille de la particule par rapport à sa distance entre elle et le joueur.
			//la particule ne subit pas le coeff anti-lag en milieu/fin de vie.
			if (distance > (250.0f*ajusteur))
			{
				_Ingame->Upgrade.flamethrower_width = FLAMETHROWER_WIDTH + ((_Utils->iCompteur_Zombie - _Ingame->iCompteur_Kill)*0.0015);
				size = _Ingame->Upgrade.flamethrower_width;
			}
			//la particule subit le coeff anti-lag en début de vie.
			if (distance <= (250.0f*ajusteur))
			{
				_Ingame->Upgrade.flamethrower_width = FLAMETHROWER_WIDTH + ((_Utils->iCompteur_Zombie - _Ingame->iCompteur_Kill)*0.003);
				size = _Ingame->Upgrade.flamethrower_width;
			}
		}

		if (current_case > FLAMME_SIZE)
		{
			current_case = 0;
		}
		//Action
		if (sfMouse_isButtonPressed(sfMouseLeft) && _Ingame->iArme_Choisie == LanceFlamme)
		{
			Afficher_Sprite(_Ingame->Sprite.TabFlamme[current_case], tempParticle->fPos.x, tempParticle->fPos.y, size, size, tempParticle->fRotation, _Utils->window); //MàJ
		}
		//Idle
		else if (!sfMouse_isButtonPressed(sfMouseLeft) && _Ingame->iArme_Choisie == LanceFlamme)
		{
			Afficher_Sprite(_Ingame->Sprite.TabFlamme[current_case], tempParticle->fPos.x, tempParticle->fPos.y, 0.01f, 0.01f, tempParticle->fRotation, _Utils->window); //MàJ
		}

		tempParticle = tempParticle->suivant;
	}

}




//void Display_Particles(INGAME* _Ingame, UTILS* _Utils)
//{
//	PARTICLE* tempParticle = _Ingame->Particle.iFirstParticle;
//
//	while (tempParticle != 0)
//	{
//
//		int current_case;
//
//		current_case = (1 - tempParticle->fTTL / tempParticle->fTTLMax) * FLAMME_SIZE;
//		//printf("%d", current_case);
//		if (current_case > FLAMME_SIZE)
//		{
//			current_case = 0;
//		}
//
//		if (sfMouse_isButtonPressed(sfMouseLeft) && _Ingame->iArme_Choisie == LanceFlamme)
//		{
//			Afficher_Sprite(_Ingame->Sprite.TabFlamme[current_case], tempParticle->fPos.x, tempParticle->fPos.y, 0.75f, 0.75f, tempParticle->fRotation, _Utils->window);
//		}
//		else if (!sfMouse_isButtonPressed(sfMouseLeft) && _Ingame->iArme_Choisie == LanceFlamme)
//		{
//			Afficher_Sprite(_Ingame->Sprite.TabFlamme[current_case], tempParticle->fPos.x, tempParticle->fPos.y, 0.05f, 0.05f, tempParticle->fRotation, _Utils->window);
//		}
//
//		tempParticle = tempParticle->suivant;
//	}
//
//}