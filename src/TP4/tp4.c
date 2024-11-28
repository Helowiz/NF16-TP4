#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"
#include "../Pile/pile.h"

#define MAX_DATE 1231
#define MIN_DATE 101

T_Noeud *creer_noeud(int id_entr, char *objet, T_Inter intervalle)
{
    T_Noeud* n = (T_Noeud*)malloc(sizeof(T_Noeud));
    n->droit = n->gauche = NULL;
    n->id_entr = id_entr;
    n->objet = strdup(objet);
    n->inter = intervalle;
    return n;
}

void ajouter(T_Arbre *abr, int id_entr, char *objet, T_Inter intervalle)
{
    if(*abr == NULL){
        *abr = creer_noeud(id_entr, objet, intervalle);
        return;
    }

    T_Noeud* n = creer_noeud(id_entr, objet, intervalle);
    T_Noeud* pred = NULL;
    T_Noeud* current = *abr;

    while (current != NULL && current->inter.deb != intervalle.deb){
        pred = current;
        if (intervalle.deb < current->inter.deb) {
            current = current->gauche;
        } else {
            current = current->droit;
        }
    }

    if (intervalle.deb < pred->inter.deb) {
        pred->gauche = n;
    } else if (intervalle.deb > pred->inter.deb) {
        pred->droit = n;
    } else {
        printf("ERREUR : Une reservation est deja a cette date");
    }
    return;
}
T_Noeud* rechercher(T_Arbre abr, T_Inter intervalle, int id_entr){
    T_Noeud* current = abr;
    while(current != NULL){
        if (current->inter.deb == intervalle.deb &&
            current->inter.fin == intervalle.fin &&
            current->id_entr == id_entr) {
            return current;
        }

        if(intervalle.fin < current->inter.deb) {
            current = current->gauche;
        } else {
            current = current->droit;
        }
    }
    return NULL;
}
void supprimer(T_Arbre* abr, T_Inter intervalle, int id_entr){
    if (*abr == NULL) return;

    T_Noeud* n = rechercher(*abr, intervalle, id_entr);
    if (n == NULL) return;

    T_Noeud* pred = predecesseur(*abr, n);

    if (n->gauche == NULL && n->droit == NULL) {
        if (pred == NULL) { //Racine
            *abr = NULL;
        } else if (n == pred->gauche) {
            pred->gauche = NULL;
        } else {
            pred->droit = NULL;
        }
        free(n->objet);
        free(n);
        n = NULL;
    } else if (n->gauche == NULL || n->droit == NULL) {
        T_Noeud* fils = (n->gauche != NULL) ? n->gauche : n->droit;
        if (pred == NULL) { //racine
            *abr = fils;
        } else if (n == pred->gauche) {
            pred->gauche = fils;
        } else {
            pred->droit = fils;
        }
        free(n->objet);
        free(n);
        n = NULL;
    } else {
        T_Noeud* succ = minimum(n->droit);
        n->inter = succ->inter;
        n->id_entr = succ->id_entr;
        n->objet = strdup(succ->objet);
        supprimer(&(n->droit), succ->inter, succ->id_entr);
    }
    return;
}
void modifier(T_Arbre abr, int id_entr, T_Inter actuel, T_Inter nouveau){
    if (abr == NULL) return;
    T_Noeud* current = rechercher(abr, actuel, id_entr);
    if (current == NULL) {
        return;
    }
    char* objet_copie = strdup(current->objet);
    supprimer(&abr, actuel, id_entr);
    ajouter(&abr, id_entr, objet_copie, nouveau);
    return;
}
void afficher_abr(T_Arbre abr){

    if (abr == NULL){
        printf("\nL'arbre est vide");
        return;
    }

    Pile* p = creer_pile();
	T_Noeud* current = abr;

	while ((current != NULL ) || ( !est_vide(p))) {
        while (current != NULL) {
            empiler(p, current);
            current = current->gauche;
        }
		current = depiler(p);

		afficher_date(current->inter.deb%100);
		afficher_date(current->inter.deb/100);
		printf("2024 au ");
		afficher_date(current->inter.fin%100);
		afficher_date(current->inter.fin/100);
        printf("2024 : entr. %d - %s", current->id_entr, current->objet);

        current = current->droit;
    }
}

void afficher_date(int valeur) {
    if (valeur < 10) {
        printf("0%d/", valeur);
    } else {
        printf("%d/", valeur);
    }
}


void afficher_entr(T_Arbre abr, int id_entr){
    Pile* p = creer_pile();
	T_Noeud* current = abr;

	while ((current != NULL ) || ( !est_vide(p))) {
        if (current->id_entr == id_entr) {
            while (current != NULL ) {
                empiler(p, current);
                current = current->gauche;
            }
            current = depiler(p);
            printf("%d", current->id_entr);
            current = current->droit;
        }
    }
}
void afficher_periode(T_Arbre abr, T_Inter periode){
    Pile* p = creer_pile();
	T_Noeud* current = abr;

	while ((current != NULL ) || ( !est_vide(p))) {
        if (1) { /*debI >= debP && finI <= finP*/
            while (current != NULL ) {
                empiler(p, current);
                current = current->gauche;
            }
            current = depiler(p);
            printf("%d", current->id_entr);
            current = current->droit;
        }
    }
}

void detruire_arbre(T_Arbre *abr){
    // TODO
    return;
}

void viderBuffer(){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int compare_intervalle(T_Inter inter1, T_Inter inter2){

    return 0;
}

T_Noeud* predecesseur(T_Arbre abr, T_Noeud* n){
    T_Noeud* pred = NULL;
    T_Noeud* current = abr;


    while (current != NULL) {
        if (current->inter.deb == n->inter.deb &&
            current->inter.fin == n->inter.fin &&
            current->id_entr == n->id_entr) {
            return pred;
        }
        pred = current;
        if(n->inter.fin < current->inter.deb) {
            current = current->gauche;
        } else {
            current = current->droit;
        }
    }
    return pred;
}
T_Noeud* minimum(T_Noeud* n){
    while (n->gauche != NULL) {
        n = n->gauche;
    }
    return n;
}

void afficher_noeud(T_Noeud* n){
    if (n == NULL) {
        printf("NULL\n");
        return;
    }
    printf("Identifiant entreprise : %d \nObjet : %s Date debut : %d, Date fin : %d", n->id_entr, n->objet, n->inter.deb, n->inter.fin);
}

int est_date_valide(int date){
    int jour = date % 100;
    int mois = date / 100;

    if (mois < 1 || mois > 12) return 0;

    switch (mois) {
        case 2: // Février
            if (jour < 1 || jour > 28) return 0;
            break;
        case 4: case 6: case 9: case 11:
            if (jour < 1 || jour > 30) return 0;
            break;
        default:
            if (jour < 1 || jour > 31) return 0;
            break;
    }
    return 1;
}

int verifier_intervalle(T_Inter inter) {
    return inter.deb < MIN_DATE || inter.fin > MAX_DATE || inter.deb > inter.fin || !est_date_valide(inter.deb) || !est_date_valide(inter.fin);
}
