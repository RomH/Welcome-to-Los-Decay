#include "stdafx.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////DEFINE MENU/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// *Permet de dire qu'il s'agit d'un sous états (pour les choix).


//==============================================
//==============================================
// MENU MIS A JOUR (30/03/17 )/!\

//SCALE
#define NORMAL_SCALE 1
#define BOUTONS_SCALE 0.8
//position origin des boutons
#define PLAY_X 660 //gauche -370 et droite +370
#define OPTION_X 660
#define CREDITS_X 660
#define EXIT_X 660


#define PLAY_Y 580 //haut -70 et bas +70
#define OPTION_Y 700
#define CREDITS_Y 820
#define EXIT_Y 940

//bouton origin
#define HUD_HP_X 415
#define HUD_HP_Y 645
//hitbox boutons
#define HITBOX_PLAYX 126.8
#define HITBOX_OPTIONX 210.4
#define HITBOX_CREDITX 208
#define HITBOX_EXITX 116.4
#define HITBOX_RETURNX 175

#define HITBOX_PLAYY 55.2
#define HITBOX_OPTIONY 57.6
#define HITBOX_CREDITY 57.2
#define HITBOX_EXITY 55.2
#define HITBOX_RETURNY 46.5
//Position bouton retour
#define RETURN_X ((LONGUEUR-175) > (HITBOX_RETURNX+45) ? ((LONGUEUR-175)) : (HITBOX_RETURNX+45))
#define RETURN_Y ((HAUTEUR - 145) > (HITBOX_RETURNY+145) ? ((HAUTEUR - 145)) : (HITBOX_RETURNY+145))

//hitbox boutons des options (choix)
#define HITBOX_MENUOPTIONX 125
#define HITBOX_MENUOPTIONY 43

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Menu_LoadSpritePack(INGAME* _Ingame)
{
	//menu
	_Ingame->Sprite.Menu = LoadSprite("../Sprite/menu/menu.png", 1); //Menu

	 //boutons
	 //_Ingame->Sprite.ptrouge = LoadSprite("Sprite/circle.png", 1); //test-états
	_Ingame->Sprite.credits = LoadSprite("../Sprite/menu/Option/credits.png", 1); //crédits
	_Ingame->Sprite.play = LoadSprite("../Sprite/menu/play.png", 1);

	//Boutons du menu principal
	_Ingame->Sprite.Menu_boutons[0] = LoadSprite("../Sprite/menu/play.png", 1);
	_Ingame->Sprite.Menu_boutons[1] = LoadSprite("../Sprite/menu/options.png", 1);
	_Ingame->Sprite.Menu_boutons[2] = LoadSprite("../Sprite/menu/credit.png", 1);
	_Ingame->Sprite.Menu_boutons[3] = LoadSprite("../Sprite/menu/exit.png", 1);
	_Ingame->Sprite.Return = LoadSprite("../Sprite/menu/Option/return.png", 1);
	//Surbrillances des boutons du menu principale
	_Ingame->Sprite.Menu_Surbrillance[0] = LoadSprite("../Sprite/menu/play_active.png", 1);
	_Ingame->Sprite.Menu_Surbrillance[1] = LoadSprite("../Sprite/menu/options_active.png", 1);
	_Ingame->Sprite.Menu_Surbrillance[2] = LoadSprite("../Sprite/menu/credits_active.png", 1);
	_Ingame->Sprite.Menu_Surbrillance[3] = LoadSprite("../Sprite/menu/exit_active.png", 1);
	_Ingame->Sprite.Return_Surbrillance = LoadSprite("../Sprite/menu/Option/return_activ.png", 1);
	//Options
	_Ingame->Sprite.MenuOption = LoadSprite("../Sprite/menu/Option/ecran_hud.png", 0);
	_Ingame->Sprite.OnHead = LoadSprite("../Sprite/menu/Option/OnHead.png", 1);
	_Ingame->Sprite.OnScreen = LoadSprite("../Sprite/menu/Option/OnScreen.png", 1);
	_Ingame->Sprite.Both = LoadSprite("../Sprite/menu/Option/Both.png", 1);

	_Ingame->Sprite.OnHeadHighlight = LoadSprite("../Sprite/menu/Option/on_head_activ.png", 1);
	_Ingame->Sprite.OnScreenHighlight = LoadSprite("../Sprite/menu/Option/on_screen_activ.png", 1);
	_Ingame->Sprite.BothHighlight = LoadSprite("../Sprite/menu/Option/both_activ.png", 1);

	//Menu pause
	_Ingame->Sprite.MenuPause = LoadSprite("../Sprite/menu/Pause/pause.png", 1);
	_Ingame->Sprite.cache_upgrade = LoadSprite("../Sprite/menu/Pause/cache.png", 0);
}

