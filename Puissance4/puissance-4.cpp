/*  Fichier : puissance-4.cpp
    Auteur : Damien Lanusse
    Résumé : corps du module puissance-4
    Date de dernière modification : 5 Janvier 2021
*/

/* 
- Déclaration des sous-programmes utilisés dans le module : Lignes 19 à 38
- Corps des sous-programmes du module : Lignes 39 à 201.
    - La procédure definirJoueurs se retrouve en ligne 41.
    - La procédure joueurJoue se retrouve en ligne 67.
    - La procédure verifVictoire se retrouve en ligne 144.
    - La procédure afficherGrille se retrouve en ligne 151.
- Corps des sous-programmes utilisés dans le module : Lignes 202 à 446.
*/

#include "puissance-4.h"

// Déclaration des sous-programmes utilisés dans le module
void verifVerticale (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire);
/* But : effectuer la vérification à la verticale de la victoire du joueurX au pion de couleur pionJX
        Le joueurX joue dans la colonne positionPion dont on peut trouver le remplissage dans le tableau rempliColonne
        qui correspond au remplissage par colonne de la grille grille.
        S'il y a un vainqueur, la procédure renvoie le vainqueur et l'axe par lequel il ou elle a gagné. Victoire passe alors en true
*/

void verifHorizontale (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire);
/* But : effectuer la vérification à l'horizontale de la victoire du joueurX au pion de couleur pionJX
        Le joueurX joue dans la colonne positionPion de la grille grille
        S'il y a un vainqueur, la procédure renvoie le vainqueur et l'axe par lequel il ou elle a gagné. Victoire passe alors en true
*/

void verifDiagonale (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire);
/* But : effectuer la vérification diagonale de la victoire du joueurX au pion de couleur pionJX
        Le joueurX joue dans la colonne positionPion de la grille grille
        S'il y a un vainqueur, la procédure renvoie le vainqueur et l'axe par lequel il ou elle a gagné. Victoire passe alors en true
*/

// -------------------------------------------------
// Corps des sous-programmes du module
void definirJoueurs (Joueur& joueurX, Joueur& joueurY, Couleur& pionJX, Couleur& pionJY)
{
    if (random(1,2) == 1)
    {
        joueurX = {"rouge", ROUGE};
        cout << "Le joueur 1 est le joueur ";
        afficherTexteEnCouleur(joueurX.nom, joueurX.couleur, true);
        joueurY = {"jaune", JAUNE};
        cout << "Le joueur 2 est le joueur ";
        afficherTexteEnCouleur(joueurY.nom, joueurY.couleur, true);
        pionJX = ROUGE;
        pionJY = JAUNE;
    }
    else
    {
        joueurX = {"jaune", JAUNE};
        cout << "Le joueur 1 est le joueur ";
        afficherTexteEnCouleur(joueurX.nom, joueurX.couleur, true);
        joueurY = {"rouge", ROUGE};
        cout << "Le joueur 2 est le joueur ";
        afficherTexteEnCouleur(joueurY.nom, joueurY.couleur, true);
        pionJX = JAUNE;
        pionJY = ROUGE;
    }
}

void joueurXJoue (Joueur joueurX, Couleur pionJX, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], bool& abandon, unsigned int& positionPion)
{
    // Variables
    bool erreur;   // S'il y a une erreur dans l'intervalle
    unsigned int nbElemColonne;   // On récupére le nombre d'éléments déjà présents dans la colonne où le joueur place son pion

    // Traitements
    // Affichage du joueur qui joue
    cout << "Le joueur ";
    afficherTexteEnCouleur(joueurX.nom, joueurX.couleur, false);
    cout << " a la main." << endl;

    // On effectue une saisie verif du numéro de la colonne où le joueur souhaite placer son pion
    while(true)
    {
        erreur = false; // Par défaut à chaque itération, il n'y a pas d'erreur
        // On effectue la saisie
        cout << "Veuillez saisir la colonne ou placer votre pion : " << endl;
        cin >> positionPion;

        // On vérifie le type de la saisie
        if (cin.fail())   // S'il y a une erreur dans le type de la saisie
        {
            cin.clear();   // On efface l'indicateur d'erreur
            cin.ignore();   // On ignore le fait que quelque chose a été entré en saisie
            cout << "Veuillez ne saisir qu'un entier entre 0 et 7 compris." << endl;
            erreur = true;
        }        

        // On vérifie maintenant l'intervalle demandé
        if (positionPion > NB_LIGNES + 1)
        {
            cout << "Veuillez rentrer un nombre entre 0 et 7 compris." << endl;
            erreur = true;
        }
        else
        {
            if (positionPion != 0)
            {
                // On vérifie s'il reste de la place dans la colonne
                if (rempliColonne[positionPion - 1] == NB_LIGNES)
                {
                    cout << "La colonne est pleine, veuillez en choisir une autre." << endl;
                    erreur = true;
                }
            }
        }

        // S'il n'y a pas d'erreur, on sort de la boucle
        if(!erreur)
        {
            break;
        }

    }

    // On vérifie si le joueur a décidé d'abandonner
    if (positionPion == 0)
    {
        abandon = true;
    }
    else 
    {
        // On place le pion dans la grille

        // On regarde le nombre d'éléments déjà dans la colonne
        nbElemColonne = rempliColonne[positionPion - 1];

        // On place le pion dans la colonne
        grille[NB_LIGNES - nbElemColonne - 1][positionPion - 1] = pionJX;

        // On met à jour le tableau du remplissage des colonnes
        rempliColonne[positionPion - 1] += 1;
    }

}

