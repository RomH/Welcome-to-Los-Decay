#include "stdafx.h"

void Initialisation_score(INGAME* _ingame, UTILS* _utils)
{
	_ingame->texte.Score = LoadText("../Police/POLICE2.ttf");
	_ingame->texte.EnterName = LoadText("../Police/POLICE.ttf");
	_ingame->texte.MenuScore = LoadText("../Police/POLICE.ttf");

}

void Affichage_score(INGAME* _ingame, UTILS* _utils)
{
	if (_utils->iEtat == STATEPAUSE) //Affichage de tout les scores + noms dans le menu
	{
		/*char temp[50];

		sprintf(temp, "Scores:\n");
		sfText_setScale(_ingame->texte.MenuScore, (sfVector2f) { 1.5, 1.5 });
		sfText_setString(_ingame->texte.MenuScore, temp);
		sfText_setPosition(_ingame->texte.MenuScore, (sfVector2f) { 1300, 45 });
		sfText_setColor(_ingame->texte.MenuScore, (sfColor) { 255, 0, 0, 255 });
		sfRenderWindow_drawText(_utils->window, _ingame->texte.MenuScore, NULL);*/


		char tempName[50];

		for (int i = 0; i < NB_HIGHSCORE; i++)
		{
			sprintf(tempName, "%s\n", _ingame->list_highscores[i].nom_save);
			sfText_setScale(_ingame->texte.MenuScore, (sfVector2f) { 1.5, 1.5 });
			sfText_setString(_ingame->texte.MenuScore, tempName);
			sfText_setPosition(_ingame->texte.MenuScore, (sfVector2f) { 1030, 357 + i * 64.5 });
			sfText_setColor(_ingame->texte.MenuScore, (sfColor) { 255, 0, 0, 255 });
			sfRenderWindow_drawText(_utils->window, _ingame->texte.MenuScore, NULL);
		}
		char tempScore[50];

		for (int i = 0; i < NB_HIGHSCORE; i++)
		{
			sprintf(tempScore, "%d\n", _ingame->list_highscores[i].score);
			sfText_setScale(_ingame->texte.MenuScore, (sfVector2f) { 1.5, 1.5 });
			sfText_setString(_ingame->texte.MenuScore, tempScore);
			sfText_setPosition(_ingame->texte.MenuScore, (sfVector2f) { 1380, 357 + i * 64.5 });
			sfText_setColor(_ingame->texte.MenuScore, (sfColor) { 255, 0, 0, 255 });
			sfRenderWindow_drawText(_utils->window, _ingame->texte.MenuScore, NULL);
		}
	}
	//Score en jeu
	else if (_utils->iEtat == STATEPLAY /*|| _utils->iEtat == STATEPAUSE*/)  //Affichage du score actuel pendant le jeu
	{
		char temp[50];
		sprintf(temp, "Score: %0.2d", _ingame->score_courant.Score);
		sfText_setScale(_ingame->texte.Score, (sfVector2f) { 1.5, 1.5 });
		sfText_setString(_ingame->texte.Score, temp);
		sfText_setPosition(_ingame->texte.Score, (sfVector2f) { _utils->CentreCamera.x + 600, _utils->CentreCamera.y - 500 });
		sfText_setColor(_ingame->texte.Score, (sfColor) { 255, 255, 255, 255 });  // 57 7 7 
		sfRenderWindow_drawText(_utils->window, _ingame->texte.Score, NULL);
	}
	else if (_utils->iEtat == STATEDEFAITE) //Affichage du score sur l'ecran de défaite + affichage nom joueur
	{
		char temp[50];
		sprintf(temp, "Score: %0.2d", _ingame->score_courant.Score);
		sfText_setScale(_ingame->texte.Score, (sfVector2f) { 2.0, 2.0 });
		sfText_setString(_ingame->texte.Score, temp);
		sfText_setPosition(_ingame->texte.Score, (sfVector2f) { 1350, 750 });
		sfText_setColor(_ingame->texte.Score, (sfColor) { 57, 7, 7, 255 });
		sfRenderWindow_drawText(_utils->window, _ingame->texte.Score, NULL);

		char Name[25];
		sprintf(Name, "Enter Name : %s", _ingame->score_courant.chare);
		sfText_setScale(_ingame->texte.EnterName, (sfVector2f) { 2.0, 2.0 });
		sfText_setString(_ingame->texte.EnterName, Name);
		sfText_setPosition(_ingame->texte.EnterName, (sfVector2f) { 1100, 800 });
		sfText_setColor(_ingame->texte.EnterName, (sfColor) { 255, 255, 255, 255 });
		sfRenderWindow_drawText(_utils->window, _ingame->texte.EnterName, NULL);
	}
}


