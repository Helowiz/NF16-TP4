#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP4/tp4.h"

#define MAX_STR 255

int main()
{
    T_Arbre* arbre = (T_Arbre*)malloc(sizeof(T_Arbre));
    *arbre = NULL;
    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '7') {
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
                afficher_abr(*arbre);
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
                objet[strcspn(objet, "\n")] = '\0';

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
                if (verifier_intervalle(intervalle) == 1){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }

                ajouter(arbre, id, objet, intervalle);
                break;
            }
            case '5':
            {
                printf("\n### Modifier une reservation ###\n");

                int id;
                T_Inter actuel;
                T_Inter nouveau;

                printf("Veuillez entrer l'identifiant de votre entreprise : ");
                if (!scanf("%d", &id)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("DATE ACTUEL : Veuillez entrer la date de debut sous le format MMJJ : ");
                if (!scanf("%d", &actuel.deb)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                printf("DATE ACTUEL : Veuillez entrer la date de debut sous le format MMJJ : ");
                if (!scanf("%d", &actuel.fin)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (verifier_intervalle(actuel) == 1){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }

                printf("DATE NOUVEL : Veuillez entrer la date de debut sous le format MMJJ : ");
                if (!scanf("%d", &nouveau.deb)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("DATE NOUVEL : Veuillez entrer la date de debut sous le format MMJJ : ");
                if (!scanf("%d", &nouveau.fin)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (verifier_intervalle(nouveau) == 1){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }

                modifier(*arbre, id, actuel, nouveau);
                break;
            }
            case '6':
            {
                printf("\n### Supprimer une reservation ###\n");

                int id;
                T_Inter intervalle;

                printf("Veuillez entrer l'identifiant de votre entreprise : ");
                if (!scanf("%d", &id)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

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
                if (verifier_intervalle(intervalle) == 1){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }
                supprimer(arbre, intervalle, id);
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