void verifVictoire (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire)
{
    verifVerticale(joueurX, pionJX, positionPion, grille, rempliColonne, vainqueur, axe, victoire);
    verifHorizontale(joueurX, pionJX, positionPion, grille, rempliColonne, vainqueur, axe, victoire);
    verifDiagonale (joueurX, pionJX, positionPion, grille, rempliColonne, vainqueur, axe, victoire);
}

void afficherGrille (Couleur grille [][NB_COLONNES])
{
    // VARIABLES
    unsigned int i; // Indice qui permettra d'afficher les numéros de colonne de la grille
    unsigned int indiceLignes; // L'indice d'affichage des lignes de la grille
    unsigned int indiceColonnes; // L'indice d'affichage des colonnes de la grille
    const unsigned int NOMBRE_AFFICHE = 0; // Le nombre que l'on affiche dans les cases

    // On efface ce qui se trouve dans l'interface de commande
    effacer();
    
    afficherTexteEnCouleur(JEU, vert, true);

    // On affiche les numéros de colonne
    for (i = 1; i <= NB_COLONNES; i ++)
    {
        cout << "  " << i << " ";
    }
    cout << endl;

    // On affiche les colonnes
    for (indiceLignes = 0; indiceLignes <= NB_LIGNES - 1; indiceLignes ++)
    {
        cout << "+---+---+---+---+---+---+---+" << endl;

        // On affiche le contenu d'une ligne
        for (indiceColonnes = 0; indiceColonnes <= NB_COLONNES - 1; indiceColonnes ++)
        {
            if (grille[indiceLignes][indiceColonnes] == ROUGE)
            {
                cout << "| ";
                afficherNombreEnCouleur(NOMBRE_AFFICHE, grille[indiceLignes][indiceColonnes], false);
                cout << " ";
            }
            else if (grille[indiceLignes][indiceColonnes] == JAUNE)
            {
                cout << "| ";
                afficherNombreEnCouleur(NOMBRE_AFFICHE, grille[indiceLignes][indiceColonnes], false);
                cout << " ";
            }
            else 
            {
                cout << "|   ";
            }
        }
        cout << "|" << endl;

    }
    cout << "+---+---+---+---+---+---+---+" << endl;
}

// -----------------------------------------------
// Corps des sous-programmes utilisés dans le module
/*
    - La procédure verifVerticale se retrouve en ligne 209.
    - La procédure verifHorizontale se retrouve en ligne 244.
    - La procédure verifDiagonale se retrouve en ligne 298.
*/
void verifVerticale (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire)
{
    // Initialisation
    unsigned int compteur = 1;   // Le compteur du nombre de pions alignés
    const string VERTICAL = "vertical";   // L'axe de victoire si elle se passe ici
    unsigned int indiceLigne = 6 - rempliColonne[positionPion - 1]; // L'indice de parcours de la colonne d'indice positionPion - 1

    // On compte le nombre de pion alignés à la verticale, qui sont donc dessous
    if (rempliColonne[positionPion - 1] >= 4)
    {
        while(true)
        {
            if (grille[indiceLigne][positionPion - 1] != pionJX)
            {
                break;
            }
            compteur += 1;
            if (indiceLigne == NB_LIGNES)
            {
                break;
            }
            indiceLigne +=1;
        }
    }

    // On attribue la victoie
    if(compteur >= 4)
    {
        vainqueur = joueurX;
        axe = VERTICAL;
        victoire = true;
    }
}


