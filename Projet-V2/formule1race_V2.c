#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define nbParticipants 22
#define nbTourEssai_1 5

int random_number(int min, int max);

/**
* Version 2.0
* @author : grégory
**/

typedef struct {
	int numVoiture;
	int *s1,*s2,*s3;
} t_pilote;


t_pilote tb_coureur[nbParticipants]={
	{44,NULL,NULL,NULL},
	{6,NULL,NULL,NULL},
	{5,NULL,NULL,NULL},
	{7,NULL,NULL,NULL},
	{3,NULL,NULL,NULL},
	{33,NULL,NULL,NULL},
	{19,NULL,NULL,NULL},
	{77,NULL,NULL,NULL},
	{11,NULL,NULL,NULL},
	{27,NULL,NULL,NULL},
	{26,NULL,NULL,NULL},
	{55,NULL,NULL,NULL},
	{14,NULL,NULL,NULL},
	{22,NULL,NULL,NULL},
	{9,NULL,NULL,NULL},
	{12,NULL,NULL,NULL},
	{20,NULL,NULL,NULL},
	{30,NULL,NULL,NULL},
	{8,NULL,NULL,NULL},
	{21,NULL,NULL,NULL},
	{31,NULL,NULL,NULL},
	{94,NULL,NULL,NULL}
};


//fonction random pour générer un temps aléatoire
    int random_number(int min, int max){
        static int rand_is_seeded = 0;
        if(!rand_is_seeded){
        	srand(time(NULL));
        	rand_is_seeded=1;
        }
        return rand()%(max-min+1)+min;
    }


//fonction pour afficher tous les coureurs
void afficheCoureurs(){
	printf("Test affichage coureur avec struct\n");
	int i;
	for(i=0; i<nbParticipants; i++){
		printf("Id : %d .\n",tb_coureur[i].numVoiture );
	}	
}


void essai_libre(){//fonction pour les essais libres
	int choix_essai;
	int compteur =0;
	//system("clear");
	printf("-----------------------------------------------------\n");
	printf("- 	   Date : 05/02/17 PM : essai libre (1h30)      -\n");
	printf("-----------------------------------------------------\n");
	
	while(choix_essai < 1 || choix_essai >2){

		printf("Choissiez une option pour continuer :\n");
		printf(" 1. Commencer le premier essai libre.\n");
		printf(" 2. Ne pas commencer l'essai libre, fin du Grand Prix de Forumule 1\n");
		printf(" Votre choix ? ");
		scanf("%d",&choix_essai);
	
	switch(choix_essai){

		case 1:
			printf("L'essai de ce Vendredi 05/02/17 va commencer...\n");
			for (int i=0; i<nbTourEssai_1;i++){

				printf("Tour n°%d.\n\n",i+1);
				getchar();
				for(compteur=0; compteur<nbParticipants; compteur++){
					printf("Coureur : %d va commencer son tour. Le coureur a effecuté son tour en %d.\n",tb_coureur[compteur].numVoiture,random_number(100,300));	
				}
			}
			printf("%d tours effecuté lors de ce premier essai.\nEssai libre terminé...\n",nbTourEssai_1);
			getchar();
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


void menu_depart(){//fonction de départ
	int choix;

	printf("\n\n\nProjet OS Pratique présenté par Grégory - Amine - Joel - Nadia\n\n\n");

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
						afficheCoureurs();
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

/**
* @author : grégory
**/

int main(){
	
	menu_depart();
}
