#include "stdafx.h"

// /!\ PAS TOUCHE AUX NOTES!!! /!\

//Degat par coups:
//couteaux = 25
//pistolet = 25
//fusil = 25
//tronçonneuse  = 50
//fusil à pompe = 100
//grenade = 125
//Hp zombie conseiller:
//hunter = 75hp
//normaux = 100hp
//boomer = 125hp
//BOSS = 900hp
//Nombre de coups pour le boss(dégâts de base):
//uzi = 36coups
//pistolet = 36coups
//pompe = 9coups
//grenade = 8coups (<== 7,2) 
//Score par type de Zombie (sans multiplicateurs):
//Hunter = 75pts
//Normaux = 100pts
//Boomer = 125pts
//BOSS = 1000pts

//Arme.cpp ===> ";" après un while()

//________________________________________________ UPGRADE ________________________________________________
//INFLUENT SUR: Vitesse d'attaque/tir, Degats,Taille d'explosion, Dispersion, Total de munition pouvant être portée par ARME!


//AMMO Ammo; //structure pour modifer le total munitions en réserve
//Tir.cpp //pour modif des stats d'armes
//Hud.cpp //pour déblocage des armes
//structure.h //contient les structure: TIR/AMMO/BONUS/SCORE/COMBO/UPGRADE
//zombie.cpp //MàJ des "COMBOS" !!!

//A CODER: BATTE, (...) , "Grenade, Chainsaw, Katana (= finir de les coder)", lance-flamme


//Milestones  (numero dispo ==> upgrade / armes):
//023, 026, 030, 032, 035, 036, 037, 044, 047,
//050, 053, 054, 055, 057, 059, 062, 063, 064,
//065, 068, 070, 072, 074, 076, 078, 080, 085,
//095, 100, 105, 110, 120, 125



//==============================================
//==============================================
//DEBLOCAGE ARMES
#define UNLOCK_KATANA 3  //3
#define UNLOCK_MACHINEGUN 4  //4
#define UNLOCK_SHOTGUN 9  //9
#define UNLOCK_GRENADE 19 //19
#define UNLOCK_CHAINSAW 39 //39
#define UNLOCK_FLAMETHROWER 50  //50

//UPGRADES
#define DOUBLE 2
#define QUAD 4

#define ONE_QUARTILE 1.25
#define ONE_DEMI 1.5
#define ONE_D_PLUS_Q 1.75

#define SHOTGUN_WIDESHOT 10
#define SHOTGUN_MULTISHOT 12
#define MACHINEGUN_ACCURACY 8
#define BULLET 1

//AUTRE
#define ANIMATION_X 570.0f
#define ANIMATION_Y 100
#define BALL_X (ANIMATION_X)
#define BALL_Y 100
#define BALL_DESTINATION_X 390.0f
#define FEEDBACK_X (LONGUEUR/2)
#define FEEDBACK_Y (HAUTEUR-80.0f)
#define FEEDBACK_SCALEX 0.75f
#define FEEDBACK_SCALEY 0.5f
//position texte
#define C_HUD_X 1690
#define C_HUD_Y 45
//TIMER
#define TIME 0.97f
#define TIMER_COMBO 40.0f
#define TIMER_FEEDBACK 3.0f
#define BALL_SPEED ((ANIMATION_X - BALL_DESTINATION_X)/TIMER_COMBO)
//MILESTONE
#define RIEN 0
//58 milestone max


