#include "stdafx.h"

void Init_Munition(INGAME* _ingame, UTILS* _utils)
{
	_ingame->Ammo.iAmmo_Pistol_Total = 90;  //90
	_ingame->Ammo.iAmmo_Pistol_InClip = 9;
	_ingame->Ammo.iAmmo_Pistol_Max = MAX_PISTOL_AMMO;

	_ingame->Ammo.iAmmo_Rifle_Total = 180;
	_ingame->Ammo.iAmmo_Rifle_InClip = 30;
	_ingame->Ammo.iAmmo_Rifle_Max = MAX_RIFLE_AMMO;

	_ingame->Ammo.iAmmo_Shotgun_Total = 48;
	_ingame->Ammo.iAmmo_Shotgun_InClip = 12;
	_ingame->Ammo.iAmmo_Shotgun_Max = MAX_SHOTGUN_AMMO;

	_ingame->Ammo.iAmmo_fuel_Total = 500; //500
	_ingame->Ammo.iAmmo_fuel_InClip = 100;
	_ingame->Ammo.iAmmo_fuel_Max = MAX_FUEL;

}


void Add_Munition(INGAME* _ingame, UTILS* _utils)
{

		if (_ingame->bonus[1].bonustype == eAmmo_Pistol)
		{
			_ingame->Ammo.iAmmo_Pistol_Total += _ingame->Ammo.iAmmo_Pistol_Max; //ajout d'un chargeur
		}
		if (_ingame->bonus[1].bonustype == eAmmo_Rifle)
		{
			_ingame->Ammo.iAmmo_Rifle_Total += _ingame->Ammo.iAmmo_Rifle_Max;
		}
		if (_ingame->bonus[1].bonustype == eAmmo_Shotgun)
		{
			_ingame->Ammo.iAmmo_Shotgun_Total += _ingame->Ammo.iAmmo_Shotgun_Max;
		}

}
