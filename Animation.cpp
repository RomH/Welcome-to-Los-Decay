#include "stdafx.h"

void LectureFichier(char* _Path, sfSprite*** _tab_Sprite, ANIM_DEF* _TypeAnim, INGAME* _Ingame, UTILS* _Utils) //Fonction permettant de lire un fichier d'animation
{
	//Chargement des sprites a partir du fichier

	FILE*File;
	if (!(File = fopen(_Path, "rt")))
	{
		printf("Erreur d'acces au fichier def.txt\n");
		exit(EXIT_FAILURE);
	}

	char ctemp[255]; //Tableau de char temporaire

	int iCompteur = 0;

	while (fscanf(File, "%s", ctemp) != EOF)
	{
		//printf("%d\n", iCompteur);
		//On lit le premier mot (de la première ligne si premier tour de boucle)
		if (!strcmp(ctemp, "SPRITES"))
		{//Si le premier mot de la ligne est "SPRITES"
			int nbSprite = 0;
			fscanf(File, "%d", &nbSprite); //On sait qu'il y a un int juste après qui contient le nombre de sprites, donc on le charge

			*_tab_Sprite = (sfSprite**)malloc(sizeof(sfSprite*)*nbSprite); //On se sert du nombre précédemment récuperé pour initialiser le tableau de sprites du perso à la bonne taille

			for (int i = 0; i < nbSprite; i++)
			{ //Pour chaque case de ce tableau
				fscanf(File, "%s", ctemp); //On récupère le nom de fichier suivant
			  //printf("%s\n", ctempPhrase);
				(*_tab_Sprite)[i] = LoadSprite(ctemp, 1); //Et on s'en sert dans le LoadSprite pour charger le sprite courant dans la liste.
			}
		}
		else if (!strcmp(ctemp, "ANIM"))
		{ //Chargement des lignes d'animation
			fscanf(File, "%s", _TypeAnim->scSeq[iCompteur].cNomAnim);
			fscanf(File, "%d", &_TypeAnim->scSeq[iCompteur].iDebut);
			fscanf(File, "%d", &_TypeAnim->scSeq[iCompteur].iFin);
			fscanf(File, "%f", &_TypeAnim->scSeq[iCompteur].fTiming);

			/*printf("%s\t  %d   %d    %f\n", _Ingame->Anim_Joueur.scSeq[iCompteur].cNomAnim, _Ingame->Anim_Joueur.scSeq[iCompteur].iDebut,
					_Ingame->Anim_Joueur.scSeq[iCompteur].iFin, _Ingame->Anim_Joueur.scSeq[iCompteur].fTiming);*/

			iCompteur++;
		}
	}

	fclose(File);
}

int ChercheSequence(char* _nomAnim, ANIM_DEF* _Type_Anim, INGAME* _Ingame) //On recherche la séquence qui sera lue pour démarrer l'animation 
{
	int i = 0;

	for (i = 0; i < NB_MAX_SEQUENCE_ANIMATION; i++)
	{
		//printf("%d\n", i);
		if (strcmp(_nomAnim, _Type_Anim->scSeq[i].cNomAnim) == 0)
		{
			return i;
		}
	}
}


