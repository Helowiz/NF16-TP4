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
                printf("\n### Afficher les reservations d'une entreprise ###\n");

                if (*arbre == NULL){
                    printf("Aucune date n'est enregistree\n");
                    break;
                }

                int id_entr;
                printf("Veuillez entrer l'identifiant de l'entreprise que vous souhaitez afficher : ");
                if (!scanf("%d", &id_entr)) {
                    printf("ERREUR : Veuillez entrer un entier.\n");
                    break;
                }

                afficher_entr(*arbre, id_entr);
                break;
            }
            case '3':
            {
                printf("\n### Afficher les reservations sur une periode ###\n");

                if (*arbre == NULL){
                    printf("Aucune date n'est enregistree\n");
                    break;
                }

                int date_deb, date_fin;
                printf("Entrez la date de debut de la periode (format MMJJ) : ");
                if (scanf("%d", &date_deb) != 1 || !est_date_valide(date_deb)) {
                    printf("ERREUR : Date invalide. Veuillez entrer une date au format MMJJ.\n");
                    break;
                }

                printf("Entrez la date de fin de la periode (format MMJJ) : ");
                if (scanf("%d", &date_fin) != 1 || !est_date_valide(date_fin)) {
                    printf("ERREUR : Date invalide. Veuillez entrer une date au format MMJJ.\n");
                    break;
                }

                if (date_deb > date_fin) {
                  printf("ERREUR : Periode invalide : la date de debut doit être avant la date de fin.\n");
                  break;
                }

                printf("Reservations pour la periode du %02d/%02d/2024 au %02d/%02d/2024 :\n",
                date_deb / 100, date_deb % 100, date_fin / 100, date_fin % 100);

                afficher_periode(*arbre, (T_Inter){date_deb, date_fin});
                break;
            }
            case '4':
            {
                printf("\n### Ajouter une reservation ###\n\n");

                int id;
                char* objet = malloc(MAX_STR * sizeof(char));
                T_Inter intervalle;

                printf("Veuillez entrer l'identifiant de votre entreprise : ");
                if (!scanf("%d", &id)) {
                    printf("ERREUR : Veuillez entrer un entier.\n");
                    break;
                }
                viderBuffer();

                printf("Veuillez entrer l'objet de votre reservation : ");

                fgets(objet, MAX_STR, stdin);
                objet[strcspn(objet, "\n")] = '\0';
                printf("%s", objet);
                printf("Entrez la date de debut de la periode (format MMJJ) :");
                if (!scanf("%d", &intervalle.deb)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Entrez la date de fin de la periode (format MMJJ) :");
                if (!scanf("%d", &intervalle.fin)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (verifier_intervalle(intervalle)){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }

                ajouter(arbre, id, objet, intervalle);
                break;
            }
            case '5':
            {
                printf("\n### Modifier une reservation ###\n");

                if (*arbre == NULL){
                    printf("Aucune date n'est enregistree\n");
                    break;
                }

                int id;
                T_Inter actuel;
                T_Inter nouveau;

                printf("Veuillez entrer l'identifiant de votre entreprise : ");
                if (!scanf("%d", &id)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Entrez la date actuelle de debut de la periode (format MMJJ) : ");
                if (!scanf("%d", &actuel.deb)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                printf("Entrez la date actuelle de fin de la periode (format MMJJ) : ");
                if (!scanf("%d", &actuel.fin)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (verifier_intervalle(actuel)){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }

                printf("Entrez la nouvelle date de debut de la periode (format MMJJ) : ");
                if (!scanf("%d", &nouveau.deb)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                printf("Entrez la nouvelle date de fin de la periode (format MMJJ) : ");
                
                if (!scanf("%d", &nouveau.fin)) {
                
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                
                if (verifier_intervalle(nouveau)){
                    printf("ERREUR : Ce n'est pas une date valide");
                    break;
                }
                modifier(*arbre, id, actuel, nouveau);
                break;
            }
            case '6':
            {
                printf("\n### Supprimer une reservation ###\n");

                if (*arbre == NULL){
                    printf("Aucune date n'est enregistree\n");
                    break;
                }

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
                detruire_arbre(arbre);
                break;
            }
            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
                detruire_arbre(arbre);
        }
        printf("\n\n\n");
        viderBuffer();
    }
    return 0;
}
