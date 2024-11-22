#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP4/tp4.h"

int main()
{
    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '8') {
        printf("\n======================================");
        printf("\n1. Afficher toutes les réservations");
        printf("\n2. Afficher les réservations d'une entreprise");
        printf("\n3. Afficher les réservations sur une période");
        printf("\n4. Ajouter une réservation");
        printf("\n5. Modifier une réservation");
        printf("\n6. Supprimer une réservation");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        switch (choix) {
            case '1' :
            {
                printf("\n### Afficher toutes les réservations ###\n");
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
                printf("\n### Ajouter une réservation ###\n");
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
