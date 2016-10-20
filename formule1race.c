#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define nbParticipants 22

void afficheCoureurs(int *tab_coureur);

void menu_depart(int *tab_coureur);

void afficheCoureurs(int *tab_coureur){
	printf("\nListe des Particpants engagés dans la course : \n");
	int i;
	for(i=0; i < nbParticipants ; i++){
		printf("Id : ");
		printf("%d",tab_coureur[i]);	
		printf("\n");
	}
}

void menu_depart(int *tab_coureur){//fonction de départ
	int choix;

	printf("\n\n\nProjet OS Pratique présenté par Grégory - Amine - Joel - Nadia\n\n\n");

	printf("\n ***************************************************\n");
	printf(" *           Grand Prix de Forumule 1              *\n");
	printf(" *              Lieu : Nürburgring                 *\n");
	printf(" *               Pays : Allemagne                  *\n");
	printf(" *                   * * * *                       *\n");
	printf(" *             05/02/16 - 07/02/17                 *\n");
	printf(" ***************************************************\n\n");

	printf(" ---------------------------------------------------\n");
	printf(" -       -- Présentation de la course --           -\n");
	printf(" -   (22 voitures engagées dans le grand prix)     -\n");
	printf(" ---------------------------------------------------\n\n");

	printf(" -      Programme de la course du week-end         -\n\n");

	printf(" -       05/02/17 PM : essai libre (1h30)          -\n\n");
	printf(" -        06/02/17 AM : essai libre (1h)           -\n\n");

	printf(" -  06/02/17 PM : Qualification 1 (18 minutes)     -\n");
	printf(" -  06/02/17 PM : Qualification 2 (15 minutes)     -\n");
	printf(" -  06/02/17 PM : Qualification 3 (12 minutes)     -\n\n");
	printf(" -      07/02/17 PM : La course (x minutes)        -\n");
	printf(" ---------------------------------------------------\n\n");
	printf("\n");
	printf("\n");

	while(choix <1 || choix >2){
		printf("  Choissiez une option pour continuer :\n");
		printf("    1. Démarrer le Grand Prix de Forumule 1.\n");
		printf("    2. Quitter le Programme.\n");
		printf("  Votre choix ?\n");
		scanf("%d",&choix);

		if(choix == 1){ 
			printf("Vous allez commencer la course\n");
			afficheCoureurs(tab_coureur);

		}else if(choix ==2){
			printf("Vous allez Quitter le Programme\n");
		}else if(choix != 1 || choix != 2){
			printf("choix incorrect...\n");
			//break;
		}

	}

}

int main(){
	int tab_coureur [nbParticipants]={44,6,5,7,3,33,19,77,11,27,26,55,14,22,9,12,20,30,8,21,31,94};

	menu_depart(tab_coureur);
	//afficheCoureurs(tab_coureur);
}
