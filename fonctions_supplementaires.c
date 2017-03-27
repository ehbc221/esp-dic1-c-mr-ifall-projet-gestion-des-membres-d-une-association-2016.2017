/*************************************************
*     Déclaration des bibliothèques requises     *
*************************************************/
// Fonctions des bibliothèques standard + Constantes
#include "entetes.h"
// Fonctions supplémentaires de l'application
#include "fonctions_supplementaires.h"
/**********************************************************************
*     Définition des fonctions "supplémentaires" de l'application     *
**********************************************************************/
// Nettoyer l'écran (effacer tout son contenu). Alternative à system("cls") sous windows, ou system("clear") sous linux
void clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
// Vérifier si une chaine de caractères est égale "quitter" ou non (prise en compte de la casse)
int verifierSortie(char* chaine)
{
    char quitter[8]="quitter";
    if (strcmp(chaine, quitter) == 0) {
        return QUITTER;
    }
    else {
        return ECHEC;
    }
}
// Afficher un message après avoir choisi de quitter l'application
void afficherMessageSortie()
{
    printf("\nVous avez choisi de quitter l'application. Merci de l'avoir utilisee.\n");
}
// Corriger quelques problèmes liés à l'utilisation de la fonction fgets soit en enlevant le retour a la ligne (après une saisie correcte c-a-d terminée par "entrée"), soit en enlevant les caractères restants dans le buffer (après une saisie incorrecte c-a-d terminée dépassement de la taille de la chaine, ou erreur interne)
void enleverCaracteresRestants(char *chaine)
{
    // On cherche le caractère de retour à la ligne "\n"
    char *p = strchr(chaine, '\n');
    // Si on le trouve, on annule sa valeur
    if (p) {
        *p = '\0';
    }
    // Sinon : cas où la dernière saisie ne s'est pas déroulée correctement (ou on a dépassé le nombre de caractères max spécifié en deuxième argument) alors la seconde saisie va contenir les caractères qui n'ont pas été lus
    else {
        enleverCaracteresSuperflus();
    }
}
// Enlever les caractères restants dans le buffer (après une saisie incorrecte c-a-d terminée dépassement de la taille de la chaine, ou erreur interne)
void enleverCaracteresSuperflus(void)
{
    int caractere;
    // Lire tous les caractères restant dans le buffer le buffer s'il reste des caractères non lus
    while ((caractere = getchar()) != '\n' && caractere != EOF) {}
}
// Vérifier si une chaine de caractères est alphanumérique ou non
int estAlphaNumerique(char *chaine)
{
    int i, test=SUCCES, taille_chaine = strlen(chaine);
    // Pour chaque caractere de la chaine
    for (i=0; i<taille_chaine; i++) {
        // Si ce n'est ni une lettre alphabétique, ni un chiffre, ni un espace, retourner ECHEC
        if (!isdigit(chaine[i]) && !isalpha(chaine[i]) && !isspace(chaine[i])) {
            return test = ECHEC;
        }
    }
    return test;
}
// Vérifier si une chaine de caractères est alphabétique ou non
int estAlphabetique(char *chaine)
{
    int i, test=SUCCES, taille_chaine = strlen(chaine);
    // Pour chaque caractere de la chaine
    for (i=0; i<taille_chaine; i++) {
        // Si ce n'est pas une lettre alphabétique, retourner ECHEC
        if (!isalpha(chaine[i]) && !isspace(chaine[i])) {
            return test = ECHEC;
        }
    }
    return test;
}
// Vérifier si une chaine de caractères est numérique ou non (>0)
int estNumerique(char *chaine)
{
    int i, test=SUCCES, taille_chaine = strlen(chaine);
    // Pour chaque caractere de la chaine
    for (i=0; i<taille_chaine; i++) {
        // Si ce n'est pas un chiffre, retourner ECHEC
        if (!isdigit(chaine[i])) {
            return test = ECHEC;
        }
    }
    return test;
}
// Vérifier si une chaine de caractères est une année scolaire valide ou non
int estAnneeScolaireValide(char *chaine)
{
    int i, test=SUCCES, taille_chaine = strlen(chaine);
    // Si la taille est differente de 9 (), retourner 0
    if (taille_chaine != 9) {
        test = ECHEC;
        return test;
    }
    // Si le caractère séparateur est different de /, retourner 0
    if (chaine[4] != '/') {
        test = ECHEC;
        return test;
    }
    // Pour chaque caractere de la chaine (à part le séparateur)
    for (i=0; i<taille_chaine && i!= 4; i++) {
        // Si ce n'est pas un chiffre, retourner 0
        if (!isdigit(chaine[i])) {
            test = ECHEC;
            return test;
        }
    }
    // Sinon, retourner 1
    return test;
}
