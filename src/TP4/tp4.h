#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

// STRUCTURE INTERVALLE
typedef struct Intervalle {
    int deb;
    int fin;
} T_Inter;

// STRUCTURE NOEUD
typedef struct Noeud {
    int id_entr;
    char* objet;
    T_Inter inter;
    struct Noeud* gauche;
    struct Noeud* droit;
} T_Noeud;

// TYPE T_Arbre
typedef T_Noeud* T_Arbre;

// FONCTIONS DEMANDEES
T_Noeud *creer_noeud(int id_entr, char *objet, T_Inter intervalle);
void ajouter(T_Arbre *abr, int id_entr, char *objet, T_Inter intervalle);
T_Noeud *rechercher(T_Arbre abr, T_Inter intervalle, int id_entr);
void supprimer(T_Arbre *abr, T_Inter intervalle, int id_entr);
void modifier(T_Arbre abr, int id_entr, T_Inter actuel, T_Inter nouveau);
void afficher_abr(T_Arbre abr);
void afficher_entr(T_Arbre abr, int id_entr);
void afficher_periode(T_Arbre abr, T_Inter periode);
void detruire_arbre(T_Arbre *abr);

//FONCTION AJOUTEES
int compare_intervalle(T_Inter inter1, T_Inter inter2);
void viderBuffer();
T_Noeud* predecesseur(T_Arbre abr, T_Noeud* n);
T_Noeud* minimum(T_Noeud* n);
void afficher_noeud(T_Noeud* n);
void afficher_date(int valeur);
int est_date_valide(int date);
int verifier_intervalle(T_Inter inter);

#endif
