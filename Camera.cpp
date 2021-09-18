#include "stdafx.h"

void Init_Camera(INGAME* _ingame, UTILS* _utils)
{
	_utils->Camera = sfRenderWindow_getDefaultView(_utils->window);  //Définition du cadre de la camera (aussi grand que la taille de l'ecran  1920*1080)
}

void Update_Camera(INGAME* _ingame, UTILS* _utils)
{
	if (_utils->iEtat == STATEPLAY)
	{
		//Si le joueur se trouve dans le coin superieur gauche de la map alors on bloque la CAMERA
		if (_ingame->Joueur.Position.x < 960 && _ingame->Joueur.Position.y < 540)
		{
			_utils->CentreCamera.x = 960;
			_utils->CentreCamera.y = 540;
		}
		//Si le joueur se trouve dans le coin superieur droit de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.x > 5184 && _ingame->Joueur.Position.y < 540)
		{
			_utils->CentreCamera.x = 5184;
			_utils->CentreCamera.y = 540;
		}
		//Si le joueur se trouve dans le coin inférieur gauche de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.x < 960 && _ingame->Joueur.Position.y > 4128)
		{
			_utils->CentreCamera.x = 960;
			_utils->CentreCamera.y = 4128;
		}
		//Si le joueur se trouve dans le coin inférieur droit de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.x > 5184 && _ingame->Joueur.Position.y > 4128)
		{
			_utils->CentreCamera.x = 5184;
			_utils->CentreCamera.y = 4128;
		}
		//Si le joueur se trouve dans la marge gauche de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.x < 960 )
		{
			_utils->CentreCamera.x = 960;
			_utils->CentreCamera.y = _ingame->Joueur.Position.y;
		}
		//Si le joueur se trouve dans la marge droite de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.x > 5184)
		{
			_utils->CentreCamera.x = 5184;
			_utils->CentreCamera.y = _ingame->Joueur.Position.y;
		}
		//Si le joueur se trouve dans la marge basse de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.y < 540)
		{
			_utils->CentreCamera.x = _ingame->Joueur.Position.x;
			_utils->CentreCamera.y = 540;
		}
		//Si le joueur se trouve dans la marge haut de la map alors on bloque la CAMERA
		else if (_ingame->Joueur.Position.y > 4128)
		{
			_utils->CentreCamera.x = _ingame->Joueur.Position.x;
			_utils->CentreCamera.y = 4128;
		}
		//Hors des marges la camera recentre sur le joueur
		else
		{
			_utils->CentreCamera.x = _ingame->Joueur.Position.x;
			_utils->CentreCamera.y = _ingame->Joueur.Position.y;
		}
	}

	else if (_utils->iEtat == STATEMENU || _utils->iEtat == STATEDEFAITE || _utils->iEtat == STATEPAUSE) //Dans le menu la camera est "teleporté" à la position des bouton d'option / menu etc..
	{
		_utils->CentreCamera.x = _ingame->Menu.pos_menu.x;
		_utils->CentreCamera.y = _ingame->Menu.pos_menu.y;
	}

	sfView_setCenter(_utils->Camera, _utils->CentreCamera);  //On centre la caméra
	sfRenderWindow_setView(_utils->window, _utils->Camera);  // La position centrale de la camera est positionnée sur le joueur

}
	