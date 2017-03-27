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
// Créer une liste de membres vide
liste_membres creerListeMembre()
{
    liste_membres nouveau_membre = NULL;
    return nouveau_membre;
}
// Ajouter un membre en fin de liste
liste_membres insererEnQueueMembre(liste_membres ancienne_liste_membres, char *numero_membre, char *nom_membre, char *prenoms_membre, char *adresse_membre, liste_formations formations_membre)
{
    liste_membres nouveau_membre = malloc(sizeof(membre));
    strcpy(nouveau_membre->numero_membre, numero_membre);
    strcpy(nouveau_membre->nom_membre, nom_membre);
    strcpy(nouveau_membre->prenoms_membre, prenoms_membre);
    strcpy(nouveau_membre->adresse_membre, adresse_membre);
    if (formations_membre == NULL) {
        nouveau_membre->formations_membre = NULL;
    }
    else {
        while (formations_membre != NULL) {
            nouveau_membre->formations_membre = insererEnQueueFormation(nouveau_membre->formations_membre, formations_membre->code_formation, formations_membre->intitule_formation, formations_membre->annee_formation);
            formations_membre = formations_membre->suivant;
        }
    }
    nouveau_membre->suivant = NULL;
    if (ancienne_liste_membres == NULL) {
        return nouveau_membre;
    }
    liste_membres copie_ancienne_liste_membres = ancienne_liste_membres;
    while(copie_ancienne_liste_membres->suivant != NULL) {
        copie_ancienne_liste_membres = copie_ancienne_liste_membres->suivant;
    }
    copie_ancienne_liste_membres->suivant = nouveau_membre;
    return ancienne_liste_membres;
}
// Rechercher un membre dans une liste
int rechercherUnMembre(liste_membres liste, char *numero_membre)
{
    int status_recherche=ECHEC;
    liste_membres liste_membres_temporaire=liste;
    while(liste_membres_temporaire != NULL) {
        if (strcmp(numero_membre, liste_membres_temporaire->numero_membre) == 0) {
            return status_recherche = SUCCES;
        }
        else {
            liste_membres_temporaire = liste_membres_temporaire->suivant;
        }
    }
    return status_recherche=ECHEC;
}
// Afficher un membre
void afficherUnMembre(liste_membres liste, char *numero_membre)
{
    liste_membres liste_membres_temporaire=liste;
    while(liste_membres_temporaire != NULL) {
        if (strcmp(numero_membre, liste_membres_temporaire->numero_membre) == 0) {
            printf("\nMembre :\n\n");
            printf("\tNumero %s :\n", liste_membres_temporaire->numero_membre);
            printf("\tNom : %s\n", liste_membres_temporaire->nom_membre);
            printf("\tPrenom(s) : %s\n", liste_membres_temporaire->prenoms_membre);
            printf("\tAdresse : %s\n", liste_membres_temporaire->adresse_membre);
            printf("\n\tFormations : \n\n");
            liste_formations liste_formations_temporaire = liste_membres_temporaire->formations_membre;
            if (liste_formations_temporaire == NULL) {
                printf("\t\tAucune formation a afficher.\n");
            }
            else {
                while (liste_formations_temporaire != NULL) {
                    printf("\t\tCode : %s\n", liste_formations_temporaire->code_formation);
                    printf("\t\tIntitule : %s\n", liste_formations_temporaire->intitule_formation);
                    printf("\t\tAnnee : %s\n\n", liste_formations_temporaire->annee_formation);
                    liste_formations_temporaire = liste_formations_temporaire->suivant;
                }
            }
            break;
        }
        else {
            liste_membres_temporaire = liste_membres_temporaire->suivant;
        }
    }
}
// Supprimer un membre
int supprimerUnMembre(liste_membres liste, char *numero_membre)
{
    int status_suppression=ECHEC;
    liste_membres temporaire=liste;
    liste_membres avant_dernier=liste;
    // On parcours tous les éléments de la liste
    while(temporaire != NULL && status_suppression == ECHEC) {
        // Si on trouve le membre (celui avec le meme numero)
        if (strcmp(numero_membre, temporaire->numero_membre) == 0) {
            // Si c'est le premier element de la liste qui coincide => algo supprimer premier
            if (temporaire == liste && strcmp(numero_membre, temporaire->numero_membre) == 0) {
                liste = temporaire->suivant;
                free(temporaire);
                return status_suppression = SUCCES;
            }
            // Sinon si c'est un autre membre qui coincide => algo supprimer membre quelconque
            else if (strcmp(numero_membre, temporaire->numero_membre) == 0) {
                avant_dernier->suivant = temporaire->suivant;
                free(temporaire);
                return status_suppression = SUCCES;
            }
        }
        // Sinon (si les membres ne coincident pas)
        else {
            avant_dernier = temporaire;
            temporaire = temporaire->suivant;
        }
    }
    return status_suppression = ECHEC;
}
// Afficher la liste des membres
void afficherListeMembres(liste_membres liste)
{
    liste_membres temporaire = liste;
    if(temporaire != NULL) {
        printf("\n");
        while(temporaire->suivant != NULL) {
            printf("%s:%s:%s:%s", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre);
            afficherListeFormations(temporaire->formations_membre);
            printf("\n");
            temporaire = temporaire->suivant;
        }
        printf("%s:%s:%s:%s", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre);
        afficherListeFormations(temporaire->formations_membre);
        printf("\n");
    }
    else {
        printf("\nCette liste est vide.\n");
    }
}
// Créer une liste de formations vide
liste_formations creerListeFormation()
{
    liste_formations nouvelle_formation = NULL;
    return nouvelle_formation;
}
// Ajouter un membre en fin de liste
liste_formations insererEnQueueFormation(liste_formations ancienne_liste_formations, char *code_formation, char *intitule_formation, char *annee_formation)
{
    liste_formations nouvelle_formation = malloc(sizeof(formation));
    strcpy(nouvelle_formation->code_formation, code_formation);
    strcpy(nouvelle_formation->intitule_formation, intitule_formation);
    strcpy(nouvelle_formation->annee_formation, annee_formation);
    nouvelle_formation->suivant = NULL;
    if (ancienne_liste_formations == NULL) {
        return nouvelle_formation;
    }
    liste_formations copie_ancienne_liste_formations = ancienne_liste_formations;
    while(copie_ancienne_liste_formations->suivant != NULL) {
        copie_ancienne_liste_formations = copie_ancienne_liste_formations->suivant;
    }
    copie_ancienne_liste_formations->suivant = nouvelle_formation;
    return ancienne_liste_formations;
}
// Afficher la liste des formations
void afficherListeFormations(liste_formations liste)
{
    liste_formations temporaire = liste;
    if(temporaire != NULL) {
        while(temporaire->suivant != NULL) {
            printf(":%s:%s:%s", temporaire->code_formation, temporaire->intitule_formation, temporaire->annee_formation);
            temporaire = temporaire->suivant;
        }
        printf(":%s:%s:%s", temporaire->code_formation, temporaire->intitule_formation, temporaire->annee_formation);
    }
}
