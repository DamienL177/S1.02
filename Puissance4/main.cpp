/*  Programme : PuissanceQuatre
    But : Jouer au jeu du Puissance 4
    Auteur : Damien Lanusse, Thomas Cattrossi-Dartiguelongue
    Date de dernière modification : 05 Janvier 2022
    Remarques : code conforme aux spécifications données en cours
*/

#include "puissance-4.h"


int main(void)
{
    // Initialisation de la partie
    Couleur grille [NB_LIGNES][NB_COLONNES];   // La grille dans laquelle on placera des couleurs servant de pions
    const unsigned int NB_MAX_MANCHES = 21;   // Le nombre de manches maximum du jeu
    unsigned int numManche = 0;  // Le compteur de la manche actuelle
    bool abandon = false;   // L'indicateur de si un joueur a, ou non, abandonné la partie
    unsigned int rempliColonnes [NB_COLONNES] = {0,0,0,0,0,0,0};   // Le tableau contenant le remplissage des colonnes
    Joueur vainqueur;   // Le joueur qui est vainqueur
    const string EGALITE = "egalite";   // Une variable qui sert en cas d'égalité
    string axe;   // L'axe avec lequel le joueur a gagné
    Joueur joueur1;   // Le joueur 1
    Joueur joueur2;   // Le joueur 2
    Couleur pionJ1;   // Le pion du joueur 1
    Couleur pionJ2;   // Le pion du joueur 2
    unsigned int positionPion;   // La dernière position où a été joué un pion
    bool victoire = false;   // Si, oui ou non, une victoire a été trouvée dans les vérifs


    // On prépare le tableau
    afficherGrille(grille);

    // Initialisation des joueurs
    definirJoueurs(joueur1, joueur2, pionJ1, pionJ2);

    // Jouer la partie
    // Jouer chaque manche une par une
    while (true)
    {
        // Mise à jour du numéro de la manche
        numManche += 1;

        // Les joueurs jouent la manche
        // Le joueur 1 joue
        joueurXJoue(joueur1, pionJ1, grille, rempliColonnes, abandon, positionPion);

        // On affiche la grille actuelle
        afficherGrille(grille);

        // On vérifie les victoires
        if (! abandon)
        {
            verifVictoire(joueur1, pionJ1, positionPion, grille, rempliColonnes, vainqueur, axe, victoire);
        }
        else 
        {
            vainqueur = joueur2;
            victoire = true;
        }

        if (victoire)
        {
            break;
        }

        // Le joueur 2 joue
        joueurXJoue(joueur2, pionJ2, grille, rempliColonnes, abandon, positionPion);

        // On affiche la grille actuelle
        afficherGrille(grille);

        // On vérifie les victoires
        if (! abandon)
        {
            verifVictoire (joueur2, pionJ2, positionPion, grille, rempliColonnes, vainqueur, axe, victoire);
        }
        else 
        {
            vainqueur = joueur1;
            victoire = true;
        }

        // On vérifie si l'on sort de la boucle dû à une victoire
        if (victoire)
        {
            break;
        }

        // Vérification du nombre de manches jouées
        if (numManche == NB_MAX_MANCHES)
        {
            vainqueur = {"egalite", bleu};
            break;
        }
    }
    


    // Finaliser la partie
    if (abandon == true)
    {
        cout << "Le vainqueur est ";
        afficherTexteEnCouleur(vainqueur.nom, vainqueur.couleur, false);
        cout << " par abandon de son adversaire." << endl;
    }
    else
    {
        if (vainqueur.nom == EGALITE)
        {
            cout << "La grille est pleine, il y a egalite." << endl;
        }
        else
        {
            cout << "Le vainqueur est le joueur ";
            afficherTexteEnCouleur(vainqueur.nom, vainqueur.couleur, false);
            cout << " avec des pions alignes sur un axe " << axe << endl;
        }
    }


    return 0;
}