void Combo_Initialisation(INGAME* _Ingame, UTILS* _Utils)
{
	//SPRITES
	_Ingame->Sprite.Multiply = LoadSprite("../Sprite/Combo/x.png", 0);
	_Ingame->Sprite.Slider = LoadSprite("../Sprite/Combo/barre.png", 0);
	_Ingame->Sprite.Ball_Slider = LoadSprite("../Sprite/Combo/boule.png", 0);
	//TEXTE
	_Ingame->combo.tCombo = LoadText("../Police/POLICE.ttf");

	//New
	//FEEDBACK
	for (int i = 0; i < NB_SPRITE_MILESTONE; i++)
	{
		char temp[255];
		sprintf(temp, "%s%d%s", "../Sprite/Combo/Feedback/milestone (", i + 1, ").png"); //permet de concaténer une "variable" entre deux "string", pratique pour charger masse d'image/fichier en 3 lignes!
																						 //printf("%s\n", temp);
		_Ingame->combo.Milestone_[i] = LoadSprite(temp, 1);
	}

	//VARIABLES
	_Ingame->combo.iCombo = 1;
	_Ingame->combo.iBest_Combo = RIEN;
	_Ingame->combo.iMilestone = RIEN;
	_Ingame->combo.fCombo_timer = RIEN;
	_Ingame->combo.fTotal_Time = TIMER_COMBO;
	_Ingame->combo.fAffichage_feedback = RIEN;
	_Ingame->combo.iMaJ = FALSE;
	_Ingame->combo.feed_Maj = FALSE;
	_Ingame->combo.Position_slider.x = ANIMATION_X;
	_Ingame->combo.Position_slider.y = ANIMATION_Y;
	_Ingame->combo.Pos_Cross.x = C_HUD_X - 70;
	_Ingame->combo.Pos_Feedback.x = FEEDBACK_X;
	_Ingame->combo.Pos_Cross.y = C_HUD_Y + 45;
	_Ingame->combo.Pos_Feedback.y = FEEDBACK_Y;

	//Position animation
	_Ingame->combo.Position.x = BALL_X;
	_Ingame->combo.Position.y = BALL_Y;


	//New
	//STATS ARMES!	_Max(= taille chargeur), _Total(= Réserve munitions)
	//Batte
	_Ingame->Upgrade.batte_damage = DEGAT_BATTE_DE_BASEBALL;
	_Ingame->Upgrade.batte_AttackSpeed = BATTE_ATTACK_SPEED;
	_Ingame->Upgrade.batte_Knockback = KNOCKBACK_BATTE;
	_Ingame->Upgrade.batte_Range = RANGE_BATTE;
	//Pistol
	_Ingame->Upgrade.pistol_damage = DEGAT_PISTOLET;
	_Ingame->Upgrade.pistol_infinite_Ammo = FALSE;
	_Ingame->Upgrade.pistol_FireRate = ATTACK_SPEED_PISTOLET;
	_Ingame->Upgrade.pistol_reload = TIMER_RELOAD_PISTOL;
	//Machine-gun(= fusil)
	_Ingame->Upgrade.fusil_damage = DEGAT_FUSIL;
	_Ingame->Upgrade.fusil_piercing_bullet = FALSE;
	_Ingame->Upgrade.fusil_FireRate = ATTACK_SPEED_FUSIL;
	_Ingame->Upgrade.fusil_reload = TIMER_RELOAD_RIFLE;
	_Ingame->Upgrade.fusil_randAcc = MACHINEGUN_ACCURACY;
	//Shotgun
	_Ingame->Upgrade.shotgun_piercing_bullet = FALSE;
	_Ingame->Upgrade.shotgun_MultiShot = SHOTGUN_MULTISHOT;
	_Ingame->Upgrade.shotgun_FireRate = ATTACK_SPEED_SHOTGUN;
	_Ingame->Upgrade.shotgun_randWide = SHOTGUN_WIDESHOT;
	_Ingame->Upgrade.shotgun_reload = TIMER_RELOAD_SHOTGUN;
	_Ingame->Upgrade.shotgun_bullet_Per_Reload = BULLET;
	//Flamethrower
	_Ingame->Upgrade.flamethrower_damage = DEGAT_FLAMETHROWER;
	_Ingame->Upgrade.toggle_growing_fire = FALSE;
	_Ingame->Upgrade.flamethrower_fire_Range = FLAMETHROWER_VELOCITY;
	_Ingame->Upgrade.flamethrower_growing_fire = FLAMETHROWER_FIRE_GROW;
	_Ingame->Upgrade.flamethrower_width = FLAMETHROWER_WIDTH;
	_Ingame->Upgrade.flame_duration = FLAMETHROWER_RANGE;

	//Grenade
	//_Ingame->Ammo.iAmmo_Grenade_Total = TOTAL_GRENADE_AMMO;
	//_Ingame->Upgrade.grenade_biggerBang;
	//_Ingame->Upgrade.grenade_ClusterExplode;
	//_Ingame->Upgrade.grenade_damage = DEGAT_GRENADE;


	//initialisation des armes à débloquer
	_Ingame->Upgrade.fusil_unlock = FALSE;
	_Ingame->Upgrade.shotgun_unlock = FALSE;
	_Ingame->Upgrade.lanceFlamme_unlock = FALSE;
	_Ingame->Upgrade.grenade_unlock = FALSE;

}


