/*  Fichier : puissance-4.h
    Auteur : Damien Lanusse
    Résumé : fichier d'entête du module puissance-4
    Date de dernière modification : 5 Janvier 2021
*/
#ifndef PUISSANCE_4_H
#define PUISSANCE_4_H

#include "game-tools.h"

// Création de la structure joueur
struct Joueur{
    string nom;
    Couleur couleur;
};

// Déclaration de constantes globales
const unsigned int NB_LIGNES = 6;   // Le nombre de lignes de la grille
const unsigned int NB_COLONNES = 7;   // Le nombre de colonnes de la grille
const string JEU = "Puissance 4";   // Le nom du jeu
const Couleur ROUGE = rouge;   // L'une des couleurs
const Couleur JAUNE = jaune;   // L'une des couleurs

// Déclaration des sous-programmes utilisés dans le main
void definirJoueurs (Joueur& joueurX, Joueur& joueurY, Couleur& pionJX, Couleur& pionJY);
// But : définir les joueurs 1 et 2

void joueurXJoue (Joueur joueurX, Couleur pionJX, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], bool& abandon, unsigned int& positionPion);
/* But : permettre au joueurX de jouer un pion de couleur pionJX dans la grille dans une colonne dont le remplissage est contenu dans rempliColonne
    Si le joueur décide d'abandonner, le booléen abandon passera a true et vainqueur r
*/

void verifVictoire (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire);
/* But : effectuer la vérification de la victoire du joueurX au pion de couleur pionJX
        Le joueurX joue dans la colonne d'indice positionPion - 1 dont on peut trouver le remplissage dans le tableau rempliColonne
        qui correspond au remplissage par colonne de la grille grille.
        S'il y a un vainqueur, la procédure renvoie le vainqueur et l'axe par lequel il ou elle a gagné. Victoire passe alors en true
*/

void afficherGrille (Couleur grille [][NB_COLONNES]);
// But: afficher la grille grille


#endif