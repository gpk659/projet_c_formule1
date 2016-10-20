#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h> 
#include <math.h> 
#define NMAXCHAR 21
#define nbPos 22
#define NOM "classement.txt"

int compteur=0;   // pour savoir au quel pilote nous somme et ainsi encoder les résultats dans classement[]
int tour=0; //   pour classer les pilotes selon la scéances d'essai 1,2,3 ou qualif
pthread_mutex_t lock;
FILE *f;

typedef struct {
  
  char team[NMAXCHAR];
  int numVoiture;
  char nat[4];   // nationalite
  char prenom[NMAXCHAR];
  char nom[NMAXCHAR];
  int position;
  int *lapTime;   // changer en pointeur int *lapTime l'initialisation sera alors NULL dans le typedef
  int *bestLap;
  int *deci,*bestDeci;
  int *diffTimeLap;
  int *nbTour;
  int *s1,*s2,*s3;
  } t_pilote;
  
  t_pilote tbPilote[nbPos];
 
  
 // Récupération des valeurs du fichier classement.txt
 
void fileGet(){

f=fopen(NOM,"rt+");
if(f==NULL) {
f=fopen(NOM,"rt+"); 
 }
if(f==NULL) {
printf("Erreur de création de fichier");
getchar();
exit(1);
}

printf("\nAppuyer sur enter pour recuperer le classement pour la course dans le fichier classement.txt...\n\n");
getchar();
for(compteur=0;compteur<=nbPos-1;compteur++) {
fscanf(f,"%s %d %s %s %s \n",tbPilote[compteur].team,&tbPilote[compteur].numVoiture,tbPilote[compteur].nat,tbPilote[compteur].prenom,tbPilote[compteur].nom);
}
sleep(1);

printf("Récupération terminée!\n\n");
sleep(1);
system("clear");
fclose(f);

}

// afficher la grille de départ récupérée dans le fichier classement.txt

void grilleDepart(){
	
	printf("             **********************************************************\n");
   printf("             *          GRILLE de départ pour la course 2014          *\n");
   printf("             *            Position |Team | Car | Pilotes              *\n");
   printf("             **********************************************************\n\n");
	int nbPilotes= sizeof(tbPilote)/sizeof(tbPilote[0]);
	int i;
	for(i=0;i<nbPilotes;i++){
		if(tbPilote[i].numVoiture < 10) {   // Condition if uniquement pour l'affichage
   	printf("             %d.  %s  [%d] %s %s [%s]\n",i+1,tbPilote[i].team,tbPilote[i].numVoiture,tbPilote[i].prenom,tbPilote[i].nom, tbPilote[i].nat);	
   	} else {printf("             %d. %s  [%d] %s %s [%s]\n",i+1,tbPilote[i].team,tbPilote[i].numVoiture,tbPilote[i].prenom,tbPilote[i].nom, tbPilote[i].nat);	
   	}
	}

} 

int fonction_tri(const void *a, const void *b){

		t_pilote *i1 = (t_pilote *)a;
		t_pilote *i2 = (t_pilote *)b;
		
		if((i1->lapTime - i2->lapTime)==0){
		return(i1->deci - i2->deci);
		}else{return(i1->lapTime - i2->lapTime);}
				
}

/*Affichage du tableau trié des pilotes donc le classement*/

