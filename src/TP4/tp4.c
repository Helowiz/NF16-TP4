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

void ajouter(T_Arbre *abr, int id_entr, char *objet, T_Inter intervalle){
    if(*abr == NULL){
        *abr = creer_noeud(id_entr, objet, intervalle);
        return;
    }

    T_Noeud* n = creer_noeud(id_entr, objet, intervalle);
    T_Noeud* pred = NULL;
    T_Noeud* current = *abr;

    while (current && current->inter.deb != intervalle.deb){
        pred = current;
        if (intervalle.fin < current->inter.deb) {
            current = current->gauche;
        } else if (intervalle.deb > current->inter.fin) {
            current = current->droit;
        } else {
            printf("ERREUR : Une reservation est deja a cette date\n");
            free(n->objet);
            free(n);
            return;
        }
    }

    if(pred == NULL){
        printf("ERREUR : Une reservation est deja a cette date");
        free(n->objet);
        free(n);
        return;
    }

    if (intervalle.deb < pred->inter.deb) {
        pred->gauche = n;
    } else if (intervalle.deb > pred->inter.deb) {
        pred->droit = n;
    } else {
        printf("ERREUR : Une reservation est deja a cette date");
        free(n->objet);
        free(n);
    }
    return;
}

T_Noeud* rechercher(T_Arbre abr, T_Inter intervalle, int id_entr){
    if (abr == NULL){
        printf("L'arbre est vide\n");
    }

    T_Noeud* current = abr;
    while(current){
        if (current->inter.deb == intervalle.deb &&
            current->inter.fin == intervalle.fin &&
            current->id_entr == id_entr) {
            return current;
        }
        current = intervalle.fin < current->inter.deb ? current->gauche : current->droit;
    }
    return current;
}

void supprimer(T_Arbre* abr, T_Inter intervalle, int id_entr){
    if (*abr == NULL){
        printf("L'arbre est vide\n");
        return;
    }

    T_Noeud* pred = NULL;
    T_Noeud* current = *abr;
    while (current) {
        if (current->inter.deb == intervalle.deb && current->inter.fin == intervalle.fin && current->id_entr == id_entr) {
            suppression(abr, current, pred);
            return;
        }
        pred = current;
        current = intervalle.fin < current->inter.deb ? current->gauche : current->droit;
    }
    printf("ERREUR : Le noeud n'a pas ete trouve");
    return;
}

void modifier(T_Arbre abr, int id_entr, T_Inter actuel, T_Inter nouveau){
    if (abr == NULL){
        printf("Aucune date n'est enregistree\n");
        return;
    }
    
    T_Noeud* pred = NULL;
    T_Noeud* current = abr;
    while (current) {
        if (current->inter.deb == actuel.deb && current->inter.fin == actuel.fin && current->id_entr == id_entr) {
            char* objet_copie = strdup(current->objet); 
            suppression(&abr, current, pred);
            ajouter(&abr, id_entr, objet_copie, nouveau);
            return;
        }
        pred = current;
        current = actuel.fin < current->inter.deb ? current->gauche : current->droit;
    }
    printf("ERREUR : Le noeud n'a pas ete trouve");
    return;
}

void afficher_abr(T_Arbre abr){

    if (abr == NULL){
        printf("Aucune date n'est enregistree\n");
        return;
    }

    Pile* p = creer_pile();
	T_Noeud* current = abr;

	while ((current) || ( !est_vide(p))) {
        while (current) {
            empiler(p, current);
            current = current->gauche;
        }
		current = depiler(p);
	    printf("%02d/%02d/2024 au %02d/%02d/2024 : entr. %d - %s\n",
        current->inter.deb % 100, current->inter.deb / 100, current->inter.fin % 100, current->inter.fin / 100, current->id_entr, current->objet);
        current = current->droit;
    }
}

void afficher_entr(T_Arbre abr, int id_entr){

    if (abr == NULL){
        printf("Aucune entreprise n'est enregistree\n");
        return;
    }

    Pile* p = creer_pile();
	T_Noeud* current = abr;

    printf("Reservations de l'entreprise %d :\n", id_entr);
	while ((current) || (!est_vide(p))) {
            while (current) {
                empiler(p, current);
                current = current->gauche;
            }
            current = depiler(p);
            if (current->id_entr == id_entr)printf("%02d/%02d/2024 au %02d/%02d/2024 : entr. %d - %s\n", current->inter.deb % 100, current->inter.deb / 100, current->inter.fin % 100, current->inter.fin / 100, current->id_entr, current->objet);
            current = current->droit;
    }
}
void afficher_periode(T_Arbre abr, T_Inter periode){
    if (abr == NULL) {
        printf("Aucune reservation trouvee pour la periode donnee (%02d/%02d au %02d/%02d).\n",
               periode.deb / 100, periode.deb % 100,
               periode.fin / 100, periode.fin % 100);
        return;
    }
    Pile* p = creer_pile();
    T_Noeud* current = abr;
    int found = 0;
    while ((current) || (!est_vide(p))) {
        while (current) {
            empiler(p, current);
            current = current->gauche;
        }
        current = depiler(p);
        if ((current->inter.deb <= periode.fin) && (current->inter.fin >= periode.deb)) {
            found = 1;
            printf("%02d/%02d/2024 au %02d/%02d/2024 : entr. %d - %s\n", current->inter.deb % 100, current->inter.deb / 100, current->inter.fin % 100, current->inter.fin / 100, current->id_entr, current->objet);
        }
        current = current->droit;
    }
    if (!found) {
        printf("Aucune reservation trouvee pour la periode donnee (%02d/%02d au %02d/%02d).\n",
               periode.deb / 100, periode.deb % 100,
               periode.fin / 100, periode.fin % 100);
    }
}

void detruire_arbre(T_Arbre *abr) {
    if (*abr == NULL) {
        return;
    }
    detruire_arbre(&(*abr)->gauche);
    detruire_arbre(&(*abr)->droit);

    free((*abr)->objet);
    free(*abr);
    *abr = NULL;
}

void viderBuffer(){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

T_Noeud* minimum(T_Noeud* n){
    while (n->gauche) {
        n = n->gauche;
    }
    return n;
}

int est_date_valide(int date){
    int jour = date % 100;
    int mois = date / 100;

    if (mois < 1 || mois > 12) return 0;

    switch (mois) {
        case 2: // Fevrier
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

void suppression(T_Arbre* abr, T_Noeud* n, T_Noeud* p){
    if (n->gauche == NULL && n->droit == NULL) {
        if (p == NULL) { //Racine
            *abr = NULL;
        } else if (n == p->gauche) {
            p->gauche = NULL;
        } else {
            p->droit = NULL;
        }
        free(n->objet);
        free(n);
        n = NULL;
    } else if (n->gauche == NULL || n->droit == NULL) {
        T_Noeud* fils = n->gauche ? n->gauche : n->droit;
        if (p == NULL) { //Racine
            *abr = fils;
        } else if (n == p->gauche) {
            p->gauche = fils;
        } else {
            p->droit = fils;
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