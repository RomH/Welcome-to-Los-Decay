#include "Load_Display.h"

//_______________________________________________________________________________________________________________________________________________________

sfText* LoadText(char* _sNom)
{
	sfFont* font;
	sfText* texte;

	font = sfFont_createFromFile(_sNom);
	texte = sfText_create();
	sfText_setFont(texte, font);

	return texte;
}

//_______________________________________________________________________________________________________________________________________________________

sfSprite* LoadSprite(char* _sNom, int _isCentered)
{
	sfSprite* sprite;
	sfTexture* texture;

	texture = sfTexture_createFromFile(_sNom, NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);

	if (_isCentered != 0)
	{
		sfVector2u tempsize = sfTexture_getSize(texture);
		sfVector2f origin = { (float)tempsize.x / 2 , (float)tempsize.y / 2 };
		sfSprite_setOrigin(sprite, origin);
	}
	return sprite;
}

//_______________________________________________________________________________________________________________________________________________________

//======================== NEW!!! ===============================
void DrawPixel(sfImage* whichImage, sfVector2f whichPosition, sfColor whichColor)
{
	sfVector2u boundaries = sfImage_getSize(whichImage);
	if (whichPosition.x >= 0 &&
		whichPosition.y >= 0 &&
		whichPosition.x < boundaries.x &&
		whichPosition.y < boundaries.y)
	{
		sfImage_setPixel(whichImage, whichPosition.x, whichPosition.y, whichColor);
	}
}

void DrawLine(sfImage* whichImage, sfVector2f pointA, sfVector2f pointB, sfColor whichColor)
{
	if (pointA.x > pointB.x)
	{
		DrawLine(whichImage, pointB, pointA, whichColor);
	}
	else
	{
		DrawPixel(whichImage, pointA, whichColor);
		DrawPixel(whichImage, pointB, whichColor);
		if ((pointB.x - pointA.x) > abs(pointA.y - pointB.y))
		{
			float pixelY = (pointB.y < pointA.y ? -1 : 1) * abs(pointB.y - pointA.y) / (pointB.x - pointA.x);
			for (int i = 0; i < (pointB.x - pointA.x); i++)
			{
				DrawPixel(whichImage, (sfVector2f) { pointA.x + i, pointA.y + i * pixelY }, whichColor);
			}
		}
		else
		{
			float pixelX = (pointB.x - pointA.x) / abs(pointB.y - pointA.y);
			for (int i = 0; i < abs(pointB.y - pointA.y); i++)
			{
				DrawPixel(whichImage, (sfVector2f) { pointA.x + i * pixelX, pointA.y + (pointB.y < pointA.y ? -i : i) }, whichColor);
			}
		}
	}
}
//_______________________________________________________________________________________________________________________________________________________

