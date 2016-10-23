/**
* Version 2.0
* @author : grégory
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define nbParticipants 22
#define nbTourEssai_1 2
#define maxCaracteres 21

int random_number(int min, int max);
int compteur=0;
pthread_mutex_t lock; 

/**
* Il y a un soucis quand deux threads cherchent à modifier deux variables en même temps.
* Donc on utilise les mutex :
* Les mutex permettent l'execution mutuelle (mecanisme de synchronisation)
* @pthread_mutex_t lock; 
* Un mutex est en C une variable de type pthread_mutex_t. 
* Elle va nous servir de verrou, pour nous permettre de protéger des données. 
**/

typedef struct {
	int numVoiture;
	char name[maxCaracteres];
	int *s1,*s2,*s3;
	int *tour;
} t_pilote;

//Definition de tous les pilotes participants
t_pilote tb_coureur[nbParticipants]={
	{44,"L.HAMILTON",NULL,NULL,NULL,NULL},
	{6,"N.ROSBERG",NULL,NULL,NULL,NULL},
	{5,"S.VETTEL",NULL,NULL,NULL,NULL},
	{7,"R.RAIKKONEN",NULL,NULL,NULL,NULL},
	{3,"D.RICCIARDO",NULL,NULL,NULL,NULL},
	{33,"M.VERSTAPPEN",NULL,NULL,NULL,NULL},
	{19,"F.MASSA",NULL,NULL,NULL,NULL},
	{77,"V.BOTTAS",NULL,NULL,NULL,NULL},
	{11,"S.PEREZ",NULL,NULL,NULL,NULL},
	{27,"N.HULKENBERG",NULL,NULL,NULL,NULL},
	{26,"D.KVYAT",NULL,NULL,NULL,NULL},
	{55,"C.SAINZ",NULL,NULL,NULL,NULL},
	{14,"F.ALONSO",NULL,NULL,NULL,NULL},
	{22,"J.BUTTON",NULL,NULL,NULL,NULL},
	{9,"M.ERICSSON",NULL,NULL,NULL,NULL},
	{12,"F.NASR",NULL,NULL,NULL,NULL},
	{20,"K.MAGNUSSEN",NULL,NULL,NULL,NULL},
	{30,"J.PALMER",NULL,NULL,NULL,NULL},
	{8,"R.GROSJEAN",NULL,NULL,NULL,NULL},
	{21,"E.GUTIERREZ",NULL,NULL,NULL,NULL},
	{31,"E.OCON",NULL,NULL,NULL,NULL},
	{94,"P.WEHRLEIN",NULL,NULL,NULL,NULL}
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
	int i;
		system("clear");																 
		printf("	*********************************\n");
		printf("	*   ID 	 |	 Nom\n");
		printf("	*-------------------------------*\n");
	for(i=0; i<nbParticipants; i++){
		printf("	*   %d 	 |	 %s\n",tb_coureur[i].numVoiture,tb_coureur[i].name);
	}
		printf("	*********************************\n");
																		 
}


//ici les threads

void* thread_coureur(void* parameter){
	int s1,s2,s3; int tour;
	s1=random_number(30,60);
	s2=random_number(30,60);
	s3=random_number(30,60);
	tour=s1+s2+s3;

	//printf("Le thread est bien créé, soulagement...\n");
	printf("	Segment 1 effecuté en %d secondes.\n",s1);
	sleep(1);
	printf("	Segment 2 effecuté en %d secondes.\n",s2);
	sleep(1);
	printf("	Segment 3 effecuté en %d secondes.\n\n",s3);
	sleep(1);
	printf("	Tour effecuté en %d secondes.\n\n\n",tour);
	sleep(2);

	tb_coureur[compteur].s1=&s1;
	tb_coureur[compteur].s2=&s2;
	tb_coureur[compteur].s3=&s3;

	tb_coureur[compteur].tour=&tour;


}

int creer_thread_coureur(void){

	int new_thread_pilote;
	pthread_t myThread;

	new_thread_pilote=pthread_create(&myThread,0,thread_coureur,0);

	if(new_thread_pilote!=0){
		printf("Create thread failed error: %d\n",new_thread_pilote);
		exit(1);
	}
	pthread_join(myThread,0);

	pthread_mutex_destroy(&lock);
}

//fonction pour les essais libres

void essai_libre(){
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
			system("clear");
			printf("L'essai de ce Vendredi 05/02/17 va commencer...\n");
			for (int i=0; i<nbTourEssai_1;i++){

				printf("Tour n°%d.\n\n",i+1);
				getchar();
				for(compteur=0; compteur<nbParticipants; compteur++){
					printf("	===================================\n");
					printf("	%s (#%d) va commencer son tour.\n\n",tb_coureur[compteur].name,tb_coureur[compteur].numVoiture);
					creer_thread_coureur();
					//printf(tb_coureur[compteur].*s1);
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
