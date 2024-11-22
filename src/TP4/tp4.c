#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"
#include "../Pile/pile.h"

T_Noeud *creer_noeud(int id_entr, char *objet, T_Inter intervalle)
{
    T_Noeud* n = (T_Noeud*)malloc(sizeof(T_Noeud));
    n->droit = n->gauche = NULL;
    n->id_entr = id_entr;
    n->objet = objet;
    n->inter = intervalle;
    return n;
}
void ajouter(T_Arbre *abr, int id_entr, char *objet, T_Inter intervalle)
{
    T_Noeud* n = creer_noeud(id_entr, objet, intervalle);
    if(abr == NULL) {
        abr = &n;
        return;
    }
    T_Noeud* pred = NULL;
    T_Noeud* current = &abr;
    while (current != NULL && compare_intervalle(intervalle, current->inter) != 0){
        pred = current;
        if (intervalle.fin < current->inter.deb) {
            current = current->gauche;
        } else if (intervalle.deb < current->inter.fin){
            current = current->droit;
        }
    }
    if (intervalle.fin < pred->inter.deb) {
        pred->gauche = n;
        return;
    } else if (intervalle.deb < pred->inter.fin) {
        pred->droit = n;
        return;
    }
    return;
}
T_Noeud* rechercher(T_Arbre abr, T_Inter intervalle, int id_entr){
    while(abr != NULL /*&& Cle[abrre] != cle*/ ){ /*TODO rechercher avec id entre vérifier que c'est égale*/
        if(intervalle.fin < abr->inter.deb) {
            abr = abr->gauche;
        } else {
            abr = abr->droit;
        }
    }
    return abr;
}
void supprimer(T_Arbre *abr, T_Inter intervalle, int id_entr){
    if (abr == NULL) return;

    T_Noeud* n = rechercher(abr, intervalle, id_entr);
    T_Noeud* pred = predecesseur(abr, n);

    if (n->gauche == NULL && n->droit == NULL) {
        if (pred == NULL) {
            abr = NULL;
        } else if (n == pred->gauche) {
            pred->gauche = NULL;
        } else {
            pred->droit = NULL;
        }
        free(n);
    } else if (n->gauche == NULL || n->droit == NULL) {
        T_Noeud* fils = (n->gauche != NULL) ? n->gauche : n->droit;
        n = pred;

        if (n == NULL) {
            abr = n;
        } else if (n == pred->gauche) {
            pred->gauche = n;
        } else {
            pred->droit = n;
        }
        free(n);
    } else {
        T_Noeud* nMin = minimum(n->droit);
        n->inter = nMin->inter;
        supprimer(abr, nMin->inter, nMin->id_entr);
    }
}
void modifier(T_Arbre abr, int id_entr, T_Inter actuel, T_Inter nouveau){
    T_Noeud* current = rechercher(abr, actuel, id_entr);
    supprimer(abr, actuel, id_entr);
    ajouter(abr, id_entr, current->objet, nouveau);
    return;
}
void afficher_abr(T_Arbre abr){ //TODO creer gestion de pile + struct
    Pile* p = creer_pile();
	T_Noeud* current = abr;

	while ((current != NULL ) || ( !est_vide(p))) {
        while (current != NULL) {
            empiler(p, current);
            current = current->gauche;
        }
		current = depiler(p);
        printf("%d", current->id_entr);
        current = current->droit;
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
    //TODO
}

int compare_intervalle(T_Inter inter1, T_Inter inter2){
    //TODO
    return 0;
}

T_Noeud* predecesseur(T_Arbre* abr, T_Noeud* n){
    //TODO
    T_Noeud* p = NULL;
    return p;
}
T_Noeud* minimum(T_Arbre* abr){
    //TODO
    T_Noeud* p = NULL;
    return p;
}
