/*************************************************
*     Déclaration des bibliothèques requises     *
*************************************************/
// Fonctions des bibliothèques standard + Constantes
#include "entetes.h"
// Stuctures + Liste chaînées + Fonctions relatives à ces dernières
#include "membres.h"
/*******************************************************************
* Définition des fonctions relatives aux membres et formations     *
*******************************************************************/
// Créer une liste d'utilisateurs vide
liste_utilisateurs creerUtilisateur()
{
    liste_utilisateurs nouvel_utilisateur = NULL;
    return nouvel_utilisateur;
}
// Ajouter un utilisateur en fin de liste
liste_utilisateurs insererEnQueueUtilisateur(liste_utilisateurs liste, char* login_utilisateur, char* mot_de_passe_utilisateur)
{
    liste_utilisateurs nouvel_utilisateur = malloc(sizeof(utilisateur));
    strcpy(nouvel_utilisateur->login_utilisateur, login_utilisateur);
    strcpy(nouvel_utilisateur->mot_de_passe_utilisateur, mot_de_passe_utilisateur);
    nouvel_utilisateur->suivant = NULL;
    if (liste == NULL)
        return nouvel_utilisateur;
    utilisateur* temporaire = liste;
    while(temporaire->suivant != NULL)
        temporaire = temporaire->suivant;
    temporaire->suivant = nouvel_utilisateur;
    return liste;
}
// Créer une liste de membres vide
liste_membres creerMembre()
{
    liste_membres nouveau_membre = NULL;
    return nouveau_membre;
}
// Ajouter un membre en fin de liste
liste_membres insererEnQueueMembre(liste_membres liste, char numero_membre[TAILLE_L], char nom_membre[TAILLE_XL], char prenoms_membre[TAILLE_XL], char adresse_membre[TAILLE_XXL], struct formation *formations_membre)
{
    liste_membres nouveau_membre = malloc(sizeof(membre));
    strcpy(nouveau_membre->numero_membre, numero_membre);
    strcpy(nouveau_membre->nom_membre, nom_membre);
    strcpy(nouveau_membre->prenoms_membre, prenoms_membre);
    strcpy(nouveau_membre->adresse_membre, adresse_membre);
    nouveau_membre->formations_membre = NULL;
    nouveau_membre->suivant = NULL;
    if (liste == NULL)
        return nouveau_membre;
    liste_membres temporaire = liste;
    while(temporaire->suivant != NULL)
        temporaire = temporaire->suivant;
    temporaire->suivant = nouveau_membre;
    return liste;
}
// Afficher la liste des membres
void afficherListeMembres(liste_membres liste)
{
    liste_membres temporaire = liste;
    if(temporaire != NULL) {
        printf("\n");
        while(temporaire->suivant != NULL) {
            printf("%s:%s:%s:%s\n", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre);
            temporaire = temporaire->suivant;
        }
        printf("%s:%s:%s:%s\n", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre);
    }
    else
        printf("\nCette liste est vide.\n");
}
// Créer une liste de formations vide
liste_formations creerFormation()
{
    liste_formations nouvelle_formation = NULL;
    return nouvelle_formation;
}