void LoadSpritePack(INGAME* _Ingame, UTILS* _Utils)
{
	Menu_LoadSpritePack(_Ingame);
	Bonus_LoadSprite(_Ingame);

	_Ingame->Sprite.HUD = LoadSprite("../Sprite/HUD/HUD.png", 1);

	_Ingame->Sprite.Map = LoadSprite("../Sprite/Map.png", 0);
	_Ingame->Sprite.Map_Color = LoadSprite("../Sprite/ObstructionMap.png", 0);
	_Ingame->Sprite.Image_Map_Color = sfImage_createFromFile("../Sprite/ObstructionMap.png");

	
	//BARRE DE VIE
	_Ingame->Sprite.barre_rouge = LoadSprite("../Sprite/barre_rouge.jpg", 0);
	_Ingame->Sprite.barre_rouge2 = LoadSprite("../Sprite/barre_rouge2.jpg", 0);

	_Ingame->Sprite.HP_Vide = LoadSprite("../Animation/HUD/Hp_Bar/Sain/barre_vide.png", 0);
	_Ingame->Sprite.HP_Piston = LoadSprite("../Animation/HUD/Hp_Bar/Sain/piston.png", 1);
	_Ingame->Sprite.HP_Seringue = LoadSprite("../Animation/HUD/Hp_Bar/Sain/seringue.png", 1);

	_Ingame->Sprite.HP_VidePoison = LoadSprite("../Animation/HUD/Hp_Bar/Poison/barre_vide.png", 0);
	_Ingame->Sprite.HP_PistonPoison = LoadSprite("../Animation/HUD/Hp_Bar/Poison/piston.png", 1);
	_Ingame->Sprite.HP_SeringuePoison = LoadSprite("../Animation/HUD/Hp_Bar/Poison/seringue.png", 1);

	//Bras + Armes
	_Ingame->Sprite.Batte_Gauche = LoadSprite("../Animation/Personnage/Gauche/bras/Batte.png", 1);
	_Ingame->Sprite.Batte_Droite = LoadSprite("../Animation/Personnage/Droite/bras/Batte.png", 1);

	_Ingame->Sprite.Pistolet_Gauche = LoadSprite("../Animation/Personnage/Gauche/bras/pistolet.png", 1);
	_Ingame->Sprite.Pistolet_Droite = LoadSprite("../Animation/Personnage/Droite/bras/pistolet.png", 1);

	_Ingame->Sprite.Fusil_Gauche = LoadSprite("../Animation/Personnage/Gauche/bras/fusil.png", 1);
	_Ingame->Sprite.Fusil_Droite = LoadSprite("../Animation/Personnage/Droite/bras/fusil.png", 1);

	_Ingame->Sprite.Pompe_Gauche = LoadSprite("../Animation/Personnage/Gauche/bras/shotgun.png", 1);
	_Ingame->Sprite.Pompe_Droite = LoadSprite("../Animation/Personnage/Droite/bras/shotgun.png", 1);

	_Ingame->Sprite.LanceFlamme_Gauche = LoadSprite("../Animation/Personnage/Gauche/bras/lanceflamme.png", 1);
	_Ingame->Sprite.LanceFlamme_Droite = LoadSprite("../Animation/Personnage/Droite/bras/lanceflamme.png", 1);

	//Armes
	_Ingame->Sprite.Batte = LoadSprite("../Sprite/Batte.png", 0);
	_Ingame->Sprite.Pistolet = LoadSprite("../Sprite/Pistolet.png", 0);
	_Ingame->Sprite.Fusil = LoadSprite("../Sprite/Fusil.png", 0);
	_Ingame->Sprite.Fusil_a_pompe = LoadSprite("../Sprite/Fusil_a_pompe.png", 0);
	_Ingame->Sprite.Grenade = LoadSprite("../Sprite/Grenade.png", 0);
	_Ingame->Sprite.LanceFlamme = LoadSprite("../Sprite/w_lance_flamme.png", 1);

	_Ingame->Sprite.Bullet = LoadSprite("../Sprite/Bullet/Balle.png", 1);


	//TEXTES
	_Ingame->NB_munition.Batte_de_baseball = LoadText("../Police/POLICE.ttf");
	_Ingame->NB_munition.Pistolet = LoadText("../Police/POLICE.ttf");
	_Ingame->NB_munition.Fusil = LoadText("../Police/POLICE.ttf");
	_Ingame->NB_munition.Fusil_a_pompe = LoadText("../Police/POLICE.ttf");
	_Ingame->NB_munition.Grenade = LoadText("../Police/POLICE.ttf");
	_Ingame->NB_munition.LanceFlamme = LoadText("../Police/POLICE.ttf");

	_Ingame->texte.Nbr_vague = LoadText("../Police/POLICE.ttf");
	_Ingame->texte.Timer_Wave = LoadText("../Police/POLICE.ttf");
	_Ingame->NB_munition.antidote = LoadText("../Police/POLICE.ttf");


	//Pause
	_Ingame->Sprite.ecran_Mort = LoadSprite("../Sprite/game over.png", 1);

	//FEEDBACK
	_Ingame->Sprite.interact_door = LoadSprite("../Sprite/FeedBack/Open.png", 1);
	_Ingame->Sprite.interact_sodaMachine = LoadSprite("../Sprite/FeedBack/Soda-machine.png", 1);
	_Ingame->Sprite.Infection = LoadSprite("../Sprite/FeedBack/Poison.png", 1);		//new

	//Barre D'endurance
	_Ingame->Sprite.barre_endurance = LoadSprite("../Sprite/barre_jaune.png", 0);	//new


}

