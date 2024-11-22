#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile.h"

Pile* creer_pile(){
	Pile* p = (Pile*)malloc(sizeof(Pile));
	p->sommet = NULL;
	p->nbElement = 0;
	return p;
}

void empiler(Pile* p, TypeElement e){
	Cellule* c = (Cellule*)malloc(sizeof(Cellule));
	c->cle = e;
	c->succ = p->sommet;
	p->sommet = c;
	p->nbElement++;
}

int est_vide(Pile* p){
	return p->nbElement==0;
}

TypeElement depiler(Pile* p){
	if(!est_vide(p)){
        TypeElement e = p->sommet->cle;
        Cellule* c = p->sommet;
        p->sommet = p->sommet->succ;
        free(c);
        p->nbElement--;
        return e;
	}
}

int taille(Pile* p){
	return p->nbElement;
}

void detruire_pile(Pile* p){
	while(!est_vide(p)){
		depiler(p);
	}
	free(p);
}
