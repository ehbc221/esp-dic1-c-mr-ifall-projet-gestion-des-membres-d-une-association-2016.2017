/****************************************
*     Déclaration des bibliotheques     *
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>





/*******************************************************************
*     Déclaration des fonctions "principales" de l'application     *
*******************************************************************/

void afficherIntitule();
int connection();
int verifierConnection(char* login, char* mot_de_passe);
void afficherMessageConnection(int status_connection);
int insererMembre();
int rechercherMembre(int numero_membre);
int afficherMembre(int numero_membre);
int modifierMembre(int numero_membre);
int supprimerMembre(int numero_membre);





/***********************************************************************
*     Déclaration des fonctions "supplémentaires" de l'application     *
***********************************************************************/

int isAlphaNumerique(char *chaine);





/**************************
*     Fonction main()     *
**************************/

int main(int argc, char const *argv[])
{
	int etat_connection;
	afficherIntitule();
	etat_connection = connection();
	return 0;
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
	char login[25], mot_de_passe[25];
	int status_connection=0;
	printf("Saisissez votre login : ");
	scanf("%s", login);
	printf("Saisissez votre mot de passe : ");
	scanf("%s", mot_de_passe);
	status_connection = verifierConnection(login, mot_de_passe);
	return status_connection;
}

/*
	Cette fonction permet de vérifier si un couple d'identififants correspond a un utilisateur ou non
	Retourne un status de connection :
		-1	: Erreur interne
		0	: Authentification echouée
		1	: Authentification réussie
*/
int verifierConnection(char* login, char* mot_de_passe)
{
	int status_connection=0;
	FILE* fichier_utilisateurs = NULL;
	fichier_utilisateurs = fopen("membres.txt", "r");
	if (fichier_utilisateurs != NULL) {
	}
	else {
		return -1;
	}
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
	if (status_connection == -1) {
		printf("Une erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
	}
	else if (status_connection == 0) {
		printf("Aucun utilisateur ne correspond aux identifiants saisis.\n");
	}
	else if (status_connection == 1) {
		printf("Authentification reussie.\n");
	}
}

/*
	Cette fonction permet d'insérer un membre dans le fichier membres.txt
	Retourne un status d'ajout :
		-1	: Erreur interne
		0	: Ce membre éxiste déjà
		1	: Ajout réussi
*/
int insererMembre()
{
	int status_ajout;
	FILE* fichier_membres = NULL;
	fichier_membres = fopen("membres.txt", "a+");
	return status_ajout;
}

/*
	Cette procedure permet d'afficher un message relatif à un status d'ajout de membre
	Status d'ajout :
		-1	: Erreur interne
		0	: Ce membre éxiste déjà
		1	: Ajout réussi
*/
void afficherMessageInsererMembre(int status_ajout)
{
	if (status_ajout == -1) {
		printf("Une erreur est survenue lors de la connection. Merci de reessayer plutard.\n");
	}
	else if (status_ajout == 0) {
		printf("Un utilisateur avec ce numéro existe deja.\n");
	}
	else if (status_ajout == 1) {
		printf("Ajout du membre reussi.\n");
	}
}


int rechercherMembre(int numero_membre)
{
	int status_recherche;
	FILE* fichier_membres = NULL;
	fichier_membres = fopen("membres.txt", "r");
	return status_recherche;
}

int afficherMembre(int numero_membre)
{
	int membre_existe;
	membre_existe = rechercherMembre(numero_membre);
}


/*
	Définition des fonctions "supplémentaires" de l'application
*/
int isAlphaNumerique(char *chaine)
{
	int i, resultat=1, taille_chaine = strlen(chaine);
	// Pour chaque caractere de la chaine
	for (i=0; i<taille_chaine; i++) {
		// Si ce n'est ni une lettre de l'alphabet, ni un chiffre, retourner 0
		if (!isdigit(chaine[i]) && !isalpha(chaine[i])) {
			resultat = 0;
			return resultat;
		}
	}
	// Sinon, retourner 1
	return resultat;
}