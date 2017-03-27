/***********************************************
* Définition des stuctures et listes chaînées  *
************************************************/
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
// Créer une liste de membres vide
liste_membres creerListeMembre();
// Ajouter un membre en fin de liste
liste_membres insererEnQueueMembre(liste_membres ancienne_liste_membres, char *numero_membre, char *nom_membre, char *prenoms_membre, char *adresse_membre, liste_formations formations_membre);
// Rechercher un membre dans une liste
int rechercherUnMembre(liste_membres liste, char *numero_membre);
// Afficher un membre
void afficherUnMembre(liste_membres liste, char *numero_membre);
// Supprimer un membre
int supprimerUnMembre(liste_membres liste, char *numero_membre);
// Afficher la liste des membres
void afficherListeMembres(liste_membres liste);
// Créer une liste de formations vide
liste_formations creerListeFormation();
// Ajouter un membre en fin de liste
liste_formations insererEnQueueFormation(liste_formations ancienne_liste_formations, char *code_formation, char *intitule_formation, char *annee_formation);
// Afficher la liste des formations
void afficherListeFormations(liste_formations liste);
// Rechercher une formation dans une liste
int rechercherUneFormation(liste_formations liste, char *code_formation);
// Supprimer une formation
int supprimerUneFormation(liste_formations liste, char *code_formation);
