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


void essai_libre(){//fonction pour les essais libres
	int choix_essai;
	//system("clear");
	printf("-----------------------------------------------------\n");
	printf("- 		Date : 05/02/17 PM : essai libre (1h30)     -\n");
	printf("-----------------------------------------------------\n");

	
	while(choix_essai < 1 || choix_essai >2){
	
		printf("Choissiez une option pour continuer :\n");
		printf("1. Commencer le premier essai libre.\n");
		printf("2. Ne pas commencer l'essai libre, fin du Grand Prix de Forumule 1\n");
		printf("Votre choix ? ");
		scanf("%d",&choix_essai);
	
	switch(choix_essai){
		case 1:
			printf("L'essai de ce Vendredi 05/02/17 va commencer...\n");
			break;
		case 2:
			printf("Le Grand Prix de Forumule 1 n'as pas commencé, fin de la course...\n");
			exit(0);
			break;
		default:
			printf("Erreur...Veuillez entrer 1 ou 2 !\n");
			break;
		}
	}
	
}



void menu_depart(int *tab_coureur){//fonction de départ
	int choix;

	printf("\n\n\nProjet OS Pratique présenté par Grégory - Amine - Joel - Nadia\n\n\n");
/**
*
**/
	printf("\n***************************************************\n");
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

		printf("  Votre choix ? ");
		scanf("%d",&choix);

		switch(choix){
			case 1:
				printf("Vous allez commencer la course\n");
					
					int AffichCour;
					printf("Voulez vous afficher tous les Particpants de la course ?\n");
					printf(" 1. OUI - 2. NON\n");
					
					printf("Votre choix ?");
					scanf("%d",&AffichCour);
					
					switch(AffichCour){//switch pour afficher les coureurs ou non
						case 1:
							afficheCoureurs(tab_coureur);
							essai_libre();
							break;
						case 2:
							printf("La liste des coureurs n'est pas affichée...\n");
							essai_libre();
							break;
						default:
							printf("Erreur! Veuillez choisir entre '1' et '2'...");
					}//fin du switch affichCoureurs ou non 
				break;//fin du choix 1 pour commencer la course
			case 2:
				printf("Vous allez quitter le Programme...\n");
				exit(0);
				break;
			default:
				printf("Choix incorrect...");
				break;
		}

	}

}

int main(){
	int tab_coureur [nbParticipants]={44,6,5,7,3,33,19,77,11,27,26,55,14,22,9,12,20,30,8,21,31,94};

	menu_depart(tab_coureur);
	//afficheCoureurs(tab_coureur);
}
