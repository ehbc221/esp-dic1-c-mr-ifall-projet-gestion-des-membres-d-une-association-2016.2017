/****************************************
*     Déclaration des bibliotheques     *
****************************************/

#include <stdio.h>
#include <stdlib.h>
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





/*******************************************************************
*     Déclaration des fonctions "principales" de l'application     *
*******************************************************************/

void afficherIntitule();
int connection();
void afficherMessageConnection(int status_connection);
int afficherEtChoisirOptionsMenu();
void afficherEnteteOptionChoisie(int numero_option);
int chargerListeMembres();
int insererNouveauMembre();
void afficherMessageInsererNouveauMembre(int status_ajout);
int rechercherMembre(int numero_membre);
void afficherMessageRechercherMembre(int status_recherche);
int afficherMembre(int numero_membre);
int modifierMembre(int numero_membre);
int supprimerMembre(int numero_membre);
int verifierSortie(char* chaine);
void afficherMessageSortie();





/***********************************************************************
*     Déclaration des fonctions "supplémentaires" de l'application     *
***********************************************************************/

int estAlphaNumerique(char *chaine);
int estAlphabetique(char *chaine);
int estNumerique(char *chaine);
void enleverCaracteresRestants(char *chaine);
void enleverCaracteresSuperflus(void);





/***********************************************
* Définition des stuctures et listes chainées  *
************************************************/

/*
	Structure d'un utilisateur
	Données :
		- Login de l'utilisateur
		- Mot de passe de l'utilisateur
		- Pointeur vers l'utilisateur suivant (s'il éxiste)
*/
typedef struct utilisateur
{
	char login_utilisateur[TAILLE_XL];
	char mot_de_passe_utilisateur[TAILLE_XL];
	struct utilisateur *suivant;
} utilisateur;
typedef utilisateur* liste_utilisateurs;

/*
	Structure d'un membre
	Données :
		- Numéro du membre
		- Nom du membre
		- Prénom(s) du membre
		- Adresse du membre
		- Formations du membre  (si elles éxistent)
		- Pointeur vers le membre suivant (s'il éxiste)
*/
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

/*
	Structure d'une formation
	Données :
		- Code de la formation
		- Intitulé de la formation
		- Date de la formation
		- Pointeur vers la formation suivante (si elle éxiste)
*/
typedef struct formation
{
	char code_formation[TAILLE_L];
	char intitule_formation[TAILLE_L];
	char date_formation[TAILLE_L];
	struct formation *suivant;
} formation;
typedef formation* liste_formations;






/**************************************************
* Traitement élémentaire sur les listes chainées. *
**************************************************/

/***********************
*     Utilisateurs     *
***********************/

// Créer une liste d'utilisateurs vide
liste_utilisateurs creerUtilisateur()
{
	liste_utilisateurs nouvel_utilisateur = NULL;
	return nouvel_utilisateur;
}

// Ajouter un utilisateur en fin de liste
liste_utilisateurs insererEnQueueUtilisateur(liste_utilisateurs liste, char* login_utilisateur, char* mot_de_passe_utilisateur)
{
	utilisateur* nouvel_utilisateur = malloc(sizeof(utilisateur));
	strcpy(nouvel_utilisateur->login_utilisateur, login_utilisateur);
	strcpy(nouvel_utilisateur->mot_de_passe_utilisateur, mot_de_passe_utilisateur);
	nouvel_utilisateur->suivant = NULL;
	if (liste == NULL) {
		return nouvel_utilisateur;
	}
	utilisateur* temporaire = liste;
	while(temporaire->suivant != NULL) {
		temporaire = temporaire->suivant;
	}
	temporaire->suivant = nouvel_utilisateur;
	return liste;
}

/******************
*     Membres     *
******************/

// Créer une liste de membres vide
liste_membres creerMembre()
{
	liste_membres nouveau_membre = NULL;
	return nouveau_membre;
}