void Menu_initialisation(INGAME* _Ingame, UTILS* _Utils)
{
	//initialisation
	//ETAT
	_Utils->iEtat = STATEMENU;

	//MENU
	_Ingame->Menu.pos_menu.x = LONGUEUR / 2;
	_Ingame->Menu.pos_menu.y = HAUTEUR / 2;
	//Boutons menu
	_Ingame->Menu.pos_play.x = PLAY_X;
	_Ingame->Menu.pos_play.y = PLAY_Y;
	_Ingame->Menu.pos_options.x = OPTION_X;
	_Ingame->Menu.pos_options.y = OPTION_Y;
	_Ingame->Menu.pos_credits.x = CREDITS_X;
	_Ingame->Menu.pos_credits.y = CREDITS_Y;
	_Ingame->Menu.pos_exit.x = EXIT_X;
	_Ingame->Menu.pos_exit.y = EXIT_Y;

	_Ingame->Menu.return_pos.x = RETURN_X;
	_Ingame->Menu.return_pos.y = RETURN_Y;
	//OPTIONS
	_Ingame->Menu.fpos_hpHUD_X = LONGUEUR / 2;
	_Ingame->Menu.fpos_hpHUD_Y = HAUTEUR / 2;
	_Utils->iHud_HP = STATEHUD_HP3;
	//Boutons Options
	_Ingame->Menu.fpos_opts_X = HUD_HP_X;
	_Ingame->Menu.fpos_opts_Y = HUD_HP_Y;

	//Menu Pause
	_Ingame->Menu.pos_menu_pause.x = LONGUEUR / 2;
	_Ingame->Menu.pos_menu_pause.y = HAUTEUR / 2;

	_Ingame->Menu.nb_cache = NB_SPRITE_MILESTONE;

	for (int i = 21; i > -1; i--)
	{
		_Ingame->Menu.pos_cache_upgrade[i].x = 23;
		_Ingame->Menu.pos_cache_upgrade[i].y = 94 + (44 * i);
		//printf("colonne 1, cache num: %2d\t pos x %f y %f\n",i,_Ingame->Menu.pos_cache_upgrade[i].x,	_Ingame->Menu.pos_cache_upgrade[i].y);
	}

	for (int i = (NB_SPRITE_MILESTONE - 22) - 1; i > -1; i--)
	{
		_Ingame->Menu.pos_cache_upgrade[i + 22].x = 452;
		_Ingame->Menu.pos_cache_upgrade[i + 22].y = 94 + (44 * i);
		//printf("colonne 2, cache num: %2d\t pos x %f y %f\n",i,	_Ingame->Menu.pos_cache_upgrade[i + 22].x,	_Ingame->Menu.pos_cache_upgrade[i + 22].y);
	}
}

