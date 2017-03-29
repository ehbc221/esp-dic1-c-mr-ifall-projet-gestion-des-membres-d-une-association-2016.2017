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
    printf("\t1) TEST test\n");
    printf("\t2) TEST test\n");
    printf("\t3) TEST test\n");
    printf("\t4) TEST test\n");
    printf("\n\nBienvenue dans l'application de gestion des membres d'une association. Connectez-vous pour commencer.\n\n");
}
// Se connecter à l'application
int connection()
{
    char login_saisi[TAILLE_XL], mot_de_passe_saisi[TAILLE_XL], ligne_utilisateur[TAILLE_MAX_LIGNE_FICHIER_MEMBRES], delimiteur[2]=":", *cle, login_temporaire[TAILLE_XL], mot_de_passe_temporaire[TAILLE_XL];
    int test=ECHEC, indice_cle=0, sortir_app=ECHEC;
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
        if (sortir_app == QUITTER) {
            return QUITTER;
        }
        printf("Saisissez votre mot de passe : ");
        fgets(mot_de_passe_saisi, sizeof mot_de_passe_saisi, stdin);
        enleverCaracteresRestants(mot_de_passe_saisi);
        // Tant qu'on n'arrive pas à la fin du fichier et que l'on n'a pas trouvé un utilisateur correspondant aux identifiants 
        while(fgets(ligne_utilisateur, TAILLE_XXL, fichier_utilisateurs) != NULL && test == ECHEC) {
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
                test = SUCCES;
            }
        }
        if (test == ERREUR) {
            printf("\nUne erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
        }
        else if (test == ECHEC) {
            printf("\nAucun utilisateur ne correspond aux identifiants saisis. Veuillez reessayer s'il vous plait.\n");
        }
        else if (test == SUCCES) {
            printf("\nAuthentification reussie.\n");
        }
    }
    // Si l'ouverture ne s'est pas bien déroulée, on retourne un code d'érreur (-1)
    else {
        return test = ERREUR;
    }
    fclose(fichier_utilisateurs);
    return test;
}
// Afficher le menu de l'application sélectionner une option
int afficherEtChoisirOptionsMenu()
{
    char choix[10], choix_possibles[5][8]={"1", "2", "3", "4", "quitter"};
    int i, test=ECHEC;
    printf("\n /------------\\\n");
    printf("|     Menu     |");
    printf("\n \\------------/\n\n");
    printf("1) Inserer un nouveau membre.\n");
    printf("2) Rechercher un membre.\n");
    printf("3) Modifier un membre.\n");
    printf("4) Supprimer un membre.\n");
    // Demander à l'utilisateur de choisir un numero tant son choix n'est pas valide
    while (test == ECHEC) {
        printf("\nSaisissez le numero de votre choix pour continuer (ou tapez 'quitter' pour sortir de l'application) : ");
        fgets(choix, sizeof choix, stdin);
        enleverCaracteresRestants(choix);
        if (strcmp(choix, choix_possibles[0]) != 0 && strcmp(choix, choix_possibles[1]) != 0 && strcmp(choix, choix_possibles[2]) != 0 && strcmp(choix, choix_possibles[3]) != 0 && strcmp(choix, choix_possibles[4]) != 0) {
            printf("\nChoix incorrect. Veuillez le ressaisir s'il vous plait.\n");
        }
        else {
            test = SUCCES;
        }
    }
    // Si le choix est 1, 2, 3, ou 4 (par rapport au menu), retourner ce numero
    for (i=0; i<4; i++) {
        if (strcmp(choix, choix_possibles[i]) == 0) {
            return i+1;
        }
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
    int indice_cle=0;
    char numero_membre[TAILLE_L], nom_membre[TAILLE_XL], prenoms_membre[TAILLE_XL], adresse_membre[TAILLE_XXL], code_formation[TAILLE_L], intitule_formation[TAILLE_L], annee_formation[TAILLE_L], ligne_membre[TAILLE_MAX_LIGNE_FICHIER_MEMBRES], delimiteur[2]=":", *cle;
    // Création d'une nouvelle liste de membres
    liste_membres liste_membres_temporaire = creerListeMembre();
    // Création d'une nouvelle liste de formations
    liste_formations liste_formations_temporaire = creerListeFormation();
    // On déclare une variable qui nous permettra de travailler sur le fichier
    FILE* fichier_membres = NULL;
    // On ouvre le fichier contenant les membres (membres.txt) en mode lecture
    fichier_membres = fopen("fichiers/fichier_membres.txt", "r");
    // On teste si l'ouverture s'est bien déroulée. Dans le cas échéant, on peut continuer le traitement du fichier
    if (fichier_membres != NULL) {
        // Tant qu'on n'arrive pas à la fin du fichier
        while(fgets(ligne_membre, TAILLE_MAX_LIGNE_FICHIER_MEMBRES, fichier_membres) != NULL) {
            enleverCaracteresRestants(ligne_membre);
            liste_formations_temporaire = creerListeFormation();
            cle = strtok(ligne_membre, delimiteur);
            indice_cle = 0;
            while(cle != NULL) {
                switch(indice_cle) {
                    case 0 :
                        strcpy(numero_membre, cle);
                        break;
                    case 1 :
                        strcpy(nom_membre, cle);
                        break;
                    case 2 :
                        strcpy(prenoms_membre, cle);
                        break;
                    case 3 :
                        strcpy(adresse_membre, cle);
                        break;
                    case 4 :
                        strcpy(code_formation, cle);
                        break;
                    case 5 :
                        strcpy(intitule_formation, cle);
                        break;
                    case 6 :
                        strcpy(annee_formation, cle);
                        break;
                }
                if (indice_cle < 6) {
                    indice_cle++;
                }
                else {
                    indice_cle = 4;
                    liste_formations_temporaire = insererEnQueueFormation(liste_formations_temporaire, code_formation, intitule_formation, annee_formation);
                }
                cle = strtok(NULL, delimiteur);
            }
            liste_membres_temporaire = insererEnQueueMembre(liste_membres_temporaire, numero_membre, nom_membre, prenoms_membre, adresse_membre, liste_formations_temporaire);
        }
    }
    // Si l'ouverture ne s'est pas bien déroulée, on retourne NULL
    else {
        return NULL;
    }
    fclose(fichier_membres);
    return liste_membres_temporaire;
}
// Insérer un nouveau membre ( dans la liste des membres )
liste_membres insererNouveauMembre(liste_membres liste)
{
    char numero_membre[TAILLE_L], nom_membre[TAILLE_XL], prenoms_membre[TAILLE_XL], adresse_membre[TAILLE_XXL], code_formation[TAILLE_L], intitule_formation[TAILLE_L], annee_formation[TAILLE_L], nombre_formations[TAILLE_L];
    int test1=SUCCES, test2=ECHEC;
    long i=0, compteur=0;
    liste_membres liste_membres_temporaire=liste;
    liste_formations liste_formations_temporaire = creerListeFormation();
    while (test2 == ECHEC || test1 == SUCCES) {
        liste_membres_temporaire = liste;
        printf("\nNumero du membre a ajouter : ");
        fgets(numero_membre, sizeof numero_membre, stdin);
        enleverCaracteresRestants(numero_membre);
        test2 = estNumerique(numero_membre);
        if (test2 == ECHEC) {
            printf("\nLe numero du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n");
        }
        // On cherche s'il n'y a pas un membre avec le meme numero
        while(liste_membres_temporaire != NULL) {
            if (strcmp(numero_membre, liste_membres_temporaire->numero_membre) == 0) {
                test1 = SUCCES;
                break;
            }
            else {
                test1 = ECHEC;
                liste_membres_temporaire = liste_membres_temporaire->suivant;
            }
        }
        if (test1 == SUCCES) {
            printf("\nCe numero de membre existe deja. Veuillez en retaper un autre.\n");
        }
    }
    test1 = ECHEC;
    liste_membres_temporaire = liste;
    while (test1 == ECHEC) {
        printf("\nNom du membre : ");
        fgets(nom_membre, sizeof nom_membre, stdin);
        enleverCaracteresRestants(nom_membre);
        test1 = estAlphabetique(nom_membre);
        if (test1 == ECHEC) {
            printf("\nLe nom du membre ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
        }
    }
    test1 = ECHEC;
    while (test1 == ECHEC) {
        printf("\nPrénom(s) du membre : ");
        fgets(prenoms_membre, sizeof prenoms_membre, stdin);
        enleverCaracteresRestants(prenoms_membre);
        test1 = estAlphabetique(prenoms_membre);
        if (test1 == ECHEC) {
            printf("\nLe prénom du membre ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
        }
    }
    test1 = ECHEC;
    while (test1 == ECHEC) {
        printf("\nAdresse du membre : ");
        fgets(adresse_membre, sizeof adresse_membre, stdin);
        enleverCaracteresRestants(adresse_membre);
        test1 = estAlphaNumerique(adresse_membre);
        if (test1 == ECHEC) {
            printf("\nL'adresse du membre ne doit contenir que des lettres alphabetiques, des chiffres, et espaces. Veuillez le retaper s'il vous plait.\n");
        }
    }
    test1 = ECHEC;
    while (test1 == ECHEC) {
        printf("\nDonnez le nombre de formations du membre : ");
        fgets(nombre_formations, sizeof nombre_formations, stdin);
        enleverCaracteresRestants(nombre_formations);
        test1 = estNumerique(nombre_formations);
        if (test1 == ECHEC) {
            printf("\nNombre de formations invalide. Veuillez le retaper s'il vous plait.\n");
        }
    }
    compteur = strtol(nombre_formations, NULL, 10);
    if (compteur == 0) {
        liste_formations_temporaire = NULL;
    }
    else {
        for (i=0; i<compteur; i++) {
            test1 = ECHEC;
            while (test1 == ECHEC) {
                printf("\n\n\tCode de la formation %ld: ", i+1);
                fgets(code_formation, sizeof code_formation, stdin);
                enleverCaracteresRestants(code_formation);
                test1 = estAlphaNumerique(code_formation);
                if (test1 == ECHEC) {
                    printf("\n\tLe code de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                }
            }
            test1 = ECHEC;
            while (test1 == ECHEC) {
                printf("\n\tIntitule de la formation %ld: ", i+1);
                fgets(intitule_formation, sizeof intitule_formation, stdin);
                enleverCaracteresRestants(intitule_formation);
                test1 = estAlphaNumerique(intitule_formation);
                if (test1 == ECHEC) {
                    printf("\n\tL'intitule de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                }
            }
            test1 = ECHEC;
            while (test1 == ECHEC) {
                printf("\n\tAnnee de la formation %ld (AAAA/AAAA) : ", i+1);
                fgets(annee_formation, sizeof annee_formation, stdin);
                enleverCaracteresRestants(annee_formation);
                test1 = estAnneeScolaireValide(annee_formation);
                if (test1 == ECHEC) {
                    printf("\n\tL'annee de la formation doit respecter le format donne (Ex: 2016/2017). Veuillez la retaper s'il vous plait.\n");
                }
            }
            liste_formations_temporaire = insererEnQueueFormation(liste_formations_temporaire, code_formation, intitule_formation, annee_formation);
        }
    }
    // Ajouter dans la structure
    liste_membres_temporaire = insererEnQueueMembre(liste_membres_temporaire, numero_membre, nom_membre, prenoms_membre, adresse_membre, liste_formations_temporaire);
    printf("\nVoici le membre que vous venez d'ajouter :\n");
    afficherUnMembre(liste, numero_membre);
    return liste_membres_temporaire;
}
// Rechercher un membre ( dans la liste des membres )
void rechercherMembre(liste_membres liste)
{
    if (liste != NULL) {
        char numero_membre[TAILLE_L];
        int test=ECHEC;
        while (test == ECHEC) {
            printf("\nSaisissez le numero du membre que vous recherchez : ");
            fgets(numero_membre, sizeof numero_membre, stdin);
            enleverCaracteresRestants(numero_membre);
            test = estNumerique(numero_membre);
            if (test == ECHEC) {
                printf("\nCe numero de membre est invalide. Veuillez le retaper s'il vous plait.\n");
            }
            else {
                test = SUCCES;
            }
        }
        test = rechercherUnMembre(liste, numero_membre);
        if (test == SUCCES) {
            printf("\nVoici le membre que vous recherchiez :\n");
            afficherUnMembre(liste, numero_membre);
        }
        else {
            printf("\nCe membre n'existe pas.\n");
        }
    }
    else {
        printf("\nLa liste des membres est vide. Impossible de continuer.\n");
    }
}
// Modifier un membre ( de la liste des membres )
liste_membres modifierMembre(liste_membres membres)
{
    if (membres == NULL) {
        printf("\nAucun membre a afficher. La liste des membres est vide.\n");
        return NULL;
    }
    char choix[TAILLE_L], numero_membre[TAILLE_L], code_formation[TAILLE_L], intitule_formation[TAILLE_L], annee_formation[TAILLE_L];
    int test=ECHEC, trouve=ECHEC;
    long compteur=0;
    while (test == ECHEC) {
        printf("\nSaisissez le numero du membre a modifier : ");
        fgets(numero_membre, sizeof numero_membre, stdin);
        enleverCaracteresRestants(numero_membre);
        test = estNumerique(numero_membre);
        if (test == ECHEC) {
            printf("\nLe numero du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n");
        }
    }
    test = ECHEC;
    liste_membres liste_membres_temporaire=membres;
    while(liste_membres_temporaire != NULL) {
        if (strcmp(numero_membre, liste_membres_temporaire->numero_membre) == 0) {
            test = SUCCES;
            break;
        }
        liste_membres_temporaire = liste_membres_temporaire->suivant;
    }
    if (test == SUCCES) {
        printf("\nVoici le membre que vous allez modifier :\n");
        afficherUnMembre(membres, numero_membre);
        test = ECHEC;
        while (test == ECHEC) {
            printf("\nNouveau nom du membre : ");
            fgets(liste_membres_temporaire->nom_membre, sizeof liste_membres_temporaire->nom_membre, stdin);
            enleverCaracteresRestants(liste_membres_temporaire->nom_membre);
            test = estAlphabetique(liste_membres_temporaire->nom_membre);
            if (test == ECHEC) {
                printf("\nLe nom du membre ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
            }
        }
        test = ECHEC;
        while (test == ECHEC) {
            printf("\nNouveau prénom du membre : ");
            fgets(liste_membres_temporaire->prenoms_membre, sizeof liste_membres_temporaire->prenoms_membre, stdin);
            enleverCaracteresRestants(liste_membres_temporaire->prenoms_membre);
            test = estAlphabetique(liste_membres_temporaire->prenoms_membre);
            if (test == ECHEC) {
                printf("\nLe prénom du membre ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
            }
        }
        test = ECHEC;
        while (test == ECHEC) {
            printf("\nNouvelle adresse du membre : ");
            fgets(liste_membres_temporaire->adresse_membre, sizeof liste_membres_temporaire->adresse_membre, stdin);
            enleverCaracteresRestants(liste_membres_temporaire->adresse_membre);
            test = estAlphaNumerique(liste_membres_temporaire->adresse_membre);
            if (test == ECHEC) {
                printf("\nL'adresse du membre ne doit contenir que des lettres alphabetiques, des chiffres, et espaces. Veuillez le retaper s'il vous plait.\n\n");
            }
        }
        printf("\nFormations :\n");
        printf("\n\t1) Aucune modification a faire :\n");
        printf("\t2) Ajouter une formation\n");
        printf("\t3) Modifier une formation\n");
        printf("\t4) Supprimer une formation\n");
        test = ECHEC;
        while (test == ECHEC) {
            printf("\n\tSaisissez le numero de votre choix : ");
            fgets(choix, sizeof choix, stdin);
            enleverCaracteresRestants(choix);
            test = estNumerique(choix);
            if (test == ECHEC) {
                printf("\nLe choix doit etre numerique. Veuillez le ressaisir s'il vous plait.\n");
            }
            else {
                if (strcmp(choix, "1") != 0 && strcmp(choix, "2") != 0 && strcmp(choix, "3") != 0 && strcmp(choix, "4") != 0) {
                    test = ECHEC;
                    printf("\nCe choix n'appartient pas aux 4 disponibles. Veuillez le ressaisir s'il vous plait.\n");
                }
            }
        }
        compteur = strtol(choix, NULL, 10);
        if (compteur == 1) {
            printf("\nAucune modification a apporter.\n");
        }
        else if (compteur == 2) {
            test = ECHEC;
            while (test == ECHEC) {
                printf("\n\tCode de la formation : ");
                fgets(code_formation, sizeof code_formation, stdin);
                enleverCaracteresRestants(code_formation);
                test = estAlphaNumerique(code_formation);
                if (test == ECHEC) {
                    printf("\n\tLe code de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                }
            }
            test = ECHEC;
            while (test == ECHEC) {
                printf("\n\tIntitule de la formation : ");
                fgets(intitule_formation, sizeof intitule_formation, stdin);
                enleverCaracteresRestants(intitule_formation);
                test = estAlphaNumerique(intitule_formation);
                if (test == ECHEC) {
                    printf("\n\tL'intitule de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                }
            }
            test = ECHEC;
            while (test == ECHEC) {
                printf("\n\tAnnee de la formation (AAAA/AAAA) : ");
                fgets(annee_formation, sizeof annee_formation, stdin);
                enleverCaracteresRestants(annee_formation);
                test = estAnneeScolaireValide(annee_formation);
                if (test == ECHEC) {
                    printf("\n\tL'annee de la formation doit respecter le format donne (Ex: 2016/2017). Veuillez la retaper s'il vous plait.\n");
                }
            }
            liste_membres_temporaire->formations_membre = insererEnQueueFormation(liste_membres_temporaire->formations_membre, code_formation, intitule_formation, annee_formation);
            printf("\nFormation ajoute avec succes.\n");
        }
        else if (compteur == 3) {
            liste_formations liste_formations_temporaire = liste_membres_temporaire->formations_membre;
            if (liste_formations_temporaire ==  NULL) {
                printf("\nAucune formation a modifier.\n");
            }
            else {
                test = ECHEC;
                while (test == ECHEC) {
                    printf("\n\tDonnez le code de la formation a modifier: ");
                    fgets(code_formation, sizeof code_formation, stdin);
                    enleverCaracteresRestants(code_formation);
                    test = estAlphaNumerique(code_formation);
                    if (test == ECHEC) {
                        printf("\n\tLe code de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                    }
                }
                trouve = ECHEC;
                while (liste_formations_temporaire != NULL) {
                    if (strcmp(liste_formations_temporaire->code_formation, code_formation) == 0) {
                        test = ECHEC;
                        while (test == ECHEC) {
                            printf("\n\tNouveau code de la formation : ");
                            fgets(liste_formations_temporaire->code_formation, sizeof liste_formations_temporaire->code_formation, stdin);
                            enleverCaracteresRestants(liste_formations_temporaire->code_formation);
                            test = estAlphaNumerique(liste_formations_temporaire->code_formation);
                            if (test == ECHEC) {
                                printf("\n\tLe code de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                            }
                        }
                        test = ECHEC;
                        while (test == ECHEC) {
                            printf("\n\tNouvel intitule de la formation : ");
                            fgets(liste_formations_temporaire->intitule_formation, sizeof liste_formations_temporaire->intitule_formation, stdin);
                            enleverCaracteresRestants(liste_formations_temporaire->intitule_formation);
                            test = estAlphaNumerique(liste_formations_temporaire->intitule_formation);
                            if (test == ECHEC) {
                                printf("\n\tL'intitule de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                            }
                        }
                        test = ECHEC;
                        while (test == ECHEC) {
                            printf("\n\tNouvelle annee de la formation (AAAA/AAAA) : ");
                            fgets(liste_formations_temporaire->annee_formation, sizeof liste_formations_temporaire->annee_formation, stdin);
                            enleverCaracteresRestants(liste_formations_temporaire->annee_formation);
                            test = estAnneeScolaireValide(liste_formations_temporaire->annee_formation);
                            if (test == ECHEC) {
                                printf("\n\tL'annee de la formation doit respecter le format donne (Ex: 2016/2017). Veuillez la retaper s'il vous plait.\n");
                            }
                        }
                        trouve = SUCCES;
                        break;
                    }
                    liste_formations_temporaire = liste_formations_temporaire->suivant;
                }
                if (trouve == SUCCES) {
                    printf("\nFormation modifiee avec succes.\n");
                }
                else {
                    printf("\nAucune formation ne correspond a ce code.\n");
                }
            }
        }
        else if (compteur == 4) {
            liste_formations liste_formations_temporaire = liste_membres_temporaire->formations_membre;
            liste_formations avant = liste_membres_temporaire->formations_membre;
            if (liste_formations_temporaire ==  NULL) {
                printf("\nAucune formation a modifier.\n");
            }
            else {
                test = ECHEC;
                while (test == ECHEC) {
                    printf("\n\tDonnez le code de la formation a supprimer: ");
                    fgets(code_formation, sizeof code_formation, stdin);
                    enleverCaracteresRestants(code_formation);
                    test = estAlphaNumerique(code_formation);
                    if (test == ECHEC) {
                        printf("\n\tLe code de la formation ne doit contenir que des lettres alphabetiques et/ou espaces. Veuillez le retaper s'il vous plait.\n");
                    }
                }
                test = rechercherUneFormation(liste_formations_temporaire, code_formation);
                if (test = SUCCES) {
                    liste_formations_temporaire = supprimerUneFormation(liste_formations_temporaire, code_formation);
                }
                else {
                    printf("\nCe code ne correspond a aucune formation.\n");
                }
            }
        }
        printf("\nVoici les nouvelles informations du membre :\n");
        afficherUnMembre(membres, numero_membre);
        printf("\nMembre modifie avec succes.\n");
    }
    else {
        printf("\nCe membre n'existe pas.\n");
    }
    return membres;
}
// Supprimer un membre ( de la liste des membres )
liste_membres supprimerMembre(liste_membres liste)
{
    if (liste == NULL) {
        return ECHEC;
    }
    char numero_membre[TAILLE_L];
    int test = ECHEC;
    while (test == ECHEC) {
        printf("\nSaisissez le numero du membre a supprimer : ");
        fgets(numero_membre, sizeof numero_membre, stdin);
        enleverCaracteresRestants(numero_membre);
        test = estNumerique(numero_membre);
        if (test == ECHEC) {
            printf("\nLe numero du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n");
        }
    }
    test = rechercherUnMembre(liste, numero_membre);
    if (test == SUCCES) {
        printf("\nVoici le membre que vous allez supprimer :\n");
        afficherUnMembre(liste, numero_membre);
        liste = supprimerUnMembre(liste, numero_membre);
    }
    else {
        printf("\nCe membre n'existe pas.\n");
    }
    return liste;
}
// Enregistrer la liste des membres ( depuis la liste chaînée liste_membres vers le fichier fichier_membres.txt )
void enregistrerListeMembres(liste_membres liste) {
    // On déclare une variable qui nous permettra de travailler sur le fichier
    FILE* fichier_membres = NULL;
    // On ouvre le fichier contenant les membres (membres.txt) en mode lecture
    fichier_membres = fopen("fichiers/fichier_membres.txt", "w");
    // On teste si l'ouverture s'est bien déroulée. Dans le cas échéant, on peut continuer le traitement du fichier
    if (fichier_membres != NULL) {
        liste_membres liste_membres_temporaire=liste;
        liste_formations liste_formations_temporaire;
        // Tant qu'on n'arrive pas à la fin de la liste
        while(liste_membres_temporaire != NULL) {
            fprintf(fichier_membres, "%s:%s:%s:%s", liste_membres_temporaire->numero_membre, liste_membres_temporaire->nom_membre, liste_membres_temporaire->prenoms_membre, liste_membres_temporaire->adresse_membre);
            liste_formations_temporaire = liste_membres_temporaire->formations_membre;
            while (liste_formations_temporaire != NULL) {
                fprintf(fichier_membres, ":%s:%s:%s", liste_formations_temporaire->code_formation, liste_formations_temporaire->intitule_formation, liste_formations_temporaire->annee_formation);
                liste_formations_temporaire = liste_formations_temporaire->suivant;
            }
            fprintf(fichier_membres, "\n");
            liste_membres_temporaire = liste_membres_temporaire->suivant;
        }
        printf("\nEnregistrement des membres dans le fichier avec succes.\n");
    }
    // Si l'ouverture ne s'est pas bien déroulée
    else {
        printf("\nUne erreur s'est produite lors de l'ouverture du fichier\n");;
    }
    // On ferme le fichier qui a été ouvert
    fclose(fichier_membres);
}