// Ajouter un membre en fin de liste
liste_membres insererEnQueueMembre(liste_membres liste, char numero_membre[TAILLE_L], char nom_membre[TAILLE_XL], char prenoms_membre[TAILLE_XL], char adresse_membre[TAILLE_XXL], struct formation *formations_membre)
{
	membre* nouveau_membre = malloc(sizeof(membre));
	strcpy(nouveau_membre->numero_membre, numero_membre);
	strcpy(nouveau_membre->nom_membre, nom_membre);
	strcpy(nouveau_membre->prenoms_membre, prenoms_membre);
	strcpy(nouveau_membre->adresse_membre, adresse_membre);
	nouveau_membre->formations_membre = NULL;
	nouveau_membre->suivant = NULL;
	if (liste == NULL) {
		return nouveau_membre;
	}
	membre* temporaire = liste;
	while(temporaire->suivant != NULL) {
		temporaire = temporaire->suivant;
	}
	temporaire->suivant = nouveau_membre;
	return liste;
}

// Afficher la liste des membres
void afficherListeMembres(liste_membres liste)
{
	element* temporaire = liste;
	if(temporaire != NULL) {
	while(temporaire->suivant != NULL) {
		printf("%s:%s:%s:%s:\n", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre);
		temporaire = temporaire->suivant;
	}
	printf("%s:%s:%s:%s:\n|NIL|", temporaire->numero_membre, temporaire->nom_membre, temporaire->prenoms_membre, temporaire->adresse_membre, temporaire->valeur);
	}
	else {
		printf("Cette liste est vide.\n");
	}
}


/*********************
*     Formations     *
*********************/

// Créer une liste de formations vide
liste_formations creerFormation()
{
	liste_formations nouvelle_formation = NULL;
	return nouvelle_formation;
}





/**************************
*     Fonction main()     *
**************************/

int main(int argc, char const *argv[])
{
	int sortie=0, status_connection=0, choix_menu=0;
	// On affiche l'entete (accueil) de l'application
	afficherIntitule();
	// ONn demande à l'utilisareur de se connecter tant qu'il n'a pas choisi de quitter, ou qu'il ne s'est pas connecté
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
	// Une fois l'utilisateur connecté, on lui affiche le menu de l'application et lui demande de choisir une option
	choix_menu = afficherEtChoisirOptionsMenu();
	/*
		S'il a choisi de quitter l'application, on lui affiche un message de sortie puis on arrete le programme
		Sinon, on continue
	*/
	if (choix_menu == QUITTER) {
		afficherMessageSortie();
		return SUCCES;
	}
	// On affiche l'entete de l'option choisie
	afficherEnteteOptionChoisie(choix_menu);
	return SUCCES;
}





/******************************************************************
*     Définition des fonctions "principales" de l'application     *
******************************************************************/

/*
	Cette procedure affiche juste l'entete de notre application
*/
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

/*
	Cette fonction permet de se connecter.
	Retourne un status de connection :
		-1	: Erreur interne
		0	: Authentification echouée
		1	: Authentification réussie
*/
int connection()
{
	char login_saisi[TAILLE_XL], mot_de_passe_saisi[TAILLE_XL], ligne_membre[TAILLE_XXL], delimiteur[2]=":", *cle, login_temporaire[TAILLE_XL], mot_de_passe_temporaire[TAILLE_XL];
	int status_connection=ECHEC, status_fermeture=ECHEC, indice_cle=0, utilisateur_trouve=0, sortir_app;
	FILE* fichier_utilisateurs = NULL;
	liste_utilisateurs ligne_utilisateur;
	// On ouvre le fichier contenant les utilisateurs (utilisateurs.txt)
	fichier_utilisateurs = fopen("utilisateurs.txt", "r");
	/*
		On teste si l'ouverture s'est bien déroulée
		Dans le cas échéant, on peut continuer le traitement du fichier
	*/
	if (fichier_utilisateurs != NULL) {
		/*
			Saisie des identifiants (login & du mot de passe) de connection
		*/
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
		// Création d'un nouveau membre
		creerMembre();
		// Créer une nouvelle liste d'utilisateurs (vide)
		ligne_utilisateur = creerUtilisateur();
		// Tant qu'on n'arrive pas à la fin du fichier et que l'on n'a pas trouvé un utilisateur correspondant aux identifiants 
		while(fgets(ligne_membre, TAILLE_XXL, fichier_utilisateurs) != NULL && utilisateur_trouve == 0) {
			cle = strtok(ligne_membre, delimiteur);
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
			ligne_utilisateur = insererEnQueueUtilisateur(ligne_utilisateur, login_temporaire, mot_de_passe_temporaire);
			if (strcmp(ligne_utilisateur->login_utilisateur, login_saisi) == 0 && strcmp(ligne_utilisateur->mot_de_passe_utilisateur, mot_de_passe_saisi) == 0) {
				utilisateur_trouve = 1;
				status_connection = SUCCES;
			}
		}
		afficherMessageConnection(status_connection);
	}
	// Si l'ouverture ne s'est pas bien déroulée, on retourne un code d'érreur (-1)
	else {
		status_connection = ERREUR;
		return status_connection;
	}
	// On ferme le fichier qui a été ouvert
	status_fermeture = fclose(fichier_utilisateurs);
	// Si le fermeture ne s'est pas bien passé, retourner un code d'érreur (-1)
	if (status_fermeture == EOF) {
		status_connection = ERREUR;
		return status_connection;
	}
	// Retourner le status de connection
	return status_connection;
}

