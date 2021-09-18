#include "stdafx.h"

void Gestion_Hud(INGAME* _Ingame, UTILS* _Utils)
{
	_Ingame->Hud.HP_position.x = _Utils->CentreCamera.x - 800.0f;
	_Ingame->Hud.HP_position.y = _Utils->CentreCamera.y + 500.0f;

	sfText_setCharacterSize(_Ingame->NB_munition.Grenade, 30);

	sfText_setPosition(_Ingame->NB_munition.Batte_de_baseball, (sfVector2f) { _Utils->CentreCamera.x + 820, _Utils->CentreCamera.y + 440.0f });
	sfText_setPosition(_Ingame->NB_munition.Pistolet, (sfVector2f) { _Utils->CentreCamera.x + 820, _Utils->CentreCamera.y + 440.0f	});
	sfText_setPosition(_Ingame->NB_munition.Fusil, (sfVector2f) { _Utils->CentreCamera.x + 820, _Utils->CentreCamera.y + 440.0f	 });
	sfText_setPosition(_Ingame->NB_munition.Fusil_a_pompe, (sfVector2f) { _Utils->CentreCamera.x + 820, _Utils->CentreCamera.y + 440.0f	});
	sfText_setPosition(_Ingame->NB_munition.Grenade, (sfVector2f) { _Utils->CentreCamera.x + 650, _Utils->CentreCamera.y + 440.0f});
	sfText_setPosition(_Ingame->NB_munition.LanceFlamme, (sfVector2f) { _Utils->CentreCamera.x + 820, _Utils->CentreCamera.y + 440.0f });

	sfText_setPosition(_Ingame->NB_munition.antidote, (sfVector2f) { _Utils->CentreCamera.x + 560.0f, _Utils->CentreCamera.y + 430.0f });	

	sfText_setPosition(_Ingame->texte.Nbr_vague , (sfVector2f) { _Utils->CentreCamera.x + 50, _Utils->CentreCamera.y - 530 });
	sfText_setScale(_Ingame->texte.Nbr_vague, (sfVector2f) { 2.5, 2.5 });
	sfText_setColor(_Ingame->texte.Nbr_vague, (sfColor) { 255, 255, 255, 255 });
	
	sfText_setPosition(_Ingame->texte.Timer_Wave, (sfVector2f) { _Utils->CentreCamera.x - 250, _Utils->CentreCamera.y - 460 });

	sfText_setScale(_Ingame->texte.Timer_Wave, (sfVector2f) { 1.5, 1.5 });
	sfText_setColor(_Ingame->texte.Timer_Wave, (sfColor) { 255, 255, 255, 255 });

}

void Update_HUD(INGAME* _Ingame, UTILS* _Utils)
{
	char temp[50];

	sprintf(temp, " %d / %d\n", 0, 0);
	sfText_setString(_Ingame->NB_munition.Batte_de_baseball, temp);

	sprintf(temp, " %d / %d\n", _Ingame->Ammo.iAmmo_Pistol_InClip, _Ingame->Ammo.iAmmo_Pistol_Total);
	sfText_setString(_Ingame->NB_munition.Pistolet, temp);

	sprintf(temp, " %d / %d\n", _Ingame->Ammo.iAmmo_Rifle_InClip, _Ingame->Ammo.iAmmo_Rifle_Total);
	sfText_setString(_Ingame->NB_munition.Fusil, temp);

	sprintf(temp, " %d / %d\n", _Ingame->Ammo.iAmmo_Shotgun_InClip, _Ingame->Ammo.iAmmo_Shotgun_Total);
	sfText_setString(_Ingame->NB_munition.Fusil_a_pompe, temp);

	/*sprintf(temp, " %d / %d\n", 0, 5);
	sfText_setString(_Ingame->NB_munition.Grenade, temp);*/

	sprintf(temp, " %d / %d\n", _Ingame->Ammo.iAmmo_fuel_InClip, _Ingame->Ammo.iAmmo_fuel_Total);
	sfText_setString(_Ingame->NB_munition.LanceFlamme, temp);

	//NEW
	if (_Ingame->Ammo.iAmmo_fuel_Total > 500)
	{
		_Ingame->Ammo.iAmmo_fuel_Total = 500;
	}

	sprintf(temp, "%d\n", _Ingame->Ammo.iNb_antidote);
	sfText_setString(_Ingame->NB_munition.antidote, temp);

	sprintf(temp, "%d\n", _Utils->iCompteur_Vague);
	sfText_setString(_Ingame->texte.Nbr_vague, temp);

	sprintf(temp, "Next Wave in %0.1f seconds\n", _Ingame->fTimer_Nouvelle_Vague);
	sfText_setString(_Ingame->texte.Timer_Wave, temp);


}

