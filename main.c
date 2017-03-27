/*************************************************
*     Déclaration des bibliothèques requises     *
*************************************************/
// Fonctions des bibliothèques standard + Constantes
#include "entetes.h"
// Stuctures + Liste chaînées + Fonctions relatives à ces dernières
#include "membres.h"
// Fonctionnalités relatives au cœur de l'application elle-même
#include "fonctionnalites.h"
// Fonctions supplémentaires de l'application
#include "fonctions_supplementaires.h"
/***********************************************************************
*     Définition de la fonction principale main() de l'application     *
***********************************************************************/
int main()
{
    int sortir_app=ECHEC, status_connection=ECHEC, status_recherche=ECHEC, choix_menu=0;
    char choix_sortie[TAILLE_L];
    // Nettoyer l'écran (effacer tout le contenu)
    clearScreen();
    /*
        TESTS
    */
        // MEMBRES
        liste_membres test_lm = creerListeMembre();
        int j;
        for (j=0; j<3; j++) {
            // FORMATIONS
            liste_formations test_lf = creerListeFormation();
            int i;
            for (i=0; i<3; i++) {
                test_lf = insererEnQueueFormation(test_lf, "51SF", "SGBD", "2016/2017");
            }
            test_lm = insererEnQueueMembre(test_lm, "1", "CISSE", "EL HADJ BABACAR", "MARISTE", test_lf);
        }
        afficherListeMembres(test_lm);
    /*
        FIN TESTS
    */
    // On affiche l'entete (accueil) de l'application
    afficherIntitule();
    // On demande à l'utilisareur de se connecter tant qu'il n'a pas choisi de quitter, ou qu'il ne s'est pas connecté
    do {
        // On demande à l'utilisateur de se connecter
        status_connection = connection();
        /*
            S'il a choisi de quitter l'application, on lui affiche un message de sortie puis on arrete le programme
            Sinon, on continue
        */
        if (status_connection == QUITTER) {
            afficherMessageSortie();
            return SUCCES;
        }
    } while (status_connection != SUCCES);
    // On déclare et initialise la liste des membres
    liste_membres liste;
    liste = creerListeMembre();
    // On charge les membres depuis le fichier vers une liste chaînée
    liste = chargerListeMembres();
    do {
        // Nettoyer l'écran (effacer tout le contenu)
        clearScreen();
        afficherListeMembres(liste);
        // Une fois l'utilisateur connecté, on lui affiche le menu de l'application et lui demande de choisir une option
        choix_menu = afficherEtChoisirOptionsMenu();
        // S'il a choisi de quitter l'application, on lui affiche un message de sortie puis on arrete le programme. Sinon, on continue
        if (choix_menu == QUITTER) {
            sortir_app = SUCCES;
            afficherMessageSortie();
            afficherListeMembres(liste);
            enregistrerListeMembres(liste);
            return sortir_app;
        }
        // Nettoyer l'écran (effacer tout le contenu)
        clearScreen();
        afficherListeMembres(liste);
        // On affiche l'entete de l'option choisie
        afficherEnteteOptionChoisie(choix_menu);
        switch (choix_menu) {
            case 1 :
                // Ajouter un nouveau membre à la liste
                liste = insererNouveauMembre(liste);
                break;
            case 2 :
                // Rechercher un membre
                rechercherMembre(liste);
                break;
            case 3 :
                // Modifier un membre
                liste = modifierMembre(liste);
                break;
            case 4 :
                // Supprimer un membre
                liste = supprimerMembre(liste);
                break;
            default :
                sortir_app = SUCCES;
                afficherMessageSortie();
                afficherListeMembres(liste);
                enregistrerListeMembres(liste);
                return sortir_app;
        }
        printf("\nTapez 'quitter' pour sortir de l'application, ou toute autre phrase pour revenir au menu : ");
        fgets(choix_sortie, sizeof choix_sortie, stdin);
        enleverCaracteresRestants(choix_sortie);
        sortir_app = verifierSortie(choix_sortie);
        if (sortir_app == QUITTER) {
            sortir_app = SUCCES;
            afficherMessageSortie();
            afficherListeMembres(liste);
            enregistrerListeMembres(liste);
            return sortir_app;
        }
    } while (sortir_app == ECHEC); // Tant que l'utilisateur n'a pas choisi de quitter
    return SUCCES;
}