void EnterName(INGAME* _ingame, UTILS* _utils)
{
	if (_utils->iEtat == STATEDEFAITE)
	{
		char nom[10] = "";

		if (_utils->event.key.code == sfKeyBack) //efface le nom touche retour arrière
		{
			for (int i = 0; i <= CARACTERE_NOM; i++)
			{
				_ingame->score_courant.chare[i] = NULL;
			}
		}
		else if (_utils->event.key.code == sfKeyReturn) //Touche entré sauvegarde le score et passe vers le menu
		{
			Tri_Score(_utils, _ingame);
			Sauvegarde_score(_utils, _ingame);

			sfSound_stop(_ingame->musique.musique_jeu);		//NEW
			sfSound_stop(_ingame->musique.Mort);		//NEW
			_ingame->Lancement_musique = 0;		//NEW

			New_Game(_ingame, _utils);
			_utils->iEtat = STATEMENU;
		}

		if (_ingame->score_courant.chare[CARACTERE_NOM] == NULL)
		{
			switch (_utils->event.key.code)
			{
			case sfKeyA:	strcat(nom, "A"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyB:	strcat(nom, "B"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyC:	strcat(nom, "C"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyD:	strcat(nom, "D"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyE:	strcat(nom, "E"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyF:	strcat(nom, "F"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyG:	strcat(nom, "G"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyH:	strcat(nom, "H"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyI:	strcat(nom, "I"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyJ:	strcat(nom, "J"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyK:	strcat(nom, "K"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyL:	strcat(nom, "L"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyM:	strcat(nom, "M"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyN:	strcat(nom, "N"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyO:	strcat(nom, "O"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyP:	strcat(nom, "P"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyQ:	strcat(nom, "Q"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyR:	strcat(nom, "R"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyS:	strcat(nom, "S"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyT:	strcat(nom, "T"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyU:	strcat(nom, "U"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyV:	strcat(nom, "V"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyW:	strcat(nom, "W"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyX:	strcat(nom, "X"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyY:	strcat(nom, "Y"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			case sfKeyZ:	strcat(nom, "Z"); strcat(_ingame->score_courant.chare, nom); strcpy(nom, "");  break;
			}
		}
	}
}


void Chargement_score(UTILS* _utils, INGAME* _ingame)
{
	FILE* fichier_score;

	if (!(fichier_score = fopen("../Scores/fichier_score.bin", "rb")))
	{
		printf("\nerreur lors de l'ouverture du fichier\n");
		exit(EXIT_FAILURE);
	}

	fread(_ingame->list_highscores, sizeof(HIGH_SCORE), NB_HIGHSCORE, fichier_score);
	fclose(fichier_score);
}

void Sauvegarde_score(UTILS* _utils, INGAME* _ingame)
{

	FILE* fichier_score;

	if (!(fichier_score = fopen("../Scores/fichier_score.bin", "wb")))
	{
		printf("\nerreur lors de l'ouverture du fichier\n");
		exit(EXIT_FAILURE);
	}
	fwrite(_ingame->list_highscores, sizeof(HIGH_SCORE), NB_HIGHSCORE, fichier_score);

	fclose(fichier_score);
}


void Tri_Score(UTILS* _utils, INGAME* _ingame)
{
	for (int i = 0; i < NB_HIGHSCORE; i++)
	{
		if (_ingame->score_courant.Score >= _ingame->list_highscores[i].score)
		{
			for (int j = NB_HIGHSCORE; j > i; j--)
			{
				_ingame->list_highscores[j].score = _ingame->list_highscores[j - 1].score;
				strcpy(_ingame->list_highscores[j].nom_save, _ingame->list_highscores[j - 1].nom_save);
			}
			_ingame->list_highscores[i].score = _ingame->score_courant.Score;
			strcpy(_ingame->list_highscores[i].nom_save, _ingame->score_courant.chare);
			i = NB_HIGHSCORE;
		}
	}
}
