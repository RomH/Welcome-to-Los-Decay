#include "stdafx.h"

void Deplacement_Joueur(INGAME* _Ingame, UTILS* _Utils)
{
	if (_Ingame->Joueur.Position.x > 0 && _Ingame->Joueur.Position.x < 6144 && _Ingame->Joueur.Position.y > 0 && _Ingame->Joueur.Position.y < 4668)
	{
		if (sfKeyboard_isKeyPressed(sfKeyZ) == 0 && sfKeyboard_isKeyPressed(sfKeyS) == 0 && sfKeyboard_isKeyPressed(sfKeyQ) == 0 && sfKeyboard_isKeyPressed(sfKeyD) == 0)
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_IMMOBILE;
		}

		if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyQ))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_HAUT_GAUCHE;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int i = 0; i < XPERSO; i++)
			{
				for (int j = 40; j < 90; j++)
				{
					sfColor Color_Colision_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2 - 3) + i, _Ingame->Joueur.Position.y - 1 + j);
					Colisions_Perso_Color(_Ingame, _Utils, Color_Colision_Perso, &i, &j, XPERSO, YPERSO, DP_HAUT_GAUCHE, DP_IMMOBILE);
				}
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyD))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_HAUT_DROITE;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int i = 0; i < XPERSO; i++)
			{
				for (int j = 40; j < 90; j++)
				{
					sfColor Color_Colision_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2 + 3) + i, _Ingame->Joueur.Position.y - 1 + j);
					Colisions_Perso_Color(_Ingame, _Utils, Color_Colision_Perso, &i, &j, XPERSO, YPERSO, DP_HAUT_DROITE, DP_IMMOBILE);
				}
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyS) && sfKeyboard_isKeyPressed(sfKeyQ))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_BAS_GAUCHE;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int i = 0; i < XPERSO; i++)
			{
				for (int j = 40; j < 90; j++)
				{
					sfColor Color_Colision_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2 - 3) + i, _Ingame->Joueur.Position.y + 90);
					Colisions_Perso_Color(_Ingame, _Utils, Color_Colision_Perso, &i, &j, XPERSO, YPERSO, DP_BAS_GAUCHE, DP_GAUCHE);
				}
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyS) && sfKeyboard_isKeyPressed(sfKeyD))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_BAS_DROITE;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int i = 0; i < XPERSO; i++)
			{
				for (int j = 40; j < 90; j++)
				{
					sfColor Color_Colision_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2 + 3) + i, _Ingame->Joueur.Position.y + 90);
					Colisions_Perso_Color(_Ingame, _Utils, Color_Colision_Perso, &i, &j, XPERSO, YPERSO, DP_BAS_DROITE, DP_DROITE);
				}
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyZ))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_HAUT;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int i = 0; i < XPERSO; i++)
			{
				sfColor Color_Haut_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2) + i, _Ingame->Joueur.Position.y + 35);
				Colisions_Perso_Color(_Ingame, _Utils, Color_Haut_Perso, &i, &i, XPERSO, XPERSO, DP_HAUT, DP_IMMOBILE);
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyS))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_BAS;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int i = 0; i < XPERSO; i++)
			{
				sfColor Color_Bas_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2) + i, _Ingame->Joueur.Position.y + 90);
				Colisions_Perso_Color(_Ingame, _Utils, Color_Bas_Perso, &i, &i, XPERSO, XPERSO, DP_BAS, DP_IMMOBILE);
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyQ))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_GAUCHE;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			//Collision couleur
			for (int j = 40; j < 90; j++)
			{
				sfColor Color_gauche_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x - XPERSO / 2) - 1, _Ingame->Joueur.Position.y + j);
				Colisions_Perso_Color(_Ingame, _Utils, Color_gauche_Perso, &j, &j, YPERSO, YPERSO, DP_GAUCHE, DP_IMMOBILE);
			}
		}
		else if (sfKeyboard_isKeyPressed(sfKeyD))
		{
			_Ingame->Joueur.Direction_Perso_Joueur = DP_DROITE;

			SonMarche(_Ingame, _Utils); // son des pas du joueur

			////Collision couleur
			for (int j = 40; j < 90; j++)
			{
				sfColor Color_Droite_Perso = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Joueur.Position.x + XPERSO / 2) + 1, _Ingame->Joueur.Position.y + j);
				Colisions_Perso_Color(_Ingame, _Utils, Color_Droite_Perso, &j, &j, YPERSO, YPERSO, DP_DROITE, DP_IMMOBILE);
			}
		}

		//Physique des conditions
		if (_Ingame->Joueur.Direction_Perso_Joueur == DP_IMMOBILE)
		{
			_Ingame->Joueur.Velocity = 0.0f;
			_Ingame->Joueur.Position.x = _Ingame->Joueur.Position.x;
			_Ingame->Joueur.Position.y = _Ingame->Joueur.Position.y;
		}
		else if (_Ingame->Joueur.Direction_Perso_Joueur == DP_HAUT)
		{
			_Ingame->Joueur.Velocity = 400;
			_Ingame->Joueur.Position.y -= _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}
		else if (_Ingame->Joueur.Direction_Perso_Joueur == DP_BAS)
		{
			_Ingame->Joueur.Velocity = 400;
			_Ingame->Joueur.Position.y += _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}

		if (_Ingame->Joueur.Direction_Perso_Joueur == DP_GAUCHE)
		{
			_Ingame->Joueur.Velocity = 400;
			_Ingame->Joueur.Position.x -= _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}
		else if (_Ingame->Joueur.Direction_Perso_Joueur == DP_DROITE)
		{
			_Ingame->Joueur.Velocity = 400;
			_Ingame->Joueur.Position.x += _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}

		if (_Ingame->Joueur.Direction_Perso_Joueur == DP_HAUT_GAUCHE)
		{
			_Ingame->Joueur.Velocity = 290.8f;
			_Ingame->Joueur.Position.x -= _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
			_Ingame->Joueur.Position.y -= _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}
		else if (_Ingame->Joueur.Direction_Perso_Joueur == DP_HAUT_DROITE)
		{
			_Ingame->Joueur.Velocity = 290.8f;
			_Ingame->Joueur.Position.x += _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
			_Ingame->Joueur.Position.y -= _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}
		else if (_Ingame->Joueur.Direction_Perso_Joueur == DP_BAS_GAUCHE)
		{
			_Ingame->Joueur.Velocity = 290.8f;
			_Ingame->Joueur.Position.x -= _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
			_Ingame->Joueur.Position.y += _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}
		else if (_Ingame->Joueur.Direction_Perso_Joueur == DP_BAS_DROITE)
		{
			_Ingame->Joueur.Velocity = 290.8f;
			_Ingame->Joueur.Position.x += _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
			_Ingame->Joueur.Position.y += _Ingame->Joueur.Velocity * _Utils->fDeltatime * _Ingame->Joueur.ValeurSprint;
		}
	}
}