void LectureFichier_Pack(INGAME* _Ingame, UTILS* _Utils) //Regroupe toutes les fonctions de lecture de fichier
{
	LectureFichier("../Animation/Personnage/Def.txt", &_Ingame->Sprite.tabSprite_Joueur, &_Ingame->Anim_Joueur, _Ingame, _Utils); //Lecture des Animations Joueur
	_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE", &_Ingame->Anim_Joueur, _Ingame); //Animation par défaut au lancement du programme

	LectureFichier("../Animation/HUD/Hp_Bar/Def.txt", &_Ingame->Sprite.tabSprite_HPBar, &_Ingame->Anim_HPBar, _Ingame, _Utils); //Lecture des Animations Balle
	_Ingame->HPBar_Anim.currentSequence = ChercheSequence("HP_GLOW", &_Ingame->Anim_HPBar, _Ingame); //Animation par défaut au lancement du programme

	
	LectureFichier("../Animation/Zombie/Boomer/Def.txt", &_Ingame->Sprite.tabSprite_Boomer, &_Ingame->Anim_Boomer, _Ingame, _Utils);
	LectureFichier("../Animation/Zombie/ZombieNormal/Def.txt", &_Ingame->Sprite.tabSprite_Zombie, &_Ingame->Anim_ZombieNormal, _Ingame, _Utils);
	LectureFichier("../Animation/Zombie/Toxic/Def.txt", &_Ingame->Sprite.tabSprite_Toxic, &_Ingame->Anim_Toxic, _Ingame, _Utils);


	
}


//Influence l'animation  en fonction des touches pressées
void ControlAnimEvenementiel(INGAME* _Ingame, UTILS* _Utils)
{
	if (_Utils->event.type == sfEvtKeyReleased)
	{
		if (_Utils->event.key.code == sfKeyZ) //Si la touche haut est relachée = on passe sur l'anim d'immobilité 
		{
			//_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_DOS", &_Ingame->Anim_Joueur, _Ingame);
			_Ingame->Joueur.Direction_Perso_Joueur = DP_IMMOBILE;
		}
		if (_Utils->event.key.code == sfKeyQ)
		{
			//_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame);
			_Ingame->Joueur.Direction_Perso_Joueur = DP_IMMOBILE;
		}
		if (_Utils->event.key.code == sfKeyS)
		{
			//_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE", &_Ingame->Anim_Joueur, _Ingame);
			_Ingame->Joueur.Direction_Perso_Joueur = DP_IMMOBILE;
		}
		if (_Utils->event.key.code == sfKeyD)
		{
			//_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_DROITE", &_Ingame->Anim_Joueur, _Ingame);
			_Ingame->Joueur.Direction_Perso_Joueur = DP_IMMOBILE;
		}
	}
}