void Menu_Contrôle(INGAME* _Ingame, UTILS* _Utils)//Menu_Contrôle
{
	//Clic gauche souris
	if (_Utils->event.type == sfEvtMouseButtonPressed && _Utils->event.mouseButton.button == sfMouseLeft)
	{
		//printf("Clic gauche\n");
		////hitbox du bouton play
		if (_Utils->Mouse.x < _Ingame->Menu.pos_play.x + HITBOX_PLAYX &&
			_Utils->Mouse.x > _Ingame->Menu.pos_play.x - HITBOX_PLAYX &&
			_Utils->Mouse.y < _Ingame->Menu.pos_play.y + HITBOX_PLAYY &&
			_Utils->Mouse.y > _Ingame->Menu.pos_play.y - HITBOX_PLAYY &&
			_Utils->iEtat == STATEMENU)
		{
			sfSound_stop(_Ingame->musique.musique_menu);
			_Utils->iEtat = STATEPLAY; //bouton: play
									   //printf("Play!\n");
		}

		////hitbox du bouton options
		if (_Utils->Mouse.x < _Ingame->Menu.pos_options.x + HITBOX_OPTIONX &&
			_Utils->Mouse.x > _Ingame->Menu.pos_options.x - HITBOX_OPTIONX &&
			_Utils->Mouse.y < _Ingame->Menu.pos_options.y + HITBOX_OPTIONY &&
			_Utils->Mouse.y > _Ingame->Menu.pos_options.y - HITBOX_OPTIONY &&
			_Utils->iEtat == STATEMENU)
		{
			_Utils->iEtat = STATEOPTION; //bouton: options
										 //printf("Options!\n");
		}

		////hitbox du bouton credits
		if (_Utils->Mouse.x < _Ingame->Menu.pos_credits.x + HITBOX_CREDITX &&
			_Utils->Mouse.x > _Ingame->Menu.pos_credits.x - HITBOX_CREDITX &&
			_Utils->Mouse.y < _Ingame->Menu.pos_credits.y + HITBOX_CREDITY &&
			_Utils->Mouse.y > _Ingame->Menu.pos_credits.y - HITBOX_CREDITY &&
			_Utils->iEtat == STATEMENU)
		{
			_Utils->iEtat = STATECREDITS; //bouton: options
										  //printf("Credits!\n");
		}

		//hitbox du bouton exit
		if (_Utils->Mouse.x < _Ingame->Menu.pos_exit.x + HITBOX_EXITX &&
			_Utils->Mouse.x > _Ingame->Menu.pos_exit.x - HITBOX_EXITX &&
			_Utils->Mouse.y < _Ingame->Menu.pos_exit.y + HITBOX_EXITY &&
			_Utils->Mouse.y > _Ingame->Menu.pos_exit.y - HITBOX_EXITY &&
			_Utils->iEtat == STATEMENU)
		{
			sfRenderWindow_close(_Utils->window);
			system("taskkill /im cmd.exe");
		}

		//AUTRES
		////hitbox du bouton RETOUR
		if (_Utils->Mouse.x < _Ingame->Menu.return_pos.x + HITBOX_RETURNX &&
			_Utils->Mouse.x > _Ingame->Menu.return_pos.x - HITBOX_RETURNX &&
			_Utils->Mouse.y < _Ingame->Menu.return_pos.y + HITBOX_RETURNY &&
			_Utils->Mouse.y > _Ingame->Menu.return_pos.y - HITBOX_RETURNY &&
			(_Utils->iEtat == STATEOPTION || _Utils->iEtat == STATECREDITS))
		{
			_Utils->iEtat = STATEMENU; //bouton: options
									   //printf("Retour menu!\n");
		}
		////OPTIONS
		//hitbox boutons :

		if (_Utils->Mouse.x < _Ingame->Menu.fpos_opts_X + HITBOX_MENUOPTIONX &&
			_Utils->Mouse.x > _Ingame->Menu.fpos_opts_X - HITBOX_MENUOPTIONX &&
			_Utils->Mouse.y < _Ingame->Menu.fpos_opts_Y + HITBOX_MENUOPTIONY &&
			_Utils->Mouse.y > _Ingame->Menu.fpos_opts_Y - HITBOX_MENUOPTIONY &&
			_Utils->iEtat == STATEOPTION)
		{
			//printf("choix option\n"); //test hitbox
			//si "ON HEAD" est cocher
			if (_Utils->iHud_HP == STATEHUD_HP1)
			{
				_Utils->iHud_HP = STATEHUD_HP2; //alors on passe en "ON SCREEN"
			}
			//sinon si "ON SCREEN" est cocher
			else if (_Utils->iHud_HP == STATEHUD_HP2)
			{
				_Utils->iHud_HP = STATEHUD_HP3; //alors on passe en "BOTH"
			}
			//sinon si "BOTH" est cocher
			else if (_Utils->iHud_HP == STATEHUD_HP3)
			{
				_Utils->iHud_HP = STATEHUD_HP1; //alors on passe en "ON HEAD"
			}
		}
	}

	if (_Utils->event.type == sfEvtKeyPressed && _Utils->event.key.code == sfKeyEscape)
	{
		if (_Utils->iEtat == STATEPLAY || _Utils->iEtat == STATEOPTION || _Utils->iEtat == STATECREDITS)
		{
			_Utils->iEtat = STATEMENU; //retour au menu
		}
	}
}