//____________________________________________________________________________________________

void Deplacement_Zombie(INGAME* _Ingame, UTILS* _Utils, int _id)
{
	if (_Ingame->Zombie[_id].position.x > 0 && _Ingame->Zombie[_id].position.x < 6144 && _Ingame->Zombie[_id].position.y > 0 && _Ingame->Zombie[_id].position.y < 4668)
	{
		//Collsision sur la droite + en haut
		if (_Ingame->Joueur.Position.x > _Ingame->Zombie[_id].position.x  &&
			_Ingame->Joueur.Position.y < _Ingame->Zombie[_id].position.y)
		{
			//Collision couleur
			for (int i = 0; i < 90; i++)
			{
				for (int j = 40; j < 92; j++)
				{
					_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 45) + i, _Ingame->Zombie[_id].position.y + j);
					Colisions_Mob_Color(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &i, &j, 90, 184, _id, DP_MOBILE);
				}
			}
		}

		//Collsision sur la droite + en bas
		if (_Ingame->Joueur.Position.x > _Ingame->Zombie[_id].position.x  &&
			_Ingame->Joueur.Position.y > _Ingame->Zombie[_id].position.y)
		{
			//Collision couleur
			for (int i = 0; i < 90; i++)
			{
				for (int j = 40; j < 92; j++)
				{
					_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 45) + i, _Ingame->Zombie[_id].position.y + j);
					Colisions_Mob_Color(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &i, &j, 90, 184, _id, DP_MOBILE);
				}
			}
		}

		//Collsision sur la gauche + en haut
		if (_Ingame->Joueur.Position.x < _Ingame->Zombie[_id].position.x &&
			_Ingame->Joueur.Position.y < _Ingame->Zombie[_id].position.y)
		{
			//Collision couleur
			for (int i = 0; i < 90; i++)
			{
				for (int j = 40; j < 92; j++)
				{
					_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 45) + i, _Ingame->Zombie[_id].position.y + j);
					Colisions_Mob_Color(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &i, &j, 90, 184, _id, DP_MOBILE);
				}
			}
		}

		//Collsision sur la gauche + en bas
		if (_Ingame->Joueur.Position.x < _Ingame->Zombie[_id].position.x  &&
			_Ingame->Joueur.Position.y > _Ingame->Zombie[_id].position.y)
		{
			//Collision couleur
			for (int i = 0; i < 90; i++)
			{
				for (int j = 40; j < 92; j++)
				{
					_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 45) + i, _Ingame->Zombie[_id].position.y + j);
					Colisions_Mob_Color(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &i, &j, 90, 184, _id, DP_MOBILE);
				}
			}
		}


		//Physique des conditions
		if (_Ingame->Zombie[_id].Sens_Marche == DP_MOBILE && _Ingame->Zombie[_id].Recherche == FALSE)
		{
			_Ingame->Zombie[_id].position.x += _Ingame->Zombie[_id].Calcul.Direction_Mob_Joueur.x * _Ingame->Zombie[_id].Vitesse.x * _Utils->fDeltatime;
			_Ingame->Zombie[_id].position.y += _Ingame->Zombie[_id].Calcul.Direction_Mob_Joueur.y * _Ingame->Zombie[_id].Vitesse.y * _Utils->fDeltatime;
		}

		else if (_Ingame->Zombie[_id].Recherche == TRUE)
		{

			//Collision contournement Haut
			for (int i = 0; i < 60; i++)
			{
				_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 35) + i, _Ingame->Zombie[_id].position.y - 1 + 40);
				Contournement_Zombie(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &i, &i, 90, 184, _id, Contourne_Haut);
			}
			//Collision contournement Bas
			for (int i = 0; i < 60; i++)
			{
				_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 35) + i, _Ingame->Zombie[_id].position.y + 1 + 92);
				Contournement_Zombie(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &i, &i, 90, 184, _id, Contourne_Bas);
			}
			//Collision contournement Gauche
			for (int j = 55; j < 85; j++)
			{
				_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x - 45 - 1), _Ingame->Zombie[_id].position.y + j);
				Contournement_Zombie(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &j, &j, 90, 184, _id, Contourne_Gauche);
			}
			//Collision contournement Droit
			for (int j = 55; j < 85; j++)
			{
				_Ingame->Zombie[_id].Color_Colision_Zombie = sfImage_getPixel(_Ingame->Sprite.Image_Map_Color, (_Ingame->Zombie[_id].position.x + 45 + 1), _Ingame->Zombie[_id].position.y + j);
				Contournement_Zombie(_Ingame, _Utils, _Ingame->Zombie[_id].Color_Colision_Zombie, &j, &j, 90, 184, _id, Contourne_Droite);
			}


			_Ingame->Zombie[_id].fTimer_Recherche -= _Utils->fDeltatime;

			if (_Ingame->Zombie[_id].fTimer_Recherche >= 0.0f)
			{
				_Ingame->Zombie[_id].position.x += _Ingame->Zombie[_id].Calcul.Direction_Mob_Cible.x * _Ingame->Zombie[_id].Vitesse.x * _Utils->fDeltatime;
				_Ingame->Zombie[_id].position.y += _Ingame->Zombie[_id].Calcul.Direction_Mob_Cible.y * _Ingame->Zombie[_id].Vitesse.y * _Utils->fDeltatime;
			}
			else
			{
				_Ingame->Zombie[_id].fTimer_Recherche = 1.0f;
				_Ingame->Zombie[_id].Recherche = FALSE;
			}
		}
	}
}

void Sprinte_joueur(INGAME* _ingame, UTILS* _utils)
{
	if (_ingame->Joueur.courir == TRUE)
	{
		_ingame->Joueur.ValeurSprint = 1.5f;
		_ingame->Joueur.jauge_energie -= _utils->fDeltatime;
	}

	if (!sfKeyboard_isKeyPressed(sfKeyLShift) && _ingame->Joueur.courir == FALSE && _ingame->Joueur.jauge_energie <= 2.0f)
	{
		_ingame->Joueur.ValeurSprint = 1.0f;
		_ingame->Joueur.jauge_energie += _utils->fDeltatime * 0.8;
	}
}