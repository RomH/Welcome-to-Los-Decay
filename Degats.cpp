#include "stdafx.h"

void Degat_Armes(INGAME* _Ingame, UTILS* _utils, int _iCompteur)
{
	if (_Ingame->Hud.armes == Batte_de_baseball)
	{
		_Ingame->Zombie[_iCompteur].iPdv -= _Ingame->Upgrade.batte_damage;  //Degat d'un coup de batte		
	}
	else if (_Ingame->Hud.armes == Pistolet)
	{
		_Ingame->Zombie[_iCompteur].iPdv -= _Ingame->Upgrade.pistol_damage;  //Degat d'un tir du pistolet		
	}
	else if (_Ingame->Hud.armes == Fusil)
	{
		_Ingame->Zombie[_iCompteur].iPdv -= _Ingame->Upgrade.fusil_damage;  //Degat d'un tir du Fusil		
	}
	else if (_Ingame->Hud.armes == Fusil_a_pompe)
	{
		_Ingame->Zombie[_iCompteur].iPdv -= DEGAT_FUSIL_A_POMPE;  //Degat d'un tir du Fusil_a_pompe		
	}
	else if (_Ingame->Hud.armes == Grenade)
	{
		_Ingame->Zombie[_iCompteur].iPdv -= _Ingame->Upgrade.grenade_damage;  //Degat d'un tir du Grenade		
	}
}


void Degat_Zombies(INGAME* _ingame, UTILS* _utils, int _iCompteur)
{
	if (_ingame->Zombie[_iCompteur].Calcul.fDist_Joueur_Mob <= 80 && _ingame->Zombie[_iCompteur].iEtat == VIVANT) //Quand le zombie est a porté
	{
		_ingame->Zombie[_iCompteur].Attaque = TRUE;
	}

	if (_ingame->Zombie[_iCompteur].Attaque == TRUE)
	{
		_ingame->Zombie[_iCompteur].fAttack_Speed -= _utils->fDeltatime; //on demarre son timer d'attaque
		_ingame->Zombie[_iCompteur].position.x = _ingame->Zombie[_iCompteur].position.x;
		_ingame->Zombie[_iCompteur].position.y = _ingame->Zombie[_iCompteur].position.y;
	}


	switch (_ingame->Zombie[_iCompteur].Type)  //Verification du type de zombie
	{
	case eZombie:
	{
		if (_ingame->Zombie[_iCompteur].fAttack_Speed <= 0.36f)	//Quand le timer d'attaque passe à 0
		{
			if (_ingame->Joueur.invulnerable == 0 && _ingame->Zombie[_iCompteur].Calcul.fDist_Joueur_Mob <= 80) //Si le joueur peut etre attaqué (n'a pas subit de dégat recemment)
			{
				lecture_musique(_utils, _ingame, _ingame->musique.Degat_joueur, 10, 0);			// new

				_ingame->Joueur.iPdv -= DEGAT_ZOMBIE; //Le zombie lui inflige une quantité de dégats
				_ingame->Joueur.invulnerable = 1;	// et le joueur passe en frame d'invulnérabilité
			}
		}
		if (_ingame->Zombie[_iCompteur].fAttack_Speed <= 0.0f)
		{
			_ingame->Zombie[_iCompteur].fAttack_Speed = ATTACK_SPEED_ZOMBIE; //on remet ensuite le timer d'attaque à sa valeur maximale
			_ingame->Zombie[_iCompteur].Attaque = FALSE;
		}
	}	break;
	}

}

//FRAME INVINCIBILITE du joueur
void Frame_Invincibilite(INGAME* _ingame, UTILS* _utils)
{
	if (_ingame->Joueur.invulnerable == TRUE)
	{
		_ingame->Joueur.Timer_invulnerable -= _utils->fDeltatime;
		_ingame->Joueur.Timer_clignotement -= _utils->fDeltatime;
	}

	if (_ingame->Joueur.Timer_clignotement <= 0.0f || _ingame->Joueur.invulnerable == FALSE)
	{
		_ingame->Joueur.Timer_clignotement = TIMER_CLIGNOTEMENT;
	}
	if (_ingame->Joueur.Timer_invulnerable <= 0.0f)
	{
		_ingame->Joueur.Timer_invulnerable = TIMER_INVULNERABLE;
		_ingame->Joueur.invulnerable = FALSE;
	}
}