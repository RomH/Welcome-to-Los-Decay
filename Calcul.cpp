#include "stdafx.h"

void Distance_Joueur_Zombie(INGAME* _Ingame, UTILS* _Utils)
{
	for (int i = 0; i < _Ingame->iNbr_Zombie_Max; i++)
	{
		//DISTANCE Zombie / JOUEUR
		_Ingame->Zombie[i].Calcul.Dist_Joueur_Mob.x = _Ingame->Joueur.Position.x - _Ingame->Zombie[i].position.x;  //Distance mob_joueur x et y
		_Ingame->Zombie[i].Calcul.Dist_Joueur_Mob.y = _Ingame->Joueur.Position.y - _Ingame->Zombie[i].position.y;

		_Ingame->Zombie[i].Calcul.fDist_Joueur_Mob = sqrt(pow(_Ingame->Zombie[i].Calcul.Dist_Joueur_Mob.x, 2) + pow(_Ingame->Zombie[i].Calcul.Dist_Joueur_Mob.y, 2)); //distance de manhattan

		_Ingame->Zombie[i].Calcul.Direction_Mob_Joueur.x = _Ingame->Zombie[i].Calcul.Dist_Joueur_Mob.x / _Ingame->Zombie[i].Calcul.fDist_Joueur_Mob;  // normalisation x et y
		_Ingame->Zombie[i].Calcul.Direction_Mob_Joueur.y = _Ingame->Zombie[i].Calcul.Dist_Joueur_Mob.y / _Ingame->Zombie[i].Calcul.fDist_Joueur_Mob;
	}
}

void Distance_Zombie_Cible(INGAME* _Ingame, UTILS* _Utils)
{
	for (int i = 0; i < _Ingame->iNbr_Zombie_Max; i++)
	{
		//DISTANCE Zombie / Cible
		_Ingame->Zombie[i].Calcul.Dist_Cible_Mob.x = _Ingame->Zombie[i].Cible.x - _Ingame->Zombie[i].position.x;  //Distance mob_Cible x et y
		_Ingame->Zombie[i].Calcul.Dist_Cible_Mob.y = _Ingame->Zombie[i].Cible.y - _Ingame->Zombie[i].position.y;

		_Ingame->Zombie[i].Calcul.fDist_Cible_Mob = sqrt(pow(_Ingame->Zombie[i].Calcul.Dist_Cible_Mob.x, 2) + pow(_Ingame->Zombie[i].Calcul.Dist_Cible_Mob.y, 2)); //distance de manhattan

		_Ingame->Zombie[i].Calcul.Direction_Mob_Cible.x = _Ingame->Zombie[i].Calcul.Dist_Cible_Mob.x / _Ingame->Zombie[i].Calcul.fDist_Cible_Mob;  // normalisation x et y
		_Ingame->Zombie[i].Calcul.Direction_Mob_Cible.y = _Ingame->Zombie[i].Calcul.Dist_Cible_Mob.y / _Ingame->Zombie[i].Calcul.fDist_Cible_Mob;
	}
}



float Distance_Euclidienne(sfVector2f _V1, sfVector2f _V2)
{
	float total = 0.0;

	total = (float)sqrt((_V2.x - _V1.x)*(_V2.x - _V1.x) + (_V2.y - _V1.y)*(_V2.y - _V1.y));
	return total;
}

float Length(sfVector2f v)  //Calcul distance Manhattan
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

sfVector2f Normalize(sfVector2f v)
{
	float length = Length(v);
	v.x /= length;   
	v.y /= length;
	return v;
}

sfVector2f angleToDirection(float rotation) // en degré
{
	float rotationRadian = rotation * PI / 180.0f;
	sfVector2f direction;
	direction.x = cosf(rotationRadian);
	direction.y = sinf(rotationRadian);
	return direction;
}


float directionToAngle(sfVector2f v) // normalisé
{
	float angle = acosf(v.x);
	if (v.y < 0)
		angle *= -1;
	return angle / PI * 180.0f;
}

float RotationPerso(INGAME* _ingame, UTILS* _utils)
{
	/*_utils->Mouse = sfMouse_getPositionRenderWindow(_utils->window);*/
	_ingame->Joueur.vOrientation.x = _utils->Mouse.x - _ingame->Joueur.Position.x;
	_ingame->Joueur.vOrientation.y = _utils->Mouse.y - _ingame->Joueur.Position.y;

	_ingame->Joueur.vOrientation = Normalize(_ingame->Joueur.vOrientation);
	//printf("%f\n", directionToAngle(_ingame->Joueur.vOrientation));
	return  directionToAngle(_ingame->Joueur.vOrientation);
};