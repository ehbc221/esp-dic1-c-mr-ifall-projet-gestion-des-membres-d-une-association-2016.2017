/****************************************
*     Déclaration des bibliotheques     *
****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
/************************************
*     Définition des constantes     *
************************************/
// Définition de la constante ERREUR
#define QUITTER -2
// Définition de la constante ERREUR
#define ERREUR -1
// Définition de la constante ECHEC
#define ECHEC 0
// Définition de la constante SUCCES
#define SUCCES 1
// Définition de la constante TAILLE_L (Petite taille)
#define TAILLE_L 15
// Définition de la constante TAILLE_XL (taille moyenne)
#define TAILLE_XL 25
// Définition de la constante TAILLE_XXL (taille grande)
#define TAILLE_XXL 50
/***********************************************************************
*     Déclaration des fonctions "supplémentaires" de l'application     *
***********************************************************************/
int estAlphaNumerique(char *chaine);
int estAlphabetique(char *chaine);
int estNumerique(char *chaine);
void enleverCaracteresRestants(char *chaine);
void enleverCaracteresSuperflus(void);
void clearScreen();
/***********************************************
* Définition des stuctures et listes chaînées  *
************************************************/
// Structure d'un utilisateur
typedef struct utilisateur
{
    char login_utilisateur[TAILLE_XL];
    char mot_de_passe_utilisateur[TAILLE_XL];
    struct utilisateur *suivant;
} utilisateur;
typedef utilisateur* liste_utilisateurs;
// Structure d'un membre
typedef struct membre
{
    char numero_membre[TAILLE_L];
    char nom_membre[TAILLE_XL];
    char prenoms_membre[TAILLE_XL];
    char adresse_membre[TAILLE_XXL];
    struct formation *formations_membre;
    struct membre *suivant;
} membre;
typedef membre* liste_membres;
// Structure d'une formation
typedef struct formation
{
    char code_formation[TAILLE_L];
    char intitule_formation[TAILLE_L];
    char annee_formation[TAILLE_L];
    struct formation *suivant;
} formation;
typedef formation* liste_formations;
/**************************************************
* Traitement élémentaire sur les listes chaînées. *
**************************************************/
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
/*******************************************************************
*     Déclaration des fonctions "principales" de l'application     *
*******************************************************************/
void afficherIntitule();
int connection();
int afficherEtChoisirOptionsMenu();
void afficherEnteteOptionChoisie(int numero_option);
liste_membres chargerListeMembres();
liste_membres insererNouveauMembre();
void rechercherMembre(liste_membres liste);
liste_membres modifierMembre(liste_membres liste);
liste_membres supprimerMembre(liste_membres liste);
int verifierSortie(char* chaine);
void afficherMessageSortie();
void enregistrerListeMembres(liste_membres liste);
/**************************
*     Fonction main()     *
**************************/
int main()
{
    int sortir_app=ECHEC, status_connection=ECHEC, status_recherche=ECHEC, choix_menu=0;
    char choix_sortie[TAILLE_L];
    // Nettoyer l'écran (effacer tout le contenu)
    clearScreen();
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
    liste = creerMembre();
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
/******************************************************************
*     Définition des fonctions "principales" de l'application     *
******************************************************************/
// Cette procedure affiche juste l'entete de notre application
void afficherIntitule()
{
    printf("\n /------------------------\\\n");
    printf("|     Projet Langage C     |");
    printf("\n \\------------------------/\n");
    printf("\nTitre : Gestion des membres d'une association.");
    printf("\n------\n");
    printf("\nGroupe :");
    printf("\n-------\n");
    printf("\t1) El Hadj Babacar Cissé\n");
    printf("\t2) El Hadj Babacar Cissé\n");
    printf("\t3) El Hadj Babacar Cissé\n");
    printf("\t4) El Hadj Babacar Cissé\n");
    printf("\n\nBienvenue dans l'application de gestion des membres d'une association. Connectez-vous pour commencer.\n\n");
}
// Cette fonction permet de se connecter
int connection()
{
    char login_saisi[TAILLE_XL], mot_de_passe_saisi[TAILLE_XL], ligne_utilisateur[TAILLE_XXL], delimiteur[2]=":", *cle, login_temporaire[TAILLE_XL], mot_de_passe_temporaire[TAILLE_XL];
    int status_connection=ECHEC, indice_cle=0, sortir_app=0;
    FILE* fichier_utilisateurs = NULL;
    // On ouvre le fichier contenant les utilisateurs (utilisateurs.txt)
    fichier_utilisateurs = fopen("fichiers/fichier_utilisateurs.txt", "r");
    // On teste si l'ouverture s'est bien déroulée. Dans le cas échéant, on peut continuer le traitement du fichier
    if (fichier_utilisateurs != NULL) {
        // Saisie des identifiants (login & du mot de passe) de connection
        printf("Saisissez votre login (ou 'quitter' pour sortir de l'application) : ");
        fgets(login_saisi, sizeof login_saisi, stdin);
        enleverCaracteresRestants(login_saisi);
        sortir_app = verifierSortie(login_saisi);
        if (sortir_app == QUITTER)
            return QUITTER;
        printf("Saisissez votre mot de passe : ");
        fgets(mot_de_passe_saisi, sizeof mot_de_passe_saisi, stdin);
        enleverCaracteresRestants(mot_de_passe_saisi);
        // Tant qu'on n'arrive pas à la fin du fichier et que l'on n'a pas trouvé un utilisateur correspondant aux identifiants 
        while(fgets(ligne_utilisateur, TAILLE_XXL, fichier_utilisateurs) != NULL && status_connection == ECHEC) {
            enleverCaracteresRestants(ligne_utilisateur);
            cle = strtok(ligne_utilisateur, delimiteur);
            indice_cle = 0;
            while(cle != NULL) {
                switch(indice_cle) {
                    case 0 :
                        strcpy(login_temporaire, cle);
                        break;
                    case 1 :
                        strcpy(mot_de_passe_temporaire, cle);
                        break;
                }
                indice_cle++;
                cle = strtok(NULL, delimiteur);
            }
            if (strcmp(login_temporaire, login_saisi) == 0 && strcmp(mot_de_passe_temporaire, mot_de_passe_saisi) == 0) {
                status_connection = SUCCES;
            }
        }
        if (status_connection == ERREUR)
            printf("\nUne erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
        else if (status_connection == ECHEC)
            printf("\nAucun utilisateur ne correspond aux identifiants saisis. Veuillez reessayer s'il vous plait.\n");
        else if (status_connection == SUCCES)
            printf("\nAuthentification reussie.\n");
    }
    // Si l'ouverture ne s'est pas bien déroulée, on retourne un code d'érreur (-1)
    else {
        status_connection = ERREUR;
        return status_connection;
    }
    // On ferme le fichier qui a été ouvert
    fclose(fichier_utilisateurs);
    // Retourner le status de connection
    return status_connection;
}
// Cette fonction permet d'afficher le menu de l'application et de sélectionner d'en sélectionner une option
int afficherEtChoisirOptionsMenu()
{
    char choix[10], choix_possibles[5][8]={"1", "2", "3", "4", "quitter"};
    int i, choix_valide=0;
    printf("\n /------------\\\n");
    printf("|     Menu     |");
    printf("\n \\------------/\n\n");
    printf("1) Inserer un nouveau membre.\n");
    printf("2) Rechercher un membre.\n");
    printf("3) Modifier un membre.\n");
    printf("4) Supprimer un membre.\n");
    // Demander à l'utilisateur de choisir un numéro tant son choix n'est pas valide
    do {
        printf("\nSaisissez le numero de votre choix pour continuer (ou tapez 'quitter' pour sortir de l'application) : ");
        fgets(choix, sizeof choix, stdin);
        enleverCaracteresRestants(choix);
        if (strcmp(choix, choix_possibles[0]) != 0 && strcmp(choix, choix_possibles[1]) != 0 && strcmp(choix, choix_possibles[2]) != 0 && strcmp(choix, choix_possibles[3]) != 0 && strcmp(choix, choix_possibles[4]) != 0)
            printf("\nChoix incorrect. Veuillez le ressaisir s'il vous plait.\n");
        else
            choix_valide = 1;
    } while (choix_valide == 0);
    // Si le choix est 1, 2, 3, ou 4 (par rapport au menu), retourner ce numéro
    for (i=0; i<4; i++) {
        if (strcmp(choix, choix_possibles[i]) == 0)
            return i+1;
    }
    // Sinon retourner -2 (QUITTER)
    return QUITTER;
}
// Cette procedure affiche l'entete de l'option choisie (depuis le menu)
void afficherEnteteOptionChoisie(int numero_option)
{
    switch(numero_option) {
        case 1 :
            printf("\n /------------------------------------\\\n");
            printf("|     1) Inserer un nouveau membre     |");
            printf("\n \\------------------------------------/\n\n");
            break;
        case 2 :
            printf("\n /-------------------------------\\\n");
            printf("|     2) Rechercher un membre     |");
            printf("\n \\-------------------------------/\n\n");
            break;
        case 3 :
            printf("\n /-----------------------------\\\n");
            printf("|     3) Modifier un membre     |");
            printf("\n \\-----------------------------/\n\n");
            break;
        case 4 :
            printf("\n /------------------------------\\\n");
            printf("|     4) Supprimer un membre     |");
            printf("\n \\------------------------------/\n\n");
            break;
    }
}
// Cette fonction permet de charger la liste des membres (dans une liste chaînée avec laquelle on travaillera plutard)
liste_membres chargerListeMembres()
{
    int status_chargement=ECHEC, indice_cle=0;
    char numero_temporaire[TAILLE_L], nom_temporaire[TAILLE_XL], prenoms_temporaire[TAILLE_XL], adresse_temporaire[TAILLE_XXL], ligne_membre[1000], delimiteur[2]=":", *cle;
    liste_membres temporaire;
    // Création d'un nouveau membre (vide)
    temporaire = creerMembre();
    // On déclare une variable qui nous permettra de travailler sur le fichier
    FILE* fichier_membres = NULL;
    // On ouvre le fichier contenant les membres (membres.txt) en mode lecture
    fichier_membres = fopen("fichiers/fichier_membres.txt", "r");
    // On teste si l'ouverture s'est bien déroulée. Dans le cas échéant, on peut continuer le traitement du fichier
    if (fichier_membres != NULL) {
        // Tant qu'on n'arrive pas à la fin du fichier
        while(fgets(ligne_membre, 1000, fichier_membres) != NULL) {
            enleverCaracteresRestants(ligne_membre);
            cle = strtok(ligne_membre, delimiteur);
            indice_cle = 0;
            while(cle != NULL) {
                switch(indice_cle) {
                    case 0 :
                        strcpy(numero_temporaire, cle);
                        break;
                    case 1 :
                        strcpy(nom_temporaire, cle);
                        break;
                    case 2 :
                        strcpy(prenoms_temporaire, cle);
                        break;
                    case 3 :
                        strcpy(adresse_temporaire, cle);
                        break;
                }
                indice_cle++;
                cle = strtok(NULL, delimiteur);
            }
            temporaire = insererEnQueueMembre(temporaire, numero_temporaire, nom_temporaire, prenoms_temporaire, adresse_temporaire, NULL);
        }
    }
    // Si l'ouverture ne s'est pas bien déroulée, on retourne NULL
    else
        return NULL;
    // On ferme le fichier qui a été ouvert
    fclose(fichier_membres);
    return temporaire;
}
// Cette fonction permet d'insérer un membre dans le fichier membres.txt
liste_membres insererNouveauMembre(liste_membres liste)
{
    char numero_membre[TAILLE_L], nom_membre[TAILLE_XL], prenoms_membre[TAILLE_XL], adresse_membre[TAILLE_XXL];
    int status_recherche=ECHEC, status_ajout=ECHEC, status_alpha_numerique=ECHEC, status_alphabetique=ECHEC, status_numerique=ECHEC, status_fermeture=ECHEC;
    liste_membres temporaire=liste;
    do {
        status_numerique=ECHEC;
        status_recherche=ECHEC;
        printf("Saisissez le numéro du membre a ajouter : ");
        fgets(numero_membre, sizeof numero_membre, stdin);
        enleverCaracteresRestants(numero_membre);
        status_numerique = estNumerique(numero_membre);
        if (status_numerique == ECHEC)
            printf("Le numéro du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n\n");
        else
            status_numerique = SUCCES;
        // On cherche s'il n'y a pas un membre avec le meme numero
        while(temporaire != NULL) {
            if (strcmp(numero_membre, temporaire->numero_membre) == 0) {
                status_recherche = SUCCES;
                break;
            }
            temporaire = temporaire->suivant;
        }
        if (status_recherche == SUCCES) {
            printf("\nCe numero de membre existe deja. Veuillez en retaper un autre.\n");
        }
    } while (status_numerique == ECHEC || status_recherche == SUCCES);
    temporaire = liste;
    while (status_alphabetique == ECHEC) {
        printf("Saisissez le nom du membre : ");
        fgets(nom_membre, sizeof nom_membre, stdin);
        enleverCaracteresRestants(nom_membre);
        status_alphabetique = estAlphabetique(nom_membre);
        if (status_alphabetique == ECHEC)
            printf("Le nom du membre ne doit contenir que des lettres alphabétiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
        else
            status_alphabetique = SUCCES;
    }
    status_alphabetique = ECHEC;
    while (status_alphabetique == ECHEC) {
        printf("Saisissez le prénom du membre : ");
        fgets(prenoms_membre, sizeof prenoms_membre, stdin);
        enleverCaracteresRestants(prenoms_membre);
        status_alphabetique = estAlphabetique(prenoms_membre);
        if (status_alphabetique == ECHEC)
            printf("Le prénom du membre ne doit contenir que des lettres alphabétiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
        else
            status_alphabetique = SUCCES;
    }
    while (status_alpha_numerique == ECHEC) {
        printf("Saisissez l'adresse du membre : ");
        fgets(adresse_membre, sizeof adresse_membre, stdin);
        enleverCaracteresRestants(adresse_membre);
        status_alpha_numerique = estAlphaNumerique(adresse_membre);
        if (status_alpha_numerique == ECHEC)
            printf("L'adresse du membre ne doit contenir que des lettres alphabétiques, des chiffres, et espaces. Veuillez le retaper s'il vous plait.\n\n");
        else
            status_alpha_numerique = SUCCES;
    }
    printf("\nVoici le membre que vous allez ajouter :\n");
    printf("\tNumero %s :\n", numero_membre);
    printf("\tNom : %s\n", nom_membre);
    printf("\tPrenom(s) : %s\n", prenoms_membre);
    printf("\tAdresse : %s\n\n", adresse_membre);
    // Ajouter dans la structure
    temporaire = insererEnQueueMembre(temporaire, numero_membre, nom_membre, prenoms_membre, adresse_membre, NULL);
    if (temporaire != NULL)
        printf("Membre ajoute avec succes.\n");
    else
        printf("\nEchec de l'ajout du membre.\n");
    return temporaire;
}
// Cette fonction permet de rechercher un membre
void rechercherMembre(liste_membres liste)
{
    if (liste != NULL) {
        char numero_membre[TAILLE_L];
        int status_numerique = ECHEC, status_recherche=ECHEC;
        while (status_numerique == ECHEC) {
            printf("Saisissez le numéro du membre a rechercher : ");
            fgets(numero_membre, sizeof numero_membre, stdin);
            enleverCaracteresRestants(numero_membre);
            status_numerique = estNumerique(numero_membre);
            if (status_numerique == ECHEC)
                printf("Le numéro du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n\n");
            else
                status_numerique = SUCCES;
        }
        liste_membres temporaire=liste;
        while(temporaire != NULL) {
            if (strcmp(numero_membre, temporaire->numero_membre) == 0) {
                status_recherche = SUCCES;
                break;
            }
            temporaire = temporaire->suivant;
        }
        if (status_recherche == SUCCES) {
            printf("\nVoici le membre que vous recherchiez :\n");
            printf("\tNumero %s :\n", temporaire->numero_membre);
            printf("\tNom : %s\n", temporaire->nom_membre);
            printf("\tPrenom(s) : %s\n", temporaire->prenoms_membre);
            printf("\tAdresse : %s\n", temporaire->adresse_membre);
        }
        else
            printf("\nCe membre n'existe pas.\n");
    }
    else
        printf("\nLa liste des membres est vide. Impossible de continuer.\n");
}
// Cette fonction permet de modifier un membre
liste_membres modifierMembre(liste_membres membres)
{
    if (membres == NULL)
        return ECHEC;
    char numero_membre[TAILLE_L];
    int status_recherche=ECHEC, status_alpha_numerique=ECHEC, status_alphabetique=ECHEC, status_numerique=ECHEC, status_fermeture=ECHEC;
    while (status_numerique == ECHEC) {
        printf("Saisissez le numéro du membre a modifier : ");
        fgets(numero_membre, sizeof numero_membre, stdin);
        enleverCaracteresRestants(numero_membre);
        status_numerique = estNumerique(numero_membre);
        if (status_numerique == ECHEC)
            printf("Le numéro du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n\n");
        else
            status_numerique = SUCCES;
    }
    liste_membres temporaire=membres;
    while(temporaire != NULL) {
        if (strcmp(numero_membre, temporaire->numero_membre) == 0) {
            status_recherche = SUCCES;
            break;
        }
        temporaire = temporaire->suivant;
    }
    if (status_recherche == SUCCES) {
        printf("\nVoici le membre que vous allez modifier :\n");
        printf("\tNumero %s :\n", temporaire->numero_membre);
        printf("\tNom : %s\n", temporaire->nom_membre);
        printf("\tPrenom(s) : %s\n", temporaire->prenoms_membre);
        printf("\tAdresse : %s\n\n", temporaire->adresse_membre);
        while (status_alphabetique == ECHEC) {
            printf("Saisissez le nom du membre : ");
            fgets(temporaire->nom_membre, sizeof temporaire->nom_membre, stdin);
            enleverCaracteresRestants(temporaire->nom_membre);
            status_alphabetique = estAlphabetique(temporaire->nom_membre);
            if (status_alphabetique == ECHEC)
                printf("Le nom du membre ne doit contenir que des lettres alphabétiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
            else
                status_alphabetique = SUCCES;
        }
        status_alphabetique = ECHEC;
        while (status_alphabetique == ECHEC) {
            printf("Saisissez le prénom du membre : ");
            fgets(temporaire->prenoms_membre, sizeof temporaire->prenoms_membre, stdin);
            enleverCaracteresRestants(temporaire->prenoms_membre);
            status_alphabetique = estAlphabetique(temporaire->prenoms_membre);
            if (status_alphabetique == ECHEC)
                printf("Le prénom du membre ne doit contenir que des lettres alphabétiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
            else
                status_alphabetique = SUCCES;
        }
        while (status_alpha_numerique == ECHEC) {
            printf("Saisissez l'adresse du membre : ");
            fgets(temporaire->adresse_membre, sizeof temporaire->adresse_membre, stdin);
            enleverCaracteresRestants(temporaire->adresse_membre);
            status_alpha_numerique = estAlphaNumerique(temporaire->adresse_membre);
            if (status_alpha_numerique == ECHEC)
                printf("L'adresse du membre ne doit contenir que des lettres alphabétiques, des chiffres, et espaces. Veuillez le retaper s'il vous plait.\n\n");
            else
                status_alpha_numerique = SUCCES;
        }
        printf("\nVoici les nouvelle informations du membre :\n");
        printf("\tNumero %s :\n", temporaire->numero_membre);
        printf("\tNom : %s\n", temporaire->nom_membre);
        printf("\tPrenom(s) : %s\n", temporaire->prenoms_membre);
        printf("\tAdresse : %s\n\n", temporaire->adresse_membre);
        printf("Membre modifie avec succes.\n");
    }
    else
        printf("\nCe membre n'existe pas.\n");
    return membres;
}
// Cette fonction permet de supprimer un membre
liste_membres supprimerMembre(liste_membres liste)
{
    if (liste == NULL)
        return ECHEC;
    char numero_membre[TAILLE_L];
    int status_numerique = ECHEC, status_recherche=ECHEC;
    while (status_numerique == ECHEC) {
        printf("Saisissez le numéro du membre a supprimer : ");
        fgets(numero_membre, sizeof numero_membre, stdin);
        enleverCaracteresRestants(numero_membre);
        status_numerique = estNumerique(numero_membre);
        if (status_numerique == ECHEC)
            printf("Le numéro du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n\n");
        else
            status_numerique = SUCCES;
    }
    liste_membres temporaire=liste;
    liste_membres avant_dernier=liste;
    // On parcours tous les éléments de la liste
    while(temporaire != NULL) {
        // Si c'est le premier element de la liste qui coincide => algo supprimer premier
        if (temporaire == liste && strcmp(numero_membre, temporaire->numero_membre) == 0) {
            printf("\nVoici le membre que vous allez supprimer :\n");
            printf("\tNumero %s :\n", temporaire->numero_membre);
            printf("\tNom : %s\n", temporaire->nom_membre);
            printf("\tPrenom(s) : %s\n", temporaire->prenoms_membre);
            printf("\tAdresse : %s\n", temporaire->adresse_membre);
            status_recherche = SUCCES;
            liste = temporaire->suivant;
            free(temporaire);
            break;
        }
        // Sinon si c'est un autre membre qui coincide => algo supprimer membre quelconque
        else if (strcmp(numero_membre, temporaire->numero_membre) == 0) {
            printf("\nVoici le membre que vous allez supprimer :\n");
            printf("\tNumero %s :\n", temporaire->numero_membre);
            printf("\tNom : %s\n", temporaire->nom_membre);
            printf("\tPrenom(s) : %s\n", temporaire->prenoms_membre);
            printf("\tAdresse : %s\n", temporaire->adresse_membre);
            status_recherche = SUCCES;
            avant_dernier->suivant = temporaire->suivant;
            free(temporaire);
            break;
        }
        // Sinon (les membres ne coincident pas)
        else
            avant_dernier = temporaire;
            temporaire = temporaire->suivant;
    }
    if (status_recherche == SUCCES)
        printf("\nMembre supprime avec succes.\n");
    else
        printf("\nCe membre n'existe pas.\n");
    return liste;
}
// Cette fonction permet d'enregistrer la liste des membres dans un fichier
void enregistrerListeMembres(liste_membres liste) {
    // On déclare une variable qui nous permettra de travailler sur le fichier
    FILE* fichier_membres = NULL;
    // On ouvre le fichier contenant les membres (membres.txt) en mode lecture
    fichier_membres = fopen("fichiers/fichier_membres.txt", "w");
    // On teste si l'ouverture s'est bien déroulée. Dans le cas échéant, on peut continuer le traitement du fichier
    if (fichier_membres != NULL) {
        liste_membres temporaire=liste;
        // Tant qu'on n'arrive pas à la fin de la liste
        while(temporaire != NULL) {
            fprintf(fichier_membres, "%s:%s:%s:%s\n", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre);
            temporaire = temporaire->suivant;
        }
        printf("\nEnregistrement des membres dans le fichier avec succes.\n");
    }
    // Si l'ouverture ne s'est pas bien déroulée
    else
        printf("Une erreur s'est produite lors de l'ouverture du fichier\n");;
    // On ferme le fichier qui a été ouvert
    fclose(fichier_membres);
}
/**********************************************************************
*     Définition des fonctions "supplémentaires" de l'application     *
**********************************************************************/
// Cette fonction permet de vérifier si une chaine de caractères est alphanumérique ou non
int estAlphaNumerique(char *chaine)
{
    int i, status_alpha_numerique=SUCCES, taille_chaine = strlen(chaine);
    // Pour chaque caractere de la chaine
    for (i=0; i<taille_chaine; i++) {
        // Si ce n'est ni une lettre alphabétique, ni un chiffre, ni un espace, retourner 0
        if (!isdigit(chaine[i]) && !isalpha(chaine[i]) && !isspace(chaine[i])) {
            status_alpha_numerique = ECHEC;
            return status_alpha_numerique;
        }
    }
    // Sinon, retourner 1
    return status_alpha_numerique;
}
// Cette fonction permet de vérifier si une chaine de caractères est alphabétique ou non
int estAlphabetique(char *chaine)
{
    int i, status_alphabetique=SUCCES, taille_chaine = strlen(chaine);
    // Pour chaque caractere de la chaine
    for (i=0; i<taille_chaine; i++) {
        // Si ce n'est pas une lettre alphabétique, retourner 0
        if (!isalpha(chaine[i]) && !isspace(chaine[i])) {
            status_alphabetique = ECHEC;
            return status_alphabetique;
        }
    }
    // Sinon, retourner 1
    return status_alphabetique;
}
// Cette fonction permet de vérifier si une chaine de caractères est numérique ou non
int estNumerique(char *chaine)
{
    int i, status_numerique=SUCCES, taille_chaine = strlen(chaine);
    // Pour chaque caractere de la chaine
    for (i=0; i<taille_chaine; i++) {
        // Si ce n'est pas un chiffre, retourner 0
        if (!isdigit(chaine[i])) {
            status_numerique = ECHEC;
            return status_numerique;
        }
    }
    // Sinon, retourner 1
    return status_numerique;
}
// Cette procedure permet d'enlever restants après l'le retour à la ligne à la fin d'une chaine de caractères
void enleverCaracteresRestants(char *chaine)
{
    // On cherche le caractère de retour à la ligne "\n"
    char *p = strchr(chaine, '\n');
    // Si on le trouve, on annule sa valeur
    if (p)
        *p = '\0';
    // Sinon : cas où la dernière saisie ne s'est pas déroulée correctement (ou on a dépassé le nombre de caractères max spécifié en deuxième argument) alors la seconde saisie va contenir les caractères qui n'ont pas été lus
    else
        enleverCaracteresSuperflus();
}
// Cette procedure permet de lire tous les caractères restants dans le buffer. Elle sera utilisée après les "fgets" dans la fonction "enleverCaracteresRestants" pour vider le buffer
void enleverCaracteresSuperflus(void)
{
    int c;
    // Lire tous les caractères restant dans le buffer le buffer s'il reste des caractères non lus
    while ((c = getchar()) != '\n' && c != EOF) {}
}
// Cette fonction permet de vérifier si une chaine de caractères est égale "quitter" ou non (prise en compte de la casse)
int verifierSortie(char* chaine)
{
    char quitter[8]="quitter";
    int i, taille_chaine=strlen(chaine);
    for (i=0; i<taille_chaine; i++) {
        chaine[i] = tolower(chaine[i]);
    }
    if (strcmp(chaine, quitter) == 0)
        return QUITTER;
    else
        return ECHEC;
}
// Cette procedure permet d'afficher un message après avoir quitter l'application
void afficherMessageSortie()
{
    printf("\nVous avez choisi de quitter l'application. Merci de l'avoir utilisee.\n");
}
// Cette fonction permet de nettoyer l'écran (effacer tout son contenu)
void clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