void affiche_classement(int t){
	
	int nbClasses =22;

	printf("         ****************************************************************\n");
	printf("         *                         CLASSEMENT 	                        *\n");
	printf("         *     POSITION    |        BEST LAP         |      PILOTE      *\n");
	printf("         ****************************************************************\n");
	

		//qsort(tbPilote,nbPos,sizeof(tbPilote[nbPos]),fonction_tri); // tri du tableau par qsort
		for(compteur=0; compteur<nbClasses;compteur++) {
			if(compteur <= 9) {
			printf("               [%d]            [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else {	printf("               [%d]           [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
	}
			printf("         ****************************************************************\n\n");
}
	  printf("%d Lap. Best lap: .. : Best sector: .. First position :  \n\n",t);

	getchar();
	
	system("clear");						
}

void *aleatoire_thread(void *arg)
{
		int ab1,ab2,ab3; // nb d'abandon possible
		int compteur=(int)arg;
		
		ab1=rand()%21;
		ab2=rand()%21;
		ab3=rand()%21;
		
		if(tour==3 && tbPilote[compteur].position==ab1) {
		printf("Abandon de %s %s",tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else if(tour==1 && tbPilote[compteur].position==ab2) {
		printf("Abandon de %s %s",tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else if(tour==6 && tbPilote[compteur].position==ab3) {
		printf("Abandon de %s %s",tbPilote[compteur].prenom,tbPilote[compteur].nom);
		}
		
		
		pthread_exit(NULL); /* termine le thread ecriture proprement */		
       		      
      
				
}

int creer_un_thread_aleatoire(void)
{
	
	int nouveau_Thread;
	pthread_t my_thread;
	int i;
	
	if(pthread_mutex_init(&lock,NULL) !=0) {
		printf("\nErreur d'initialisation de mutex\n");	
	}					
	
				
	
	nouveau_Thread = pthread_create(&my_thread, NULL,aleatoire_thread,(void*)compteur);
	if (nouveau_Thread != 0)
	{
	fprintf(stderr, "Erreur de creation du thread");
	exit (1);
	}
	

	
	pthread_join(my_thread, NULL); /* on attend la fin du thread */

	pthread_mutex_destroy(&lock);
  	
}

void *classement_thread(void *arg){
	
		int s1,s2,s3;
		int i,t,addr,dec3;

		
		int compteur=(int)arg;

		if(compteur<=nbPos-1) {
    	affiche_classement(tour);
 
		}
		
    	pthread_exit(NULL); /* termine le thread ecriture proprement */		
       		      
      
}

int creer_un_thread_classement(void)
{
	
	int nouveau_Thread;
	pthread_t my_thread;
	int i;
	
	/* on cree le thread */	
	
	nouveau_Thread = pthread_create(&my_thread, NULL,classement_thread,(void*)compteur);
	if (nouveau_Thread != 0)
	{
	fprintf(stderr, "Erreur de creation du thread lecture");
	exit (1);
	}
	
	
	pthread_join(my_thread, NULL); /* on attend la fin du thread */
  
}
void *pilote_thread(void *arg)
		{
		int s1,s2,s3;
		time_t t1;
		int addr,i,nbsec;
		int compteur=(int)arg;
		int dec1,dec2,dec3;
	
			pthread_mutex_lock(&lock);
			creer_un_thread_aleatoire();
			pthread_mutex_unlock(&lock);
			for(compteur=0;compteur<=nbPos-1;compteur++) {

						nbsec = rand()%15; /* on random entre 0 et 15 secondes de différence que peut avoir deux voitures par tour*/				
      				dec1 = rand()%899 + 100;			// Génération seconde jusque millième s3
      				dec2 = rand()%899 + 100;			// Génération seconde jusque millième s2
        				dec3 = rand()%899 + 100;			// Génération seconde jusque millième s3 (fin tour)
     					s1 = nbsec+1;
						//sleep(1/2);
						s2 = nbsec+3;
						//sleep(1/2);
						s3 = nbsec;
						//sleep(1/2);
						//sleep(1/10);
						addr= 40+nbsec;
						//sleep(1);	
							
						tbPilote[compteur].s1=(int*)s1;		
						tbPilote[compteur].s2=(int*)s2;		
						tbPilote[compteur].s3=(int*)s3;			
						tbPilote[compteur].lapTime=(int*)addr;  
						tbPilote[compteur].deci=(int*)dec3;  
						tbPilote[compteur].bestLap=tbPilote[compteur].lapTime;
						tbPilote[compteur].bestDeci=tbPilote[compteur].deci;
				}
						tour++;
						pthread_mutex_lock(&lock);
						creer_un_thread_classement();
						pthread_mutex_unlock(&lock);
					
						pthread_exit(NULL); /* termine le thread ecriture proprement */		
       		      
      
				
}

int creer_un_thread_pilote(void)
{
	
	int nouveau_Thread;
	pthread_t my_thread;
	int i;
	
	if(pthread_mutex_init(&lock,NULL) !=0) {
		printf("\nErreur d'initialisation de mutex\n");	
	}					
	
				
	
	nouveau_Thread = pthread_create(&my_thread, NULL,pilote_thread,(void*)compteur);
	if (nouveau_Thread != 0)
	{
	fprintf(stderr, "Erreur de creation du thread");
	exit (1);
	}
	

	
	pthread_join(my_thread, NULL); /* on attend la fin du thread */

	pthread_mutex_destroy(&lock);
  	
	
	
	// rajouter un sleep pour permettre au (futur) thread classement d'afficher le classement
	
}

void course(){


 for(compteur=0;compteur<nbPos;compteur++) { 					
 creer_un_thread_pilote();  						
 }
  
 }
		
void menu(){
  
    int choix;
    int tour; // nb de tour de la course (20)

    printf("             *******************************\n");
    printf("             *           BELGIUM           *\n");
    printf("             *        SPA | 24 AOUT        *\n");
    printf("             *******************************\n\n");
  
 	 printf("Course   Dim 14:00 - 16:00       ~     Longueur totale de la course  308.052 km\n");
    printf("Meteo du WE  Ensoleillee(sec)    ~     Temps record  1:39.896 - (2009) S. Vettel\n\n");
  
    printf("\nAppuyer sur ENTER pour continuer...\n");
    getchar();
 	 grilleDepart();
   
  
    while(choix < 1 || choix > 2)
		{

			printf("\n<1> Démarrer la course  <2> Quitter\n");
			printf("Choix: ");			
			scanf("%d",&choix);
			
			switch(choix)
				{
					case 1:
						{
							
							
							system("clear");
							 for(tour=0;tour<=20;tour++) {
                      course();
                     }//sleep(2);                      
                      //system("clear");}
							 break;
						}
					case 2:
						{
							system("clear");
             			printf("             *******************************\n");
    						printf("             *           SORTIE            *\n");
    						printf("             *       DU PROGRAMME          *\n");
    						printf("             *******************************\n\n");
                     sleep(2);
							exit(0);
							break;
						}
					default:
						{
							printf("Choix incorrect, entrer 1 ou 2 ! Essayer de nouveau...\n");
							break;
						
						}
				} /*fin du switch */
		} /* fin du while */
}




/*Appel de la fonction menu()*/

int main() {
  fileGet(); // récupération du classement de départ	
  menu();
 
  return 0;
}