/*******************************************************************
*     Déclaration des fonctions "principales" de l'application     *
*******************************************************************/
// Afficher l'entete de notre application
void afficherIntitule();
// Se connecter à l'application
int connection();
// Afficher le menu de l'application sélectionner une option
int afficherEtChoisirOptionsMenu();
// Afficher l'entete de l'option choisie ( depuis le menu )
void afficherEnteteOptionChoisie(int numero_option);
// Charger la liste des membres ( depuis le fichier fichier_membres.txt vers une liste chaînée liste_membres )
liste_membres chargerListeMembres();
// Insérer un nouveau membre ( dans la liste des membres )
liste_membres insererNouveauMembre();
// Rechercher un membre ( dans la liste des membres )
void rechercherMembre(liste_membres liste);
// Modifier un membre ( de la liste des membres )
liste_membres modifierMembre(liste_membres liste);
// Supprimer un membre ( de la liste des membres )
liste_membres supprimerMembre(liste_membres liste);
// Enregistrer la liste des membres ( depuis la liste chaînée liste_membres vers le fichier fichier_membres.txt )
void enregistrerListeMembres(liste_membres liste);