//_______________________________________________________________________________________________________________________________________________________



void Afficher_Sprite(sfSprite* _sprite, float _posX, float _posY, float _scaleX, float _scaleY, float _rotation, sfRenderWindow* _window)
{
	//printf("scale %f\n", _scaleY);

	sfVector2f tempScale = { _scaleX, _scaleY };
	sfVector2f position = { _posX, _posY };
	sfSprite_setPosition(_sprite, position);
	sfSprite_setScale(_sprite, tempScale);
	sfSprite_setRotation(_sprite, _rotation);
	sfRenderWindow_drawSprite(_window, _sprite, NULL);
}


//_______________________________________________________________________________________________________________________________________________________

void Display(INGAME* _Ingame, UTILS* _Utils)
{
	//Remplissage de la fenêtre en noir (début de toutes les instructions d'affichage)
	sfRenderWindow_clear(_Utils->window, sfBlack);


	if (_Utils->iEtat == STATEPLAY || _Utils->iEtat == STATEPAUSE)
	{
		Afficher_Sprite(_Ingame->Sprite.Map, _Ingame->Pos_Map.x, _Ingame->Pos_Map.y , 1.0f, 1.0f, 0.0f, _Utils->window);
		//Afficher_Sprite(_Ingame->Sprite.Map_Color, _Ingame->Pos_Map.x, _Ingame->Pos_Map.y, 1.0f, 1.0f, 0.0f, _Utils->window);

		//Affichage des bonus
		Bonus_Display(_Ingame, _Utils);

		//Affichage zombie
		//Affichage_Zombie(_Ingame, _Utils);  //Deplacé dans animation.cpp section zombie

		//Affichage de toute les animations (joueur/projectile/ hud...)
		AffichageAnim(_Ingame, _Utils);

		if (_Ingame->Joueur.iEtat == POISON)
		{
			Afficher_Sprite(_Ingame->Sprite.Infection, _Utils->CentreCamera.x + 200, _Utils->CentreCamera.y + 480, 1.0f, 1.0f, 0.0f, _Utils->window);		//affiche quand le perso est toucher par le toxico
		}
		
		for (int i = 0; i < _Ingame->tir.nbTir; i++)
		{
			Afficher_Sprite(_Ingame->Sprite.Bullet, _Ingame->tirs[i].position.x, _Ingame->tirs[i].position.y, 0.5f, 0.5f, directionToAngle(_Ingame->tirs[i].vOrientationTir), _Utils->window);
		}
		


		//Affichage particule
		Display_Particles(_Ingame, _Utils); 

		afficher_tir_toxic(_Ingame, _Utils);

		Display_Action_Decor(_Ingame, _Utils);

		Display_HUD(_Utils, _Ingame);

		//Affichage des points de combo / déblocage des bonus
		Combo_HUD(_Ingame, _Utils);

	}

	if (_Utils->iEtat == STATEDEFAITE)
	{
		Afficher_Sprite(_Ingame->Sprite.ecran_Mort, LONGUEUR / 2, HAUTEUR / 2, 1.0f, 1.0f, 0, _Utils->window);
		sfSound_stop(_Ingame->musique.musique_jeu);
		UpdateMusique(_Ingame, _Utils);
	}




	//printf("%0.02f %0.02f %0.02f\n", cos(_Ingame->Joueur.rotate_perso), sin(_Ingame->Joueur.rotate_perso), _Ingame->Joueur.rotate_perso);

	//MENU
	Menu_Display(_Ingame, _Utils);

	//SCORE
	Affichage_score(_Ingame, _Utils);

	sfRenderWindow_display(_Utils->window);
	
}

//_______________________________________________________________________________________________________________________________________________________