/*
	Cette procedure permet d'afficher un message relatif à un status de connection
	Status de connection :
		-1	: Erreur interne
		0	: Authentification echouée
		1	: Authentification réussie
*/
void afficherMessageConnection(int status_connection)
{
	if (status_connection == ERREUR) {
		printf("\nUne erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
	}
	else if (status_connection == ECHEC) {
		printf("\nAucun utilisateur ne correspond aux identifiants saisis. Veuillez reessayer s'il vous plait.\n");
	}
	else if (status_connection == SUCCES) {
		printf("\nAuthentification reussie.\n");
	}
}

/*
	Cette fonction permet d'afficher le menu de l'application et de sélectionner d'en sélectionner une option
	Retourne :
		- Un numéro correspondant à l'option choisie
		- -2 (QUITTER) pour quitter l'application
*/
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
		if (strcmp(choix, choix_possibles[0]) != 0 && strcmp(choix, choix_possibles[1]) != 0 && strcmp(choix, choix_possibles[2]) != 0 && strcmp(choix, choix_possibles[3]) != 0 && strcmp(choix, choix_possibles[4]) != 0) {
			printf("\nChoix incorrect. Veuillez le ressaisir s'il vous plait.\n");
		}
		else {
			choix_valide = 1;
		}
	} while (choix_valide == 0);
	// Si le choix est 1, 2, 3, ou 4 (par rapport au menu), retourner ce numéro
	for (i=0; i<4; i++) {
		if (strcmp(choix, choix_possibles[i]) == 0) {
		return i+1;
		}
	}
	// Sinon retourner -2 (QUITTER)
	return QUITTER;
}

/*
	Cette procedure affiche l'entete de l'option choisie (depuis le menu)
*/
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

