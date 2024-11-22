#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED
#include "../TP4/tp4.h"

typedef T_Noeud* TypeElement;

typedef struct Cellule {
	TypeElement cle;
	struct Cellule* succ;
} Cellule;

typedef struct Pile {
	Cellule* sommet;
	int nbElement;
} Pile;

//FONCTION PILE
Pile* creer_pile();
void empiler(Pile* p, TypeElement e);
int est_vide(Pile* p);
TypeElement depiler(Pile* p);
int taille(Pile* p);
void detruire_pile(Pile* p);

#endif // PILE_H_INCLUDED