void UpdateAnim(INGAME* _Ingame, UTILS* _Utils) //Update des Animations
{
	//Toute les animation ont liés au temps
	if (_Ingame->Joueur.courir == TRUE)
	{
		_Ingame->Joueur.Timer_Anim += _Utils->fDeltatime * 1.2;
	}
	else 	_Ingame->Joueur.Timer_Anim += _Utils->fDeltatime;

	_Ingame->HPBar_Anim.Timer_Anim += _Utils->fDeltatime;

	for (int i = 0; i < _Ingame->iNbr_Zombie_Max; i++) //Modification de la vitesse d'animation si le boomer cour ou marche
	{
		if (_Ingame->Zombie[i].iIA == eBoomer)
		{
			if (_Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].Calcul.fDist_Joueur_Mob >= 300)
				{
					_Ingame->Zombie[i].Timer_Anim += _Utils->fDeltatime;
				}
				if (_Ingame->Zombie[i].Calcul.fDist_Joueur_Mob <= 300)
				{
					_Ingame->Zombie[i].Timer_Anim += _Utils->fDeltatime * 2;
				}
			}
			if (_Ingame->Zombie[i].iEtat == EXPLOSION)
			{
				_Ingame->Zombie[i].Timer_Anim += _Utils->fDeltatime;
			}	
		}
		if (_Ingame->Zombie[i].iIA == eZombie)
		{
			_Ingame->Zombie[i].Timer_Anim += _Utils->fDeltatime;

		}
		if (_Ingame->Zombie[i].iIA == eToxic)
		{
			_Ingame->Zombie[i].Timer_Anim += _Utils->fDeltatime;

		}
	}

	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	//Barre de vie

	if (_Ingame->Joueur.iEtat == NON_POISON)
	{
		_Ingame->HPBar_Anim.currentSequence = ChercheSequence("HP_GLOW", &_Ingame->Anim_HPBar, _Ingame); //Animation par défaut au lancement du programme
	}
	else if (_Ingame->Joueur.iEtat == POISON)
	{
		_Ingame->HPBar_Anim.currentSequence = ChercheSequence("HP_POISON", &_Ingame->Anim_HPBar, _Ingame); //Animation par défaut au lancement du programme
	}

	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	//IDLE ORIENTATION
	if (_Ingame->Joueur.Direction_Perso_Joueur == DP_IMMOBILE)
	{
		//IDLE DROITE
		if (_Ingame->Joueur.rotate_perso >= 135 && _Ingame->Joueur.rotate_perso < 225)
		{
			if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_DROITE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
			{
				_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_DROITE", &_Ingame->Anim_Joueur, _Ingame);
				_Ingame->Joueur.Timer_Anim = 0.0f;
			}
		}
		//IDLE FACE
		else if (_Ingame->Joueur.rotate_perso >= 225 && _Ingame->Joueur.rotate_perso < 315)
		{
			if (_Ingame->iArme_Choisie == Batte_de_baseball)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_FACE_BATTE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE_BATTE", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Pistolet)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_FACE_PISTOLET", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE_PISTOLET", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_FACE_FUSIL", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE_FUSIL", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil_a_pompe)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_FACE_SHOTGUN", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE_SHOTGUN", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == LanceFlamme)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_FACE_LANCEFLAMME", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_FACE_LANCEFLAMME", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
		}
		//IDLE GAUCHE
		else if (_Ingame->Joueur.rotate_perso >= 315 || _Ingame->Joueur.rotate_perso < 45)
		{
			if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
			{
				_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame);
				_Ingame->Joueur.Timer_Anim = 0.0f;
			}
		}
		//IDLE DOS
		else if (_Ingame->Joueur.rotate_perso >= 45 && _Ingame->Joueur.rotate_perso < 135)
		{
			if (_Ingame->iArme_Choisie == Batte_de_baseball)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_DOS_DEUXMAINS", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_DOS_DEUXMAINS", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Pistolet)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_DOS_PISTOLET", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_DOS_PISTOLET", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil || _Ingame->iArme_Choisie == Fusil_a_pompe || _Ingame->iArme_Choisie == LanceFlamme)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("IDLE_DOS_DEUXMAINS", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("IDLE_DOS_DEUXMAINS", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
		}
	}

	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

	//ANIMATION DEPLACEMENT VERTICAL
	if (_Ingame->Joueur.Direction_Perso_Joueur == DP_HAUT || _Ingame->Joueur.Direction_Perso_Joueur == DP_BAS)
	{
		//DROITE
		if (_Ingame->Joueur.rotate_perso >= 135 && _Ingame->Joueur.rotate_perso < 225)
		{
			if (_Ingame->Joueur.currentSequence != ChercheSequence("MARCHE_DROITE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
			{
				_Ingame->Joueur.currentSequence = ChercheSequence("MARCHE_DROITE", &_Ingame->Anim_Joueur, _Ingame);
				_Ingame->Joueur.Timer_Anim = 0.0f;
			}
		}
		//FACE
		else if (_Ingame->Joueur.rotate_perso >= 225 && _Ingame->Joueur.rotate_perso < 315)
		{
			if (_Ingame->iArme_Choisie == Batte_de_baseball)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_BATTE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_BATTE", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Pistolet)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_PISTOLET", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_PISTOLET", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_FUSIL", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_FUSIL", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil_a_pompe)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_SHOTGUN", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_SHOTGUN", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == LanceFlamme)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_LANCEFLAMME", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_LANCEFLAMME", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
		}
		//GAUCHE
		else if (_Ingame->Joueur.rotate_perso >= 315 || _Ingame->Joueur.rotate_perso < 45)
		{
			if (_Ingame->Joueur.currentSequence != ChercheSequence("MARCHE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
			{
				_Ingame->Joueur.currentSequence = ChercheSequence("MARCHE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame);
				_Ingame->Joueur.Timer_Anim = 0.0f;
			}
		}
		//DOS
		else if (_Ingame->Joueur.rotate_perso >= 45 && _Ingame->Joueur.rotate_perso < 135)
		{
			if (_Ingame->iArme_Choisie == Batte_de_baseball)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BATTE_HAUT", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BATTE_HAUT", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Pistolet)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("PISTOLET_HAUT", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("PISTOLET_HAUT", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil || _Ingame->iArme_Choisie == Fusil_a_pompe || _Ingame->iArme_Choisie == LanceFlamme)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("DEUXMAINS_HAUT", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("DEUXMAINS_HAUT", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			
		}
	}

	//ANIMATION DEPLACEMENT HORIZONTAL
	
	if (_Ingame->Joueur.Direction_Perso_Joueur == DP_GAUCHE || _Ingame->Joueur.Direction_Perso_Joueur == DP_HAUT_GAUCHE || _Ingame->Joueur.Direction_Perso_Joueur == DP_BAS_GAUCHE ||
		_Ingame->Joueur.Direction_Perso_Joueur == DP_DROITE || _Ingame->Joueur.Direction_Perso_Joueur == DP_HAUT_DROITE || _Ingame->Joueur.Direction_Perso_Joueur == DP_BAS_DROITE)
	{
		//DROITE
		if (_Ingame->Joueur.rotate_perso >= 135 && _Ingame->Joueur.rotate_perso < 225)
		{
			if (_Ingame->Joueur.currentSequence != ChercheSequence("MARCHE_DROITE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
			{
				_Ingame->Joueur.currentSequence = ChercheSequence("MARCHE_DROITE", &_Ingame->Anim_Joueur, _Ingame);
				_Ingame->Joueur.Timer_Anim = 0.0f;
			}
		}
		//FACE
		else if (_Ingame->Joueur.rotate_perso >= 225 && _Ingame->Joueur.rotate_perso < 315)
		{
			if (_Ingame->iArme_Choisie == Batte_de_baseball)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_BATTE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_BATTE", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Pistolet)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_PISTOLET", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_PISTOLET", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_FUSIL", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_FUSIL", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil_a_pompe)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_SHOTGUN", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_SHOTGUN", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == LanceFlamme)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BAS_LANCEFLAMME", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BAS_LANCEFLAMME", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
		}
		//GAUCHE
		else if (_Ingame->Joueur.rotate_perso >= 315 || _Ingame->Joueur.rotate_perso < 45)
		{
			if (_Ingame->Joueur.currentSequence != ChercheSequence("MARCHE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
			{
				_Ingame->Joueur.currentSequence = ChercheSequence("MARCHE_GAUCHE", &_Ingame->Anim_Joueur, _Ingame);
				_Ingame->Joueur.Timer_Anim = 0.0f;
			}
		}
		//DOS
		else if (_Ingame->Joueur.rotate_perso >= 45 && _Ingame->Joueur.rotate_perso < 135)
		{
			if (_Ingame->iArme_Choisie == Batte_de_baseball)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("BATTE_HAUT", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("BATTE_HAUT", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Pistolet)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("PISTOLET_HAUT", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("PISTOLET_HAUT", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
			else if (_Ingame->iArme_Choisie == Fusil || _Ingame->iArme_Choisie == Fusil_a_pompe || _Ingame->iArme_Choisie == LanceFlamme)
			{
				if (_Ingame->Joueur.currentSequence != ChercheSequence("DEUXMAINS_HAUT", &_Ingame->Anim_Joueur, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Joueur.currentSequence = ChercheSequence("DEUXMAINS_HAUT", &_Ingame->Anim_Joueur, _Ingame);
					_Ingame->Joueur.Timer_Anim = 0.0f;
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//ZOMBIE
	for (int i = 0; i < _Ingame->iNbr_Zombie_Max; i++)
	{
		// HAUT
		if (_Ingame->Zombie[i].Calcul.angle >= 45 && _Ingame->Zombie[i].Calcul.angle < 135)
		{
			////BOOMER
			if (_Ingame->Zombie[i].Type == eBoomer)
			{
				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("HAUT", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("HAUT", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else if (_Ingame->Zombie[i].iEtat == EXPLOSION)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("EXPLO_HAUT", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("EXPLO_HAUT", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//ZOMBIE NORMAL
			else if (_Ingame->Zombie[i].Type == eZombie && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].Attaque == TRUE)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("ATTACK_HAUT", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("ATTACK_HAUT", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("HAUT", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("HAUT", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				
			}
			//TOXIC
			else if (_Ingame->Zombie[i].Type == eToxic && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].currentSequence != ChercheSequence("HAUT", &_Ingame->Anim_Toxic, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Zombie[i].currentSequence = ChercheSequence("HAUT", &_Ingame->Anim_Toxic, _Ingame);
					_Ingame->Zombie[i].Timer_Anim = 0.0f;
				}
			}
		}
		//BAS
		else if (_Ingame->Zombie[i].Calcul.angle >= 225 && _Ingame->Zombie[i].Calcul.angle < 315)
		{
			//BOOMER
			if (_Ingame->Zombie[i].Type == eBoomer)
			{
				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("BAS", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("BAS", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else if (_Ingame->Zombie[i].iEtat == EXPLOSION)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("EXPLO_BAS", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("EXPLO_BAS", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//ZOMBIE NORMAL
			else if (_Ingame->Zombie[i].Type == eZombie && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].Attaque == TRUE)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("ATTACK_BAS", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("ATTACK_BAS", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("BAS", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("BAS", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//TOXIC
			else if (_Ingame->Zombie[i].Type == eToxic && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].currentSequence != ChercheSequence("BAS", &_Ingame->Anim_Toxic, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Zombie[i].currentSequence = ChercheSequence("BAS", &_Ingame->Anim_Toxic, _Ingame);
					_Ingame->Zombie[i].Timer_Anim = 0.0f;
				}
			}
		}

		//DROITE
		else if (_Ingame->Zombie[i].Calcul.angle >= 135 && _Ingame->Zombie[i].Calcul.angle < 225)
		{
			//BOOMER
			if (_Ingame->Zombie[i].Type == eBoomer)
			{
				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("DROITE", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("DROITE", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else if (_Ingame->Zombie[i].iEtat == EXPLOSION)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("EXPLO_DROITE", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("EXPLO_DROITE", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//ZOMBIE NORMAL
			else if (_Ingame->Zombie[i].Type == eZombie && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].Attaque == TRUE)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("ATTACK_DROITE", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("ATTACK_DROITE", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("DROITE", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("DROITE", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//TOXIC
			else if (_Ingame->Zombie[i].Type == eToxic && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].currentSequence != ChercheSequence("DROITE", &_Ingame->Anim_Toxic, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Zombie[i].currentSequence = ChercheSequence("DROITE", &_Ingame->Anim_Toxic, _Ingame);
					_Ingame->Zombie[i].Timer_Anim = 0.0f;
				}
			}
		}

		//GAUCHE
		else if (_Ingame->Zombie[i].Calcul.angle >= 315 || _Ingame->Zombie[i].Calcul.angle < 45)
		{
			//BOOMER
			if (_Ingame->Zombie[i].Type == eBoomer)
			{
				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("GAUCHE", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("GAUCHE", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else if (_Ingame->Zombie[i].iEtat == EXPLOSION)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("EXPLO_GAUCHE", &_Ingame->Anim_Boomer, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("EXPLO_GAUCHE", &_Ingame->Anim_Boomer, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//ZOMBIE NORMAL
			else if (_Ingame->Zombie[i].Type == eZombie && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].Attaque == TRUE)
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("ATTACK_GAUCHE", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("ATTACK_GAUCHE", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
				else
				{
					if (_Ingame->Zombie[i].currentSequence != ChercheSequence("GAUCHE", &_Ingame->Anim_ZombieNormal, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
					{
						_Ingame->Zombie[i].currentSequence = ChercheSequence("GAUCHE", &_Ingame->Anim_ZombieNormal, _Ingame);
						_Ingame->Zombie[i].Timer_Anim = 0.0f;
					}
				}
			}
			//TOXIC
			else if (_Ingame->Zombie[i].Type == eToxic && _Ingame->Zombie[i].iEtat == VIVANT)
			{
				if (_Ingame->Zombie[i].currentSequence != ChercheSequence("GAUCHE", &_Ingame->Anim_Toxic, _Ingame)) //Si on etait pas sur cette animation, on s'y met et on remet le compteur a zero
				{
					_Ingame->Zombie[i].currentSequence = ChercheSequence("GAUCHE", &_Ingame->Anim_Toxic, _Ingame);
					_Ingame->Zombie[i].Timer_Anim = 0.0f;
				}
			}
		}
	}

	

}



// Affichage des animations
void AffichageAnim(INGAME* _Ingame, UTILS* _Utils)
{
	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	//JOUEUR
	//Détermination du nombre d'image total de la séquence (utile par la suite
	_Ingame->Anim_Joueur.iNbImageSequence = _Ingame->Anim_Joueur.scSeq[_Ingame->Joueur.currentSequence].iFin - _Ingame->Anim_Joueur.scSeq[_Ingame->Joueur.currentSequence].iDebut + 1;

	//printf("NBImage:%d   currentSeq:%d   fin:%d  debut:%d\n", _Ingame->Anim_Joueur.iNbImageSequence, _Ingame->Joueur.currentSequence, _Ingame->Anim_Joueur.scSeq[_Ingame->Joueur.currentSequence].iFin, _Ingame->Anim_Joueur.scSeq[_Ingame->Joueur.currentSequence].iDebut);
	//Déterminer la position dans laquelle on se trouve au sein de la séquence
	_Ingame->Joueur.iPositionSequence = (int)(_Ingame->Joueur.Timer_Anim / _Ingame->Anim_Joueur.scSeq[_Ingame->Joueur.currentSequence].fTiming) % (_Ingame->Anim_Joueur.iNbImageSequence);  //DEBUG    //_Ingame->Anim_Joueur.iNbImageSequence

	//Clignotement
	if (_Ingame->Joueur.Timer_clignotement >= 0.15) //On fait clignoter les sprites d'animation perso quand le joueur se fait toucher
	{
		//La position au sein de la séquence + la position du début de la séquence dans la timeline = la position courante dans la timeline
		Afficher_Sprite(_Ingame->Sprite.tabSprite_Joueur[_Ingame->Anim_Joueur.scSeq[_Ingame->Joueur.currentSequence].iDebut + _Ingame->Joueur.iPositionSequence],
			_Ingame->Joueur.Position.x, _Ingame->Joueur.Position.y, 0.5f, 0.5f, 0.0f, _Utils->window);

		Affichage_Weapon(_Ingame, _Utils);
	}

	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	//HP BAR
	//Détermination du nombre d'image total de la séquence (utile par la suite
	_Ingame->Anim_HPBar.iNbImageSequence = _Ingame->Anim_HPBar.scSeq[_Ingame->HPBar_Anim.currentSequence].iFin - _Ingame->Anim_HPBar.scSeq[_Ingame->HPBar_Anim.currentSequence].iDebut + 1;
	//Déterminer la position dans laquelle on se trouve au sein de la séquence
	_Ingame->HPBar_Anim.iPositionSequence = (int)(_Ingame->HPBar_Anim.Timer_Anim / _Ingame->Anim_HPBar.scSeq[_Ingame->HPBar_Anim.currentSequence].fTiming) % (_Ingame->Anim_HPBar.iNbImageSequence);

	//BARRE HP HUD
	if (_Utils->iHud_HP == STATEHUD_HP2 || _Utils->iHud_HP == STATEHUD_HP3)
	{
		Afficher_Sprite(_Ingame->Sprite.tabSprite_HPBar[_Ingame->Anim_HPBar.scSeq[_Ingame->HPBar_Anim.currentSequence].iDebut + _Ingame->HPBar_Anim.iPositionSequence],
			_Ingame->Hud.HP_position.x + 23.7f, _Ingame->Hud.HP_position.y, 0.30f, 0.65f, 0.0f, _Utils->window);

		int tempPV = _Ingame->Joueur.iPdv - 100;


		if (_Ingame->Joueur.iEtat == NON_POISON)
		{
			Afficher_Sprite(_Ingame->Sprite.HP_Vide, _Ingame->Hud.HP_position.x + 103.0f, _Ingame->Hud.HP_position.y + 21.0f, -tempPV *0.00305, 0.65f, -180.0f, _Utils->window);
			Afficher_Sprite(_Ingame->Sprite.HP_Piston, _Ingame->Hud.HP_position.x + 187.0f + (tempPV * 1.60), _Ingame->Hud.HP_position.y, 0.30f, 0.60f, -180.0f, _Utils->window);
			Afficher_Sprite(_Ingame->Sprite.HP_Seringue, _Ingame->Hud.HP_position.x, _Ingame->Hud.HP_position.y, 0.30f, 0.59f, -180.0f, _Utils->window);
		}
		else if (_Ingame->Joueur.iEtat == POISON)
		{
			Afficher_Sprite(_Ingame->Sprite.HP_VidePoison, _Ingame->Hud.HP_position.x + 103.0f, _Ingame->Hud.HP_position.y + 21.0f, -tempPV *0.00305, 0.65f, -180.0f, _Utils->window);
			Afficher_Sprite(_Ingame->Sprite.HP_PistonPoison, _Ingame->Hud.HP_position.x + 187.0f + (tempPV * 1.60), _Ingame->Hud.HP_position.y, 0.30f, 0.60f, -180.0f, _Utils->window);
			Afficher_Sprite(_Ingame->Sprite.HP_SeringuePoison, _Ingame->Hud.HP_position.x, _Ingame->Hud.HP_position.y, 0.30f, 0.59f, -180.0f, _Utils->window);
		}
		
	}

	//"ON HEAD"
	if (_Utils->iHud_HP == STATEHUD_HP1 || _Utils->iHud_HP == STATEHUD_HP3)
	{
		Afficher_Sprite(_Ingame->Sprite.barre_rouge, _Ingame->Joueur.Position.x - XPERSO / 2, _Ingame->Joueur.Position.y - 115, _Ingame->Joueur.iPdv * 0.1, 0.5, 0, _Utils->window);
	}

	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	//ZOMBIES

	for (int i = 0; i < _Ingame->iNbr_Zombie_Max; i++)
	{			
		//affichage des zombies uniquement dans le FOV de la camera
		if (_Ingame->Zombie[i].position.y - 150.2f <= (_Utils->CentreCamera.y + (HAUTEUR / 2)) &&
			_Ingame->Zombie[i].position.y + 150.2f >= (_Utils->CentreCamera.y - (HAUTEUR / 2)) &&
			_Ingame->Zombie[i].position.x - 99.6f <= (_Utils->CentreCamera.x + (LONGUEUR / 2)) &&
			_Ingame->Zombie[i].position.x + 99.6f >= (_Utils->CentreCamera.x - (LONGUEUR / 2)))
		{
			//BOOMER ANIMATION
			if (_Ingame->Zombie[i].Type == eBoomer)
			{
				//Détermination du nombre d'image total de la séquence (utile par la suite
				_Ingame->Anim_Boomer.iNbImageSequence = _Ingame->Anim_Boomer.scSeq[_Ingame->Zombie[i].currentSequence].iFin - _Ingame->Anim_Boomer.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + 1;
				//Déterminer la position dans laquelle on se trouve au sein de la séquence
				_Ingame->Zombie[i].iPositionSequence = (int)(_Ingame->Zombie[i].Timer_Anim / _Ingame->Anim_Boomer.scSeq[_Ingame->Zombie[i].currentSequence].fTiming) % (_Ingame->Anim_Boomer.iNbImageSequence);

				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					Afficher_Sprite(_Ingame->Sprite.tabSprite_Boomer[_Ingame->Anim_Boomer.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + _Ingame->Zombie[i].iPositionSequence],
						_Ingame->Zombie[i].position.x, _Ingame->Zombie[i].position.y, 0.40f, 0.40f, 0.0, _Utils->window);
				}
				else if (_Ingame->Zombie[i].iEtat == EXPLOSION)
				{
					Afficher_Sprite(_Ingame->Sprite.tabSprite_Boomer[_Ingame->Anim_Boomer.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + _Ingame->Zombie[i].iPositionSequence],
						_Ingame->Zombie[i].position.x, _Ingame->Zombie[i].position.y, 0.40f, 0.40f, 0.0, _Utils->window);
				}
			}

			//ZOMBIE NORMAL
			else if (_Ingame->Zombie[i].Type == eZombie)
			{
				//Détermination du nombre d'image total de la séquence (utile par la suite
				_Ingame->Anim_ZombieNormal.iNbImageSequence = _Ingame->Anim_ZombieNormal.scSeq[_Ingame->Zombie[i].currentSequence].iFin - _Ingame->Anim_ZombieNormal.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + 1;
				//Déterminer la position dans laquelle on se trouve au sein de la séquence
				_Ingame->Zombie[i].iPositionSequence = (int)(_Ingame->Zombie[i].Timer_Anim / _Ingame->Anim_ZombieNormal.scSeq[_Ingame->Zombie[i].currentSequence].fTiming) % (_Ingame->Anim_ZombieNormal.iNbImageSequence);

				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					Afficher_Sprite(_Ingame->Sprite.tabSprite_Zombie[_Ingame->Anim_ZombieNormal.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + _Ingame->Zombie[i].iPositionSequence],
						_Ingame->Zombie[i].position.x, _Ingame->Zombie[i].position.y, 0.50f, 0.50f, 0.0, _Utils->window);
				}
			}

			//ZOMBIE NORMAL
			if (_Ingame->Zombie[i].Type == eToxic)
			{
				//Détermination du nombre d'image total de la séquence (utile par la suite
				_Ingame->Anim_Toxic.iNbImageSequence = _Ingame->Anim_Toxic.scSeq[_Ingame->Zombie[i].currentSequence].iFin - _Ingame->Anim_Toxic.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + 1;
				//Déterminer la position dans laquelle on se trouve au sein de la séquence
				_Ingame->Zombie[i].iPositionSequence = (int)(_Ingame->Zombie[i].Timer_Anim / _Ingame->Anim_Toxic.scSeq[_Ingame->Zombie[i].currentSequence].fTiming) % (_Ingame->Anim_Toxic.iNbImageSequence);

				if (_Ingame->Zombie[i].iEtat == VIVANT)
				{
					Afficher_Sprite(_Ingame->Sprite.tabSprite_Toxic[_Ingame->Anim_Toxic.scSeq[_Ingame->Zombie[i].currentSequence].iDebut + _Ingame->Zombie[i].iPositionSequence],
						_Ingame->Zombie[i].position.x, _Ingame->Zombie[i].position.y, 0.50f, 0.50f, 0.0, _Utils->window);
				}
			}
		}	
	}
}