/*
	Cette fonction permet de charger la liste des membres (dans une liste chainée avec laquelle on travaillera plutard)
	Retourne un status de chargement :
		0	: Echec de chargement
		1	: Chargement réussi
*/
int chargerListeMembres()
{
	int status_chargement=ECHEC;
	char numero_membre[TAILLE_L], nom_membre[TAILLE_XL], prenoms_membre[TAILLE_XL], adresse_membre[TAILLE_XXL];
	// On déclare une variable qui nous permettra de travailler sur le fichier
	FILE* fichier_membres = NULL;
	// On ouvre le fichier contenant les membres (membres.txt) en mode lecture
	fichier_membres = fopen("membres.txt", "r");
	/*
		On teste si l'ouverture s'est bien déroulée
		Dans le cas échéant, on peut continuer le traitement du fichier
	*/
	if (fichier_membres != NULL) {
	// Si l'ouverture ne s'est pas bien déroulée, on retourne un code d'érreur (-1)
	else {
		status_chargement = ECHEC;
		return status_chargement;
	}
	// On ferme le fichier qui a été ouvert
	status_fermeture = fclose(fichier_membres);
	// Si le fermeture ne s'est pas bien passé, retourner un code d'érreur (-1)
	if (status_fermeture == EOF) {
		status_chargement = ECHEC;
		return status_chargement;
	}
	return status_chargement;
}

/*
	Cette fonction permet d'insérer un membre dans le fichier membres.txt
	Retourne un status d'ajout :
		-1	: Erreur interne
		0	: Ce membre éxiste déjà
		1	: Ajout réussi
*/
int insererNouveauMembre()
{
	char numero_membre[TAILLE_L], nom_membre[TAILLE_XL], prenoms_membre[TAILLE_XL], adresse_membre[TAILLE_XXL];
	int status_ajout=ECHEC, status_alpha_numerique=ECHEC, status_alphabetique=ECHEC, status_numerique=ECHEC, status_fermeture=ECHEC;
	FILE* fichier_membres = NULL;
	// On ouvre le fichier contenant les membres (membres.txt)
	fichier_membres = fopen("membres.txt", "a+");
	/*
		On teste si l'ouverture s'est bien déroulée
		Dans le cas échéant, on peut continuer le traitement du fichier
	*/
	if (fichier_membres != NULL) {
		status_alphabetique = ECHEC;
		while (status_numerique == ECHEC) {
			printf("Saisissez le numéro du membre :");
			fgets(numero_membre, sizeof numero_membre, stdin);
			enleverCaracteresRestants(numero_membre);
			status_numerique = estNumerique(numero_membre);
			if (status_numerique == ECHEC) {
				printf("Le numéro du membre ne doit contenir que des chiffres. Veuillez le retaper s'il vous plait.\n\n");
			}
			else {
				status_numerique = SUCCES;
			}
		}
		while (status_alphabetique == ECHEC) {
			printf("Saisissez le nom du membre :");
			fgets(nom_membre, sizeof nom_membre, stdin);
			enleverCaracteresRestants(nom_membre);
			status_alphabetique = estAlphabetique(nom_membre);
			if (status_alphabetique == ECHEC) {
				printf("Le nom du membre ne doit contenir que des lettres alphabétiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
			}
			else {
				status_alphabetique = SUCCES;
			}
		}
		status_alphabetique = ECHEC;
		while (status_alphabetique == ECHEC) {
			printf("Saisissez le prénom du membre :");
			fgets(prenoms_membre, sizeof prenoms_membre, stdin);
			enleverCaracteresRestants(prenoms_membre);
			status_alphabetique = estAlphabetique(prenoms_membre);
			if (status_alphabetique == ECHEC) {
				printf("Le prénom du membre ne doit contenir que des lettres alphabétiques et/ou espaces. Veuillez le retaper s'il vous plait.\n\n");
			}
			else {
				status_alphabetique = SUCCES;
			}
		}
		while (status_alpha_numerique == ECHEC) {
			printf("Saisissez l'adresse du membre :");
			fgets(adresse_membre, sizeof adresse_membre, stdin);
			enleverCaracteresRestants(adresse_membre);
			status_alpha_numerique = estAlphaNumerique(adresse_membre);
			if (status_alpha_numerique == ECHEC) {
				printf("L'adresse du membre ne doit contenir que des lettres alphabétiques, des chiffres, et espaces. Veuillez le retaper s'il vous plait.\n\n");
			}
			else {
				status_alpha_numerique = SUCCES;
			}
		}
		status_alphabetique = ECHEC;
		// Vérifier si le membre éxiste déja
		// Ajouter ce membre dans le fichier membres.txt
		fprintf(fichier_membres, "%s:%s:%s:%s\n", numero_membre, nom_membre, prenoms_membre, adresse_membre);
		status_ajout = SUCCES;
	}
	// Si l'ouverture ne s'est pas bien déroulée, on retourne un code d'érreur (-1)
	else {
		status_ajout = ERREUR;
		return status_ajout;
	}
	// On ferme le fichier qui a été ouvert
	status_fermeture = fclose(fichier_membres);
	// Si le fermeture ne s'est pas bien passé, retourner un code d'érreur (-1)
	if (status_fermeture == EOF) {
		status_ajout = ERREUR;
		return status_ajout;
	}
	return status_ajout;
}

/*
	Cette procedure permet d'afficher un message relatif à un status d'ajout de membre
	Status d'ajout :
		-1	: Erreur interne
		0	: Ce membre éxiste déjà
		1	: Ajout réussi
*/
void afficherMessageInsererNouveauMembre(int status_ajout)
{
	if (status_ajout == ERREUR) {
		printf("\nUne erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
	}
	else if (status_ajout == ECHEC) {
		printf("\nUn utilisateur avec ce numéro existe deja.\n");
	}
	else if (status_ajout == SUCCES) {
		printf("\nAjout du membre reussi.\n");
	}
}

/*
	Cette fonction permet de rechercher un membre dans le fichier membres.txt
	Retourne un status de recherche :
		-1	: Erreur interne
		0	: Ce membre n'éxiste pas
		1	: Membre trouvé
*/
int rechercherMembre(int numero_membre)
{
	int status_recherche;
	FILE* fichier_membres = NULL;
	fichier_membres = fopen("membres.txt", "r");
	return status_recherche;
}

/*
	Cette procedure permet d'afficher un message relatif à un status de recherche d'un membre
	Status de recherche :
		-1	: Erreur interne
		0	: Ce membre n'éxiste pas
		1	: Membre trouvé
*/
void afficherMessageRechercherMembre(int status_recherche)
{
	if (status_recherche == ERREUR) {
		printf("\nUne erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
	}
	else if (status_recherche == ECHEC) {
		printf("\nAucun membre ne correspond au numéro saisi.\n");
	}
	else if (status_recherche == SUCCES) {
		printf("\nMembre trouvé.\n");
	}
}

/*
	Cette fonction permet d'afficher un membre depuis le fichier membres.txt
	Retourne un status d'affichage :
		-1	: Erreur interne
		0	: Ce membre n'éxiste pas
		1	: Membre trouvé
*/
int afficherMembre(int numero_membre)
{
	int membre_existe;
	membre_existe = rechercherMembre(numero_membre);
}

/**********************************************************************
*     Définition des fonctions "supplémentaires" de l'application     *
**********************************************************************/

/*
	Cette fonction permet de vérifier si une chaine de caractères est alphanumérique ou non
	Retourne un status :
		0	: La chaine n'est pas alphanumérique
		1	: La chaine est pas alphanumérique
*/
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

/*
	Cette fonction permet de vérifier si une chaine de caractères est alphabétique ou non
	Retourne un status :
		0	: La chaine n'est pas alphabétique
		1	: La chaine est pas alphabétique
*/
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

/*
	Cette fonction permet de vérifier si une chaine de caractères est numérique ou non
	Retourne un status :
		0	: La chaine n'est pas numérique
		1	: La chaine est pas numérique
*/
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

/*
	Cette procedure permet d'enlever restants après l'le retour à la ligne à la fin d'une chaine de caractères
	Elle sera utilisée après les "fgets" pour eviter l'enregistrement du caractère de retour à la ligne "\n",
	ou vider  le buffer s'il reste des caractères non lus
*/
void enleverCaracteresRestants(char *chaine)
{
	// On cherche le caractère de retour à la ligne "\n"
	char *p = strchr(chaine, '\n');
	// Si on le trouve, on annule sa valeur
	if (p) {
		*p = 0;
	}
	/*
		Sinon :  cas où la dernière saisie ne s'est pas déroulée correctement (ou on a dépassé le nombre de caractères max spécifié en deuxième argument)
		alors la seconde saisie va contenir les caractères qui n'ont pas été lus
	*/
	else {
		enleverCaracteresSuperflus();
	}
}

/*
	Cette procedure permet de lire tous les caractères restants dans le buffer
	Elle sera utilisée après les "fgets" dans la fonction "enleverCaracteresRestants" pour vider le buffer
*/
void enleverCaracteresSuperflus(void)
{
	int c;
	// Lire tous les caractères restant dans le buffer le buffer s'il reste des caractères non lus
	while ((c = getchar()) != '\n' && c != EOF) {}
}

/*
	Cette fonction permet de vérifier si une chaine de caractères est égale "quitter" ou non (prise en compte de la casse)
	Retourne :
		- -2 (QUITTER) si c'est vrai
		- 0 (ECHEC) sinon
*/
int verifierSortie(char* chaine)
{
	char quitter[8]="quitter";
	int i, taille_chaine=strlen(chaine);
	for (i=0; i<taille_chaine; i++) {
		chaine[i] = tolower(chaine[i]);
	}
	if (strcmp(chaine, quitter) == 0) {
		return QUITTER;
	}
	else {
		return ECHEC;
	}
}

/*
	Cette procedure permet d'afficher un message après avoir quitter l'application
*/
void afficherMessageSortie()
{
	printf("\nVous avez choisi de quitter l'application. Merci de l'avoir utilisee.\n");
}