void verifHorizontale (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne[], Joueur& vainqueur, string& axe, bool& victoire)
{
    // Initialisation
    unsigned int compteur = 1;   // Le compteur du nombre de pions alignés
    const string HORIZONTAL = "horizontal";   // L'axe donné en cas de victoire
    unsigned int ligne = NB_LIGNES - rempliColonne[positionPion - 1];   // L'indice de la ligne où est posée le pion
    unsigned int positionActu;   // L'indice de la colonne dont on vérifie actuellement la couleur

    // On commence par vérifier à droite de la position du pion placé par le joueur
    if (positionPion < NB_COLONNES)
    {
        positionActu = positionPion;
        while(true)
        {
            if(grille[ligne][positionActu] != pionJX)
            {
                break;
            }
            compteur += 1;
            if(positionActu == NB_COLONNES - 1)
            {
                break;
            }
            positionActu += 1;
        }
    }
    // On continue en vérifiant à gauche de la position du pion placé par le joueur
    if (positionPion > 1)
    {
        positionActu = positionPion - 2;
        while(true)
        {
            if(grille[ligne][positionActu] != pionJX)
            {
                break;
            }
            compteur += 1;
            if(positionActu == 0)
            {
                break;
            }
            positionActu -= 1;
        }
    }

    // On attribue la victoire
    if(compteur >= 4)
    {
        vainqueur = joueurX;
        axe = HORIZONTAL;
        victoire = true;
    }
}

void verifDiagonale (Joueur joueurX, Couleur pionJX, unsigned int positionPion, Couleur grille [][NB_COLONNES], unsigned int rempliColonne [], Joueur& vainqueur, string& axe, bool& victoire)
{
    // Initialisation 
    unsigned int compteur = 1;   // Le compteur du nombre de pions alignés
    const string DIAGONAL = "diagonal";   // L'axe donné en cas de victoire
    unsigned int ligne;   // L'indice de la ligne où est posée le pion
    unsigned int positionActu;   // L'indice de la colonne dont on vérifie actuellement la couleur

    // On vérifie la diagonale partant d'en bas à gauche jusqu'en haut à droite
    if (positionPion < NB_COLONNES)
    {
        if (rempliColonne[positionPion - 1] < NB_LIGNES)
        {
            // On vérifie en haut à droite partant de la position du pion
            positionActu = positionPion;
            ligne = NB_LIGNES - rempliColonne[positionPion - 1] - 1;
            while(true)
            {
                if (grille[ligne][positionActu] != pionJX)
                {
                    break;
                }
                compteur += 1;

                if (positionActu == 6)
                {
                    break;
                }

                positionActu += 1;

                if (ligne == 0)
                {
                    break;
                }

                ligne -= 1;
            }
        }
    }

    if (positionPion > 1)
    {
        // On vérifie en bas à gauche en partant de la position du pion
        positionActu = positionPion - 2;
        ligne = NB_LIGNES - rempliColonne[positionPion - 1] + 1;
        while (true)
        {
            if (grille[ligne][positionActu] != pionJX)
            {
                break;
            }

            compteur += 1;

            if (positionActu == 0)
            {
                break;
            }

            positionActu -= 1;

            if (ligne == 5)
            {
                break;
            }

            ligne += 1;
        }
    }

    // On réinitialise le compteur s'il n'y a pas de victoire
    if (compteur < 4)
    {
        compteur = 1;
    }


    // On vérifie la diagonale partant d'en bas à droite jusqu'en haut à gauche
    if (positionPion > 1)
    {
        if (rempliColonne[positionPion - 1] < NB_LIGNES)
        {
            // On vérifie en haut à gauche partant de la position du pion
            positionActu = positionPion - 2;
            ligne = NB_LIGNES - rempliColonne[positionPion - 1] - 1;
            while(true)
            {
                if (grille[ligne][positionActu] != pionJX)
                {
                    break;
                }
                compteur += 1;

                if (positionActu == 0)
                {
                    break;
                }

                positionActu -= 1;

                if (ligne == 0)
                {
                    break;
                }

                ligne -= 1;
            }
        }
    }

    if (positionPion < NB_COLONNES)
    {
        // On vérifie en bas à droite en partant de la position du pion
        positionActu = positionPion;
        ligne = NB_LIGNES - rempliColonne[positionPion - 1] + 1;
        while (true)
        {
            if (grille[ligne][positionActu] != pionJX)
            {
                break;
            }

            compteur += 1;

            if (positionActu == 6)
            {
                break;
            }

            positionActu += 1;

            if (ligne == 5)
            {
                break;
            }

            ligne += 1;
        }
    
    }
    // On attribue la victoire
    if(compteur >= 4)
    {
        vainqueur = joueurX;
        axe = DIAGONAL;
        victoire = true;
    }
}