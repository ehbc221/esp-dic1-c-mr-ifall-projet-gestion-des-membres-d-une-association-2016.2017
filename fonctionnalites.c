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
/**********************************************************
*     Définition des fonctionnalités de l'application     *
**********************************************************/
// Afficher l'entete de notre application
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
// Se connecter à l'application
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
            if (strcmp(login_temporaire, login_saisi) == 0 && strcmp(mot_de_passe_temporaire, mot_de_passe_saisi) == 0)
                status_connection = SUCCES;
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
// Afficher le menu de l'application sélectionner une option
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
// Afficher l'entete de l'option choisie ( depuis le menu )
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
// Charger la liste des membres ( depuis le fichier fichier_membres.txt vers une liste chaînée liste_membres )
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
// Insérer un nouveau membre ( dans la liste des membres )
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
// Rechercher un membre ( dans la liste des membres )
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
// Modifier un membre ( de la liste des membres )
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
// Supprimer un membre ( de la liste des membres )
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
// Vérifier si une chaine de caractères est égale "quitter" ou non (prise en compte de la casse)
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
// Afficher un message après avoir choisi de quitter l'application
void afficherMessageSortie()
{
    printf("\nVous avez choisi de quitter l'application. Merci de l'avoir utilisee.\n");
}
// Enregistrer la liste des membres ( depuis la liste chaînée liste_membres vers le fichier fichier_membres.txt )
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
