#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP4/tp4.h"

#define MAX_STR 255

int main()
{
    T_Arbre* arbre = NULL;
    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '8') {
        printf("\n======================================");
        printf("\n1. Afficher toutes les reservations");
        printf("\n2. Afficher les reservations d'une entreprise");
        printf("\n3. Afficher les reservations sur une periode");
        printf("\n4. Ajouter une reservation");
        printf("\n5. Modifier une reservation");
        printf("\n6. Supprimer une reservation");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        switch (choix) {
            case '1' :
            {
                printf("\n### Afficher toutes les reservations ###\n");
                afficher_abr(arbre);

                break;
            }
            case '2' :
            {
                printf("\n### Afficher les réservations d'une entreprise ###\n");
                break;
            }
            case '3':
            {
                printf("\n### Afficher les réservations sur une période ###\n");
                break;
            }
            case '4':
            {
                printf("\n### Ajouter une reservation ###\n\n");
                //TODO verifier les intervalles si elles ont bien que 4 chiffre
                //TODO verfier que date deb et inferieur a date fin
                int id;
                char* objet[MAX_STR];
                T_Inter intervalle;

                printf("Veuillez entrer l'identifiant de votre entreprise : ");
                if (!scanf("%d", &id)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                viderBuffer();
                printf("Veuillez entrer l'objet de votre reservation : ");
                fgets(objet, MAX_STR, stdin);

                printf("Veuillez entrer la date de debut sous le format MMJJ : ");
                if (!scanf("%d", &intervalle.deb)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Veuillez entrer la date de debut sous le format MMJJ : ");
                if (!scanf("%d", &intervalle.fin)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                if (arbre == NULL) {
                    arbre = creer_noeud(id, objet, intervalle);
                } else {
                    ajouter(arbre, id, objet, intervalle);
                }
                break;
            }
            case '5':
            {
                printf("\n### Modifier une réservation ###\n");
                break;
            }
            case '6':
            {
                printf("\n### Supprimer une réservation ###\n");
                break;
            }
            case '7':
            {
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;
            }

            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }
        printf("\n\n\n");
        viderBuffer();
    }
    return 0;
}
