/***********************************************************************
*     Déclaration des fonctions "supplémentaires" de l'application     *
***********************************************************************/
// Nettoyer l'écran (effacer tout son contenu). Alternative à system("cls") sous windows, ou system("clear") sous linux
void clearScreen();
// Vérifier si une chaine de caractères est égale "quitter" ou non (prise en compte de la casse)
int verifierSortie(char* chaine);
// Afficher un message après avoir choisi de quitter l'application
void afficherMessageSortie();
// Corriger quelques problèmes liés à l'utilisation de la fonction fgets soit en enlevant le retour a la ligne (après une saisie correcte c-a-d terminée par "entrée"), soit en enlevant les caractères restants dans le buffer (après une saisie incorrecte c-a-d terminée dépassement de la taille de la chaine, ou erreur interne)
void enleverCaracteresRestants(char *chaine);
// Enlever les caractères restants dans le buffer (après une saisie incorrecte c-a-d terminée dépassement de la taille de la chaine, ou erreur interne)
void enleverCaracteresSuperflus(void);
// Vérifier si une chaine de caractères est alphanumérique ou non
int estAlphaNumerique(char *chaine);
// Vérifier si une chaine de caractères est alphabétique ou non
int estAlphabetique(char *chaine);
// Vérifier si une chaine de caractères est numérique ou non
int estNumerique(char *chaine);
// Vérifier si une chaine de caractères est une année scolaire valide ou non
int estAnneeScolaireValide(char *chaine);
