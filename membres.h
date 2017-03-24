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
/***********************************************************************
*     Définition des fonctions relatives aux membres et formations     *
***********************************************************************/
// Créer une liste d'utilisateurs vide
liste_utilisateurs creerUtilisateur();
// Ajouter un utilisateur en fin de liste
liste_utilisateurs insererEnQueueUtilisateur(liste_utilisateurs liste, char* login_utilisateur, char* mot_de_passe_utilisateur);
// Créer une liste de membres vide
liste_membres creerMembre();
// Ajouter un membre en fin de liste
liste_membres insererEnQueueMembre(liste_membres liste, char numero_membre[TAILLE_L], char nom_membre[TAILLE_XL], char prenoms_membre[TAILLE_XL], char adresse_membre[TAILLE_XXL], struct formation *formations_membre);
// Afficher la liste des membres
void afficherListeMembres(liste_membres liste);
// Créer une liste de formations vide
liste_formations creerFormation();