void Menu_Display(INGAME* _Ingame, UTILS* _Utils)
{
	//menu blitsprite
	//MENU
	if (_Utils->iEtat == STATEMENU) Afficher_Sprite(_Ingame->Sprite.Menu, _Ingame->Menu.pos_menu.x, _Ingame->Menu.pos_menu.y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//background																																							//Surbrillance des boutons
																																													//PLAY
	if (_Utils->Mouse.x < _Ingame->Menu.pos_play.x + HITBOX_PLAYX &&
		_Utils->Mouse.x > _Ingame->Menu.pos_play.x - HITBOX_PLAYX &&
		_Utils->Mouse.y < _Ingame->Menu.pos_play.y + HITBOX_PLAYY &&
		_Utils->Mouse.y > _Ingame->Menu.pos_play.y - HITBOX_PLAYY &&
		_Utils->iEtat == STATEMENU)
	{
		//printf("play active\n");
		Afficher_Sprite(_Ingame->Sprite.Menu_Surbrillance[0], _Ingame->Menu.pos_play.x, _Ingame->Menu.pos_play.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	}
	//OPTIONS
	if (_Utils->Mouse.x < _Ingame->Menu.pos_options.x + HITBOX_OPTIONX &&
		_Utils->Mouse.x > _Ingame->Menu.pos_options.x - HITBOX_OPTIONX &&
		_Utils->Mouse.y < _Ingame->Menu.pos_options.y + HITBOX_OPTIONY &&
		_Utils->Mouse.y > _Ingame->Menu.pos_options.y - HITBOX_OPTIONY&&
		_Utils->iEtat == STATEMENU)
	{
		//printf("options active\n");
		Afficher_Sprite(_Ingame->Sprite.Menu_Surbrillance[1], _Ingame->Menu.pos_options.x, _Ingame->Menu.pos_options.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	}
	//CREDITS
	if (_Utils->Mouse.x < _Ingame->Menu.pos_credits.x + HITBOX_CREDITX &&
		_Utils->Mouse.x > _Ingame->Menu.pos_credits.x - HITBOX_CREDITX &&
		_Utils->Mouse.y < _Ingame->Menu.pos_credits.y + HITBOX_CREDITY &&
		_Utils->Mouse.y > _Ingame->Menu.pos_credits.y - HITBOX_CREDITY &&
		_Utils->iEtat == STATEMENU)
	{
		//printf("credits active\n");
		Afficher_Sprite(_Ingame->Sprite.Menu_Surbrillance[2], _Ingame->Menu.pos_credits.x, _Ingame->Menu.pos_credits.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	}
	//EXIT
	if (_Utils->Mouse.x < _Ingame->Menu.pos_exit.x + HITBOX_EXITX &&
		_Utils->Mouse.x > _Ingame->Menu.pos_exit.x - HITBOX_EXITX &&
		_Utils->Mouse.y < _Ingame->Menu.pos_exit.y + HITBOX_EXITY &&
		_Utils->Mouse.y > _Ingame->Menu.pos_exit.y - HITBOX_EXITY &&
		_Utils->iEtat == STATEMENU)
	{
		//printf("exit active\n");
		Afficher_Sprite(_Ingame->Sprite.Menu_Surbrillance[3], _Ingame->Menu.pos_exit.x, _Ingame->Menu.pos_exit.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	}

	//MENU BOUTONS
	if (_Utils->iEtat == STATEMENU) Afficher_Sprite(_Ingame->Sprite.Menu_boutons[0], _Ingame->Menu.pos_play.x, _Ingame->Menu.pos_play.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	if (_Utils->iEtat == STATEMENU) Afficher_Sprite(_Ingame->Sprite.Menu_boutons[1], _Ingame->Menu.pos_options.x, _Ingame->Menu.pos_options.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	if (_Utils->iEtat == STATEMENU) Afficher_Sprite(_Ingame->Sprite.Menu_boutons[2], _Ingame->Menu.pos_credits.x, _Ingame->Menu.pos_credits.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);
	if (_Utils->iEtat == STATEMENU) Afficher_Sprite(_Ingame->Sprite.Menu_boutons[3], _Ingame->Menu.pos_exit.x, _Ingame->Menu.pos_exit.y, BOUTONS_SCALE, BOUTONS_SCALE, 0, _Utils->window);

	if (_Utils->iEtat == STATEOPTION) Afficher_Sprite(_Ingame->Sprite.MenuOption, 0.0f, 0.0f, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//options
	if (_Utils->iEtat == STATECREDITS) Afficher_Sprite(_Ingame->Sprite.credits, _Ingame->Menu.pos_menu.x, _Ingame->Menu.pos_menu.y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);	//crédits

	if (_Utils->iEtat == STATEOPTION)//Options
	{
		//Surbrillance des boutons
		if (_Utils->Mouse.x < _Ingame->Menu.fpos_opts_X + HITBOX_MENUOPTIONX &&
			_Utils->Mouse.x > _Ingame->Menu.fpos_opts_X - HITBOX_MENUOPTIONX &&
			_Utils->Mouse.y < _Ingame->Menu.fpos_opts_Y + HITBOX_MENUOPTIONY &&
			_Utils->Mouse.y > _Ingame->Menu.fpos_opts_Y - HITBOX_MENUOPTIONY)
		{
			if (_Utils->iHud_HP == STATEHUD_HP1) Afficher_Sprite(_Ingame->Sprite.OnHeadHighlight, _Ingame->Menu.fpos_opts_X, _Ingame->Menu.fpos_opts_Y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//ON HEAD
			if (_Utils->iHud_HP == STATEHUD_HP2) Afficher_Sprite(_Ingame->Sprite.OnScreenHighlight, _Ingame->Menu.fpos_opts_X, _Ingame->Menu.fpos_opts_Y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//ON SCREEN
			if (_Utils->iHud_HP == STATEHUD_HP3) Afficher_Sprite(_Ingame->Sprite.BothHighlight, _Ingame->Menu.fpos_opts_X, _Ingame->Menu.fpos_opts_Y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//BOTH		}
		}


		if (_Utils->iHud_HP == STATEHUD_HP1) Afficher_Sprite(_Ingame->Sprite.OnHead, _Ingame->Menu.fpos_opts_X, _Ingame->Menu.fpos_opts_Y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//ON HEAD
		if (_Utils->iHud_HP == STATEHUD_HP2) Afficher_Sprite(_Ingame->Sprite.OnScreen, _Ingame->Menu.fpos_opts_X, _Ingame->Menu.fpos_opts_Y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//ON SCREEN
		if (_Utils->iHud_HP == STATEHUD_HP3) Afficher_Sprite(_Ingame->Sprite.Both, _Ingame->Menu.fpos_opts_X, _Ingame->Menu.fpos_opts_Y, NORMAL_SCALE, NORMAL_SCALE, 0, _Utils->window);		//BOTH
	}

	//RETURN
	////hitbox du bouton RETOUR
	if (_Utils->Mouse.x < _Ingame->Menu.return_pos.x + HITBOX_RETURNX &&
		_Utils->Mouse.x > _Ingame->Menu.return_pos.x - HITBOX_RETURNX &&
		_Utils->Mouse.y < _Ingame->Menu.return_pos.y + HITBOX_RETURNY &&
		_Utils->Mouse.y > _Ingame->Menu.return_pos.y - HITBOX_RETURNY &&
		(_Utils->iEtat == STATEOPTION || _Utils->iEtat == STATECREDITS))
	{
		Afficher_Sprite(_Ingame->Sprite.Return_Surbrillance, _Ingame->Menu.return_pos.x, _Ingame->Menu.return_pos.y, 1, 1, 0, _Utils->window);
	}
	if (_Utils->iEtat == STATEOPTION || _Utils->iEtat == STATECREDITS) Afficher_Sprite(_Ingame->Sprite.Return, _Ingame->Menu.return_pos.x, _Ingame->Menu.return_pos.y, 1.0, 1.0, 0, _Utils->window);


	//PAUSE
	if (_Utils->iEtat == STATEPAUSE)
	{
		Afficher_Sprite(_Ingame->Sprite.MenuPause, _Ingame->Menu.pos_menu_pause.x, _Ingame->Menu.pos_menu_pause.y, 1.0, 1.0, 0.0, _Utils->window);

		//Affichage des caches et upgrade du menu pause	
		for (int i = 0; i < NB_SPRITE_MILESTONE; i++)
		{
			//Cache Wip, n'efface pas
			//Afficher_Sprite(_Ingame->Sprite.cache_upgrade, _Ingame->Menu.pos_cache_upgrade[i].x, _Ingame->Menu.pos_cache_upgrade[i].y, 1.0, 1.0, 0.0, _Utils->window);
			sfColor color1 = { 255,255,255,255 };
			sfSprite_setColor(_Ingame->combo.Milestone_[i], color1);

			//permet d'enlever l'effet "transparent" de l'upgrade débloqué! et vice-versa
			if (i >= _Ingame->combo.iMilestone)
			{
				sfColor color2 = { 255,155,255,100 };
				sfSprite_setColor(_Ingame->combo.Milestone_[i], color2);
			}
			//Les valeurs brutes pour les position X/Y sont pour centrer les sprites dans le menu pause
			Afficher_Sprite(_Ingame->combo.Milestone_[i], _Ingame->Menu.pos_cache_upgrade[i].x + (200), _Ingame->Menu.pos_cache_upgrade[i].y + (22), 0.75, 0.5, 0.0, _Utils->window);
		}
		//Camera.cpp à été mis à jour pour éviter d'avoir les même prob que le menu du jeu
	}
}
//==============================================
//==============================================