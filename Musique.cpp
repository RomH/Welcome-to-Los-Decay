#include "stdafx.h"

#define Z_No_Sound 5.0f
#define Z_sound_01 2.065f //Zombie de base
#define Z_sound_02 1.0f

sfSound* LoadSound(char* _sNom)
{
	sfSound* son;
	sfSoundBuffer* buffer;

	buffer = sfSoundBuffer_createFromFile(_sNom);
	son = sfSound_create();
	sfSound_setBuffer(son, buffer);

	return son;
}

void LoadSound_Pack(UTILS* _utils, INGAME* _ingame)
{
	_ingame->musique.musique_menu = LoadSound("../Sons/Menu_jeu.ogg");
	_ingame->musique.musique_jeu = LoadSound("../Sons/Musique_jeu.ogg");
	_ingame->musique.bruit_pistolet = LoadSound("../Sons/Pistolet_bruit.ogg");
	_ingame->musique.bruit_fusil_a_pompe = LoadSound("../Sons/Fusil_a_pompe_bruit.ogg");
	_ingame->musique.bruit_fusil = LoadSound("../Sons/Fusil_bruit.ogg");
	_ingame->musique.Degat_joueur = LoadSound("../Sons/Degat_joueur.ogg");
	_ingame->musique.bruit_course = LoadSound("../Sons/marche_joueur.ogg");		//new
	_ingame->musique.canette = LoadSound("../Sons/canette.ogg");		//new
	//_ingame->musique.lance_flamme = LoadSound("../Sons/lance_flamme.ogg");		//new
	_ingame->musique.bruit_zombie = LoadSound("../Sons/bruit_zombie.ogg");
	_ingame->musique.bruit_boomer = LoadSound("../Sons/bruit_boomer.ogg");
	_ingame->musique.explosion_boomer = LoadSound("../Sons/BoomerExplosion.ogg");
	_ingame->musique.Mort = LoadSound("../Sons/Mort.ogg");

	_ingame->musique.lancement_manche = LoadSound("../Sons/Horde.ogg");

}

void lecture_musique(UTILS* _utils, INGAME* _ingame, sfSound* sound, float volume, sfBool is_boocle)
{
	sfSound_setVolume(sound, volume);
	sfSound_play(sound);
	sfSound_setLoop(sound, is_boocle);
}

void initialisation_sonsZombie(UTILS* _utils, INGAME* _ingame)
{
	_ingame->musique.timer_bruit_zombie = 0.0f;
	_ingame->son_zombie = 0;
	_ingame->musique.rand_pause_time = 0;
	_ingame->reset_Zsound = FALSE;
}


//new//
void bruitage_des_zombies(UTILS* _utils, INGAME* _ingame)
{
	if (_ingame->fTimer_Nouvelle_Vague <= 0.0f)
	{
		if (_utils->iEtat == STATEPLAY)
		{
			if (_ingame->son_zombie == 0 && _ingame->musique.timer_bruit_zombie == 0.0f)
			{
				int random = rand() % 3; //pour randomiser les sons
				_ingame->musique.sound_undead = random; //l'enum recup la valeur du random pour jouer un son correspondant à cette valeur
				_ingame->musique.rand_pause_time = rand() % 3 + 1; // pour randomiser un durée supp pour éviter de trop grosse répétitions
			}

			switch (_ingame->musique.sound_undead)
			{
				//Aucun son
			case eNo_sound:
				if (_ingame->son_zombie == 0) //play
				{
					_ingame->musique.timer_bruit_zombie += _utils->fDeltatime; //timer

					if (_ingame->musique.timer_bruit_zombie >= Z_No_Sound)
					{
						_ingame->musique.timer_bruit_zombie = 0.0f;
					}
				}
				//_utils->fDeltatime;
				else if (_ingame->son_zombie == 1)
				{
					_ingame->musique.timer_bruit_zombie += _utils->fDeltatime;
					if (_ingame->musique.timer_bruit_zombie >= Z_No_Sound)
					{
						_ingame->musique.timer_bruit_zombie = Z_No_Sound;
					}
				}
				break;

				//Zombie de base
			case eZombie_sound:
				if (_ingame->son_zombie == 0) //play
				{
					_ingame->musique.timer_bruit_zombie += _utils->fDeltatime; //timer

					if (_ingame->musique.timer_bruit_zombie >= Z_sound_01 + (float)_ingame->musique.rand_pause_time)
					{
						lecture_musique(_utils, _ingame, _ingame->musique.bruit_zombie, 8, 0); //lecture son

						_ingame->musique.timer_bruit_zombie = 0.0f;
					}
				}
				else if (_ingame->son_zombie == 1)
				{
					_ingame->musique.timer_bruit_zombie += _utils->fDeltatime;
					if (_ingame->musique.timer_bruit_zombie >= Z_sound_01 + (float)_ingame->musique.rand_pause_time)
					{
						_ingame->musique.timer_bruit_zombie = Z_sound_01 + (float)_ingame->musique.rand_pause_time;
					}
				}
				break;


			case eBoomer_sound:
				if (_ingame->son_zombie == 0) //play
				{
					_ingame->musique.timer_bruit_zombie += _utils->fDeltatime; //timer

					if (_ingame->musique.timer_bruit_zombie >= Z_sound_02 + (float)_ingame->musique.rand_pause_time)
					{
						lecture_musique(_utils, _ingame, _ingame->musique.bruit_boomer, 18, 0); //lecture son

						_ingame->musique.timer_bruit_zombie = 0.0f;
					}
				}
				else if (_ingame->son_zombie == 1)
				{
					_ingame->musique.timer_bruit_zombie += _utils->fDeltatime;
					if (_ingame->musique.timer_bruit_zombie >= Z_sound_02 + (float)_ingame->musique.rand_pause_time)
					{
						_ingame->musique.timer_bruit_zombie = Z_sound_02 + (float)_ingame->musique.rand_pause_time;
					}
				}
				break;
			}
		}
	}
	//CRI DE HORDE AU LANCEMENT D'UNE VAGUE
	if (_ingame->fTimer_Nouvelle_Vague >= 2.0f) 
	{
		lecture_musique(_utils, _ingame, _ingame->musique.lancement_manche, 15, 0); //lecture son

	}

}

//fin new//

void UpdateMusique(INGAME* _ingame, UTILS* _utils)
{
	if (_utils->iEtat == STATEMENU)
	{
		if (_ingame->Lancement_musique == 0)
		{
			//printf("test");
			lecture_musique(_utils, _ingame, _ingame->musique.musique_menu, 8, 1);
			_ingame->Lancement_musique = 1;
		}
	}

	if (_utils->iEtat == STATEPLAY)
	{
		if (_ingame->Lancement_musique == 1)
		{
			lecture_musique(_utils, _ingame, _ingame->musique.musique_jeu, 5, 1);
			_ingame->Lancement_musique = 2;
		}

	}
	if (_utils->iEtat == STATEDEFAITE)
	{
		if (_ingame->Lancement_musique == 2)
		{
			lecture_musique(_utils, _ingame, _ingame->musique.Mort, 8, 0);
			_ingame->Lancement_musique = 3;
		}
	}
}


void SonMarche(INGAME* _ingame, UTILS* _utils)
{
	//new//
	if (_ingame->musique.son_active == 0)
	{
		_ingame->musique.time_deplacement += _utils->fDeltatime;

		if (_ingame->musique.time_deplacement >= MARCHE_JOUEUR)
		{
			lecture_musique(_utils, _ingame, _ingame->musique.bruit_course, 1, 0);
			_ingame->musique.time_deplacement = 0.0f;

		}
	}
	else if (_ingame->musique.son_active == 1)
	{
		_ingame->musique.time_deplacement += _utils->fDeltatime;

		if (_ingame->musique.time_deplacement >= MARCHE_JOUEUR)
		{
			_ingame->musique.time_deplacement = MARCHE_JOUEUR;
		}
	}

}


void protection_son(INGAME* _ingame, UTILS* _utils)
{
	if (_utils->iEtat == STATEPAUSE)
	{
		sfSound_stop(_ingame->musique.lancement_manche);
		sfSound_stop(_ingame->musique.bruit_boomer);
		sfSound_stop(_ingame->musique.bruit_zombie);
		sfSound_stop(_ingame->musique.bruit_course);
		sfSound_stop(_ingame->musique.bruit_fusil);
		sfSound_stop(_ingame->musique.bruit_fusil_a_pompe);
		sfSound_stop(_ingame->musique.bruit_pistolet);
		sfSound_stop(_ingame->musique.bruit_pistolet);
		sfSound_stop(_ingame->musique.canette);
		sfSound_stop(_ingame->musique.Degat_joueur);
		sfSound_stop(_ingame->musique.explosion_boomer);
		sfSound_stop(_ingame->musique.Mort);
		sfSound_stop(_ingame->musique.musique_menu);
	}
	if (_utils->iEtat == STATEDEFAITE)
	{
		sfSound_stop(_ingame->musique.lancement_manche);
		sfSound_stop(_ingame->musique.bruit_boomer);
		sfSound_stop(_ingame->musique.bruit_zombie);
		sfSound_stop(_ingame->musique.bruit_course);
		sfSound_stop(_ingame->musique.bruit_fusil);
		sfSound_stop(_ingame->musique.bruit_fusil_a_pompe);
		sfSound_stop(_ingame->musique.bruit_pistolet);
		sfSound_stop(_ingame->musique.bruit_pistolet);
		sfSound_stop(_ingame->musique.canette);
		sfSound_stop(_ingame->musique.Degat_joueur);
		sfSound_stop(_ingame->musique.explosion_boomer);
		sfSound_stop(_ingame->musique.musique_jeu);
		sfSound_stop(_ingame->musique.musique_menu);
	}
	if (_utils->iEtat == STATEMENU)
	{
		sfSound_stop(_ingame->musique.lancement_manche);
		sfSound_stop(_ingame->musique.bruit_boomer);
		sfSound_stop(_ingame->musique.bruit_zombie);
		sfSound_stop(_ingame->musique.bruit_course);
		sfSound_stop(_ingame->musique.bruit_fusil);
		sfSound_stop(_ingame->musique.bruit_fusil_a_pompe);
		sfSound_stop(_ingame->musique.bruit_pistolet);
		sfSound_stop(_ingame->musique.bruit_pistolet);
		sfSound_stop(_ingame->musique.canette);
		sfSound_stop(_ingame->musique.Degat_joueur);
		sfSound_stop(_ingame->musique.explosion_boomer);
		sfSound_stop(_ingame->musique.Mort);
		sfSound_stop(_ingame->musique.musique_jeu);
	}


}