void Display_HUD(UTILS *_Utils, INGAME *_Ingame)
{
	Afficher_Sprite(_Ingame->Sprite.HUD, _Utils->CentreCamera.x, _Utils->CentreCamera.y, 1.0f, 1.0f, 0, _Utils->window);



	if (_Ingame->Hud.armes == Batte_de_baseball)
	{
		Afficher_Sprite(_Ingame->Sprite.Batte, _Utils->CentreCamera.x + 700, _Utils->CentreCamera.y + 420, 1.0f, 1.0f, 0, _Utils->window);
		sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.Batte_de_baseball, NULL);
	}
	else if (_Ingame->Hud.armes == Pistolet)
	{
		Afficher_Sprite(_Ingame->Sprite.Pistolet, _Utils->CentreCamera.x + 700, _Utils->CentreCamera.y + 420, 1.0f, 1.0f, 0, _Utils->window);
		sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.Pistolet, NULL);
	}
	else if (_Ingame->Hud.armes == Fusil)
	{
		Afficher_Sprite(_Ingame->Sprite.Fusil, _Utils->CentreCamera.x + 700, _Utils->CentreCamera.y + 420, 1.0f, 1.0f, 0, _Utils->window);
		sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.Fusil, NULL);
	}
	else if (_Ingame->Hud.armes == Fusil_a_pompe)
	{
		Afficher_Sprite(_Ingame->Sprite.Fusil_a_pompe, _Utils->CentreCamera.x + 700, _Utils->CentreCamera.y + 420, 1.0f, 1.0f, 0, _Utils->window);
		sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.Fusil_a_pompe, NULL);
	}
	else if (_Ingame->Hud.armes == LanceFlamme)
	{
		Afficher_Sprite(_Ingame->Sprite.LanceFlamme, _Utils->CentreCamera.x + 700, _Utils->CentreCamera.y + 420, 0.05f, 0.05f, 0, _Utils->window);
		sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.LanceFlamme, NULL);
	}

	/*Afficher_Sprite(_Ingame->Sprite.Grenade, _Utils->CentreCamera.x + 560, _Utils->CentreCamera.y + 460, 1.0f, 1.0f, 0, _Utils->window);
	sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.Grenade, NULL);*/

	Afficher_Sprite(_Ingame->Sprite.Antidote, _Utils->CentreCamera.x + 440.0f, _Utils->CentreCamera.y + 440.0f, 0.15f, 0.15f, 0, _Utils->window);
	sfRenderWindow_drawText(_Utils->window, _Ingame->NB_munition.antidote, NULL);

	Afficher_Sprite(_Ingame->Sprite.barre_endurance, _Utils->CentreCamera.x - 550.0f, _Utils->CentreCamera.y + 480.0f, _Ingame->Joueur.jauge_energie * 4.2, 0.14f, 0, _Utils->window);

	sfRenderWindow_drawText(_Utils->window, _Ingame->texte.Nbr_vague, NULL);


	if (_Ingame->fTimer_Nouvelle_Vague >= 0.0f)
	{
		sfRenderWindow_drawText(_Utils->window, _Ingame->texte.Timer_Wave, NULL);

	}



}
