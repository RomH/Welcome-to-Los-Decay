#pragma once
#include "stdafx.h"

void LectureFichier(char* _Path, sfSprite** _tab_Sprite, ANIM_DEF* _TypeAnim, INGAME* _Ingame, UTILS* _Utils); //Fonction permettant de lire un fichier d'animation

int ChercheSequence(char* _nomAnim, ANIM_DEF* _Type_Anim, INGAME* _Ingame); //On recherche la séquence qui sera lue pour démarrer l'animation

void LectureFichier_Pack(INGAME* _Ingame, UTILS* _Utils); //Regroupe toutes les fonctions de lecture de fichier

void ControlAnimEvenementiel(INGAME* _Ingame, UTILS* _Utils); //Influence l'animation en fonction des touches pressées

void UpdateAnim(INGAME* _Ingame, UTILS* _Utils); //Update des Animations

void AffichageAnim(INGAME* _Ingame, UTILS* _Utils); // Affichage des animations