void Combo_Update(INGAME* _Ingame, UTILS* _Utils)
{
	//enclenche le timer
	if (_Ingame->combo.iCombo > 1)
	{
		_Ingame->combo.fCombo_timer += 1.0f * _Utils->fDeltatime; //timer combo
																  //si le timer atteint le temps limite alors on décrémente le combo et on remet à jour le timer
		if (_Ingame->combo.fCombo_timer >= _Ingame->combo.fTotal_Time) //Enlève 1pts de combo et relance - le timer
		{
			//printf("-1 combo\n");
			_Ingame->combo.iCombo -= 1; //enlève un pts de combo.
			_Ingame->combo.fTotal_Time *= (1.0f / TIME); // ré-augmente légérement le total de temps nécessaire pour enlever un pts de combo.
			_Ingame->combo.fCombo_timer = RIEN; //Réinitialise le timer
			_Ingame->combo.Position.x = BALL_X; //remet la boule rouge à sa position initial (indicateur du temps restant).
		}
		//Permet de déplacer le curseur rouge sur slider pour montrer combien de temps il reste avant de réduire le score de combos 1 par 1.
		//Permet d'adapter le vitesse de la boule rouge sur le slider par rapport au temps restant en gros!
		_Ingame->combo.Position.x -= BALL_SPEED * _Utils->fDeltatime * (TIMER_COMBO / _Ingame->combo.fTotal_Time);
	}
	else if (_Ingame->combo.iCombo == 1) //réinitialise les valeurs si le combo reviens à 1 [SECURITER!]
	{
		_Ingame->combo.Position.x = BALL_X;
		_Ingame->combo.fTotal_Time = TIMER_COMBO; //valeur initiale du timer de combo
	}
	//met à jour les combo quand on tue un zombie (voir fonction "suppr_Zombie();"!)
	while (_Ingame->combo.iCombo > 1 && _Ingame->combo.iMaJ == TRUE) //ajoute du combo
	{
		_Ingame->combo.Position.x = BALL_X;
		_Ingame->combo.fCombo_timer = RIEN;
		_Ingame->combo.iCombo += 1;
		_Ingame->combo.fTotal_Time *= TIME; //réduit le temps total du timer de combo.
		_Ingame->combo.iMaJ = FALSE;
	}

	//permet d'enregistrer le meilleur combo de la partie pour avoir accés aux différentes récompenses!
	if (_Ingame->combo.iCombo > _Ingame->combo.iBest_Combo)
	{
		_Ingame->combo.iBest_Combo = _Ingame->combo.iCombo;
		//printf("Meilleur Combo: %d\n", _Ingame->combo.iBest_Combo);
	}

	//==================== FEEDBACK ====================
	//Init Chrono d'affichage à chaques milestone
	//WEAPON


	//===========================================================================================================

	//MEGA MAJ!!!
	//Recopie touuuuuu-tes les conditions de milestones! Armes ET Upgrade
	//Le dossier contenant les sprites des combos à été mis à jour!

	//if (_Ingame->combo.iBest_Combo == UNLOCK_KATANA && _Ingame->combo.iMilestone < 1)
	//{
	//	_Ingame->Upgrade.katana_unlock = TRUE;
	//	//_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
	//	//_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie
	//}
	if (_Ingame->combo.iBest_Combo == UNLOCK_MACHINEGUN && _Ingame->combo.iMilestone < 2)
	{
		_Ingame->Upgrade.fusil_unlock = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == UNLOCK_SHOTGUN && _Ingame->combo.iMilestone < 4)
	{
		_Ingame->Upgrade.shotgun_unlock = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == UNLOCK_GRENADE && _Ingame->combo.iMilestone < 8)
	{
		_Ingame->Upgrade.grenade_unlock = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//Mettre à jour les num des milestones
	if (_Ingame->combo.iBest_Combo == UNLOCK_CHAINSAW && _Ingame->combo.iMilestone < 14)
	{
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == UNLOCK_FLAMETHROWER && _Ingame->combo.iMilestone < 25)
	{
		_Ingame->Upgrade.lanceFlamme_unlock = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}


	//UPGRADE
	if (_Ingame->combo.iBest_Combo == 3 && _Ingame->combo.iMilestone < 1)
	{
		_Ingame->Upgrade.pistol_FireRate = ATTACK_SPEED_PISTOLET / DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 7 && _Ingame->combo.iMilestone < 3)
	{
		_Ingame->Upgrade.pistol_damage = DEGAT_PISTOLET * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 12 && _Ingame->combo.iMilestone < 5)
	{
		_Ingame->Upgrade.fusil_FireRate = ATTACK_SPEED_FUSIL / DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 16 && _Ingame->combo.iMilestone < 6)
	{
		_Ingame->Ammo.iAmmo_Rifle_Total = TOTAL_RIFLE_AMMO * DOUBLE;
		_Ingame->Ammo.iAmmo_Rifle_Max = MAX_RIFLE_AMMO * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 17 && _Ingame->combo.iMilestone < 7)
	{
		_Ingame->Upgrade.shotgun_FireRate = ATTACK_SPEED_SHOTGUN / DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 20 && _Ingame->combo.iMilestone < 9)
	{
		_Ingame->Ammo.iAmmo_Shotgun_Total = TOTAL_SHOTGUN_AMMO * DOUBLE;
		_Ingame->Ammo.iAmmo_Shotgun_Max = MAX_SHOTGUN_AMMO * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//New
	if (_Ingame->combo.iBest_Combo == 23 && _Ingame->combo.iMilestone < 10)
	{
		_Ingame->Upgrade.pistol_infinite_Ammo = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//Mettre à jour les num des milestones
	if (_Ingame->combo.iBest_Combo == 26 && _Ingame->combo.iMilestone < 11)
	{
		_Ingame->Upgrade.fusil_randAcc = MACHINEGUN_ACCURACY / DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 28 && _Ingame->combo.iMilestone < 12)
	{
		_Ingame->Upgrade.fusil_reload = TIMER_RELOAD_RIFLE / DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 30 && _Ingame->combo.iMilestone < 13)
	{
		_Ingame->Upgrade.shotgun_randWide = SHOTGUN_WIDESHOT * ONE_QUARTILE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 32 && _Ingame->combo.iMilestone < 15)
	{
		//printf("Fragmentation activée.\n");
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 35 && _Ingame->combo.iMilestone < 16)
	{
		_Ingame->Upgrade.pistol_reload = TIMER_RELOAD_PISTOL / DOUBLE;
		_Ingame->Upgrade.shotgun_bullet_Per_Reload = BULLET * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//Maj des num
	if (_Ingame->combo.iBest_Combo == 37 && _Ingame->combo.iMilestone < 17)
	{
		_Ingame->Upgrade.shotgun_reload = TIMER_RELOAD_SHOTGUN / DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 38 && _Ingame->combo.iMilestone < 18)
	{
		_Ingame->Ammo.iAmmo_Rifle_Total = TOTAL_RIFLE_AMMO * QUAD;
		_Ingame->Ammo.iAmmo_Rifle_Max = MAX_RIFLE_AMMO * QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 40 && _Ingame->combo.iMilestone < 19)
	{
		_Ingame->Ammo.iAmmo_Shotgun_Total = TOTAL_SHOTGUN_AMMO * QUAD;
		_Ingame->Ammo.iAmmo_Shotgun_Max = MAX_SHOTGUN_AMMO * QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 41 && _Ingame->combo.iMilestone < 20)
	{
		//printf("Grenade double munitions Activée.\n");
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 42 && _Ingame->combo.iMilestone < 21)
	{
		_Ingame->Upgrade.shotgun_FireRate = ATTACK_SPEED_SHOTGUN / QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 44 && _Ingame->combo.iMilestone < 22)
	{
		//printf("Grenade upgrade explosion 1 Activee.\n");
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 47 && _Ingame->combo.iMilestone < 23)
	{
		_Ingame->Upgrade.fusil_damage = DEGAT_FUSIL * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 49/*50*/ && _Ingame->combo.iMilestone < 24)
	{
		_Ingame->Upgrade.shotgun_randWide = SHOTGUN_WIDESHOT * ONE_DEMI;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 51 && _Ingame->combo.iMilestone < 26)
	{
		//printf("Grenade Quadruple Munitions Activee.\n");
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//New
	if (_Ingame->combo.iBest_Combo == 53 && _Ingame->combo.iMilestone < 27)
	{
		_Ingame->Upgrade.flamethrower_width = FLAMETHROWER_WIDTH + 0.25f + _Ingame->Upgrade.flamethrower_growing_fire;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//MaJ des num des iMilestone
	if (_Ingame->combo.iBest_Combo == 55 && _Ingame->combo.iMilestone < 28)
	{
		_Ingame->Upgrade.shotgun_MultiShot = SHOTGUN_MULTISHOT * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 57 && _Ingame->combo.iMilestone < 29)
	{
		//printf("Grenade Taille d'explosion niveau 2 Activee.\n");
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 59 && _Ingame->combo.iMilestone < 30)
	{
		_Ingame->Upgrade.pistol_reload = TIMER_RELOAD_PISTOL / QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 62 && _Ingame->combo.iMilestone < 31)
	{
		_Ingame->Upgrade.fusil_FireRate = ATTACK_SPEED_FUSIL / QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 63/*89*/ && _Ingame->combo.iMilestone < 32)
	{
		_Ingame->Upgrade.fusil_damage = DEGAT_FUSIL * QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//New
	if (_Ingame->combo.iBest_Combo == 64 && _Ingame->combo.iMilestone < 33)
	{
		_Ingame->Upgrade.flamethrower_damage = DEGAT_FLAMETHROWER * DOUBLE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//MaJ des num des iMilestone
	if (_Ingame->combo.iBest_Combo == 65 && _Ingame->combo.iMilestone < 34)
	{
		_Ingame->Upgrade.fusil_reload = TIMER_RELOAD_RIFLE / QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	if (_Ingame->combo.iBest_Combo == 70 && _Ingame->combo.iMilestone < 35)
	{
		_Ingame->Upgrade.shotgun_MultiShot = SHOTGUN_MULTISHOT * QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//New
	if (_Ingame->combo.iBest_Combo == 72 && _Ingame->combo.iMilestone < 36)
	{
		_Ingame->Upgrade.flamethrower_fire_Range = (FLAMETHROWER_RANGE + 500.0f);
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}

	if (_Ingame->combo.iBest_Combo == 74 && _Ingame->combo.iMilestone < 37)
	{
		_Ingame->Upgrade.shotgun_reload = TIMER_RELOAD_SHOTGUN / QUAD;
		_Ingame->Upgrade.shotgun_bullet_Per_Reload = BULLET * QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1; //permet d'éviter d'afficher le sprite + d'une fois par partie

	}
	//New
	if (_Ingame->combo.iBest_Combo == 78 && _Ingame->combo.iMilestone < 38)
	{
		_Ingame->Upgrade.toggle_growing_fire = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//New
	if (_Ingame->combo.iBest_Combo == 85 && _Ingame->combo.iMilestone < 39)
	{
		_Ingame->Upgrade.flamethrower_damage = DEGAT_FLAMETHROWER * QUAD;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//New
	if (_Ingame->combo.iBest_Combo == 95 && _Ingame->combo.iMilestone < 40)
	{
		_Ingame->Upgrade.flamethrower_fire_Range = (FLAMETHROWER_RANGE + 1000.0f);
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//New
	if (_Ingame->combo.iBest_Combo == 110 && _Ingame->combo.iMilestone < 41)
	{
		_Ingame->Upgrade.fusil_piercing_bullet = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}
	//New
	if (_Ingame->combo.iBest_Combo == 120 && _Ingame->combo.iMilestone < 42)
	{
		_Ingame->Upgrade.shotgun_piercing_bullet = TRUE;
		_Ingame->combo.fAffichage_feedback += TIMER_FEEDBACK;
		_Ingame->combo.iMilestone += 1;
	}



	//printf("range %f\t", _Ingame->Upgrade.flamethrower_range);
	//printf("mouse: x %d y %d\n", _Utils->Mouse.x, _Utils->Mouse.y);

	//printf("iMilestone = %d\n", _Ingame->combo.iMilestone);

	//Compte à rebours affichage feedback
	if (_Ingame->combo.fAffichage_feedback >= 0.0f)
	{
		_Ingame->combo.fAffichage_feedback -= 1.0f * _Utils->fDeltatime;
		_Ingame->combo.feed_Maj = TRUE;
	}
	else
	{
		_Ingame->combo.feed_Maj = FALSE;
	}
	//printf("zombie %d\n", _Utils->iCompteur_Zombie);
}


void Combo_HUD(INGAME* _Ingame, UTILS* _Utils)
{
	//Affichage texte_______________________________________________________________________________________________________
	char temp[100];
	sprintf(temp, "%0.2d", _Ingame->combo.iCombo);
	sfText_setScale(_Ingame->combo.tCombo, (sfVector2f) { 2.0, 2.0 });
	sfText_setString(_Ingame->combo.tCombo, temp);
	sfText_setPosition(_Ingame->combo.tCombo, (sfVector2f) { _Utils->CentreCamera.x + 830, _Utils->CentreCamera.y - 450 });
	sfText_setColor(_Ingame->combo.tCombo, (sfColor) { 255, 255, 255, 255 });

	sfRenderWindow_drawText(_Utils->window, _Ingame->combo.tCombo, NULL);
	int Color_temp;
	//Affichage feedback
	if (_Ingame->combo.fAffichage_feedback <= 1.75f)
	{
		Color_temp = 255 * (_Ingame->combo.fAffichage_feedback / TIMER_FEEDBACK); //pour changer la transparence du sprite
	}
	//quand le chrono est activé...
	if (_Ingame->combo.fAffichage_feedback > 0.0f && _Ingame->combo.iMilestone > 0 && _Ingame->combo.feed_Maj == TRUE)
	{
		//printf("milestone %d\n", _Ingame->combo.iMilestone);
		sfSprite_setColor(_Ingame->combo.Milestone_[_Ingame->combo.iMilestone - 1], (sfColor) { 255, 255, 255, (int)Color_temp });
		Afficher_Sprite(_Ingame->combo.Milestone_[_Ingame->combo.iMilestone - 1], _Utils->CentreCamera.x, _Utils->CentreCamera.y + 500.0f, FEEDBACK_SCALEX, FEEDBACK_SCALEY, 0, _Utils->window);
	}



	//Affichage de l'HUD des combos______________________________________________________________________________________________________
	Afficher_Sprite(_Ingame->Sprite.Multiply, _Utils->CentreCamera.x + 790, _Utils->CentreCamera.y - 425, 0.20, 0.25, 0, _Utils->window);
	Afficher_Sprite(_Ingame->Sprite.Slider, _Utils->CentreCamera.x + 570, _Utils->CentreCamera.y - 420, 1.0, 1.0, 0, _Utils->window); //Slider
																																	  //affichage de la boule rouge du slider
	Afficher_Sprite(_Ingame->Sprite.Ball_Slider, _Utils->CentreCamera.x + _Ingame->combo.Position.x, _Utils->CentreCamera.y - 422, 1.0, 1.0, 0, _Utils->window); //Ball Slider
}
//==============================================
//==============================================