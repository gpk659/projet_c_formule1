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
int partie; //   pour classer les pilotes selon la scéances d'essai 1,2,3 ou qualif
int passage; // passage est pour les qualifs
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



/*Définitions de tout les pilotes par : TEAM | Numéro de voiture | Nationalité | Prénom | Nom*/

  
  t_pilote tbPilote[nbPos]={
    
    {"RedBull   ",1,"GER","Sebastian","Vettel",1,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"RedBull   ",3,"AUS","Daniel","Ricciardo",2,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Mercedes   ",44,"ENG","Lewis","Hamilton",3,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Mercedes   ",6,"GER","Nico","Rosberg",4,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Ferrari    ",14,"SPA","Fernando","Alonso",5,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Ferrari    ",7,"FIN","Kimi","Raikkonen",6,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Lotus      ",8,"FRA","Romain","Grosjean",7,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Lotus      ",13,"EQU","Pastor","Maldonado",8,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"McLaren    ",22,"ENG","Jenson","Button",9,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"McLaren    ",20,"AUT","Kevin","Magnussen",10,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"ForceIndia",27,"GER","Nico","Hulkenberg",11,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"ForceIndia",11,"MEX","Sergio","Perez",12,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Sauber     ",99,"GER","Adrian","Sutil",13,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Sauber     ",21,"MEX","Esteban","Gutierrez",14,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"ToroRosso ",25,"FRA","Jean-Eric","Vergne",15,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"ToroRosso ",26,"RUS","Daniil","Kvyat",16,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Williams   ",19,"BRA","Felipe","Massa",17,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Williams   ",77,"FIN","Valtteri","Bottas",18,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Marussia   ",17,"FRA","Jules","Bianchi",19,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Marussia   ",4,"ENG","Max","Chilton",20,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Caterham   ",10,"JAP","Kamui","Kobayashi",21,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {"Caterham   ",9,"SWE","Marcus","Ericsson",22,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
     
    };
   





int fonction_tri(const void *a, const void *b){

		t_pilote *i1 = (t_pilote *)a;
		t_pilote *i2 = (t_pilote *)b;
		
		if((i1->lapTime - i2->lapTime)==0){
		return(i1->deci - i2->deci);
		}else{return(i1->lapTime - i2->lapTime);}
				
}

int fonction_diff_lap(const void *a, const void *b){

		t_pilote *i1 = (t_pilote *)a;
		t_pilote *i2 = (t_pilote *)b;
		
		
		return(i1->lapTime - i2->lapTime);
	
				
}


/*Affichage du tableau trié des pilotes donc le classement*/

void affiche_classement(){
	
	int nbClasses= 22; // ou 22

	/*Viens ensuite l'affichage; l'enregistrement dans un fichier se fera juste 
		après le tri pour avoir la grille de départ de la course*/

	printf("         ****************************************************************\n");
	printf("         *                         CLASSEMENT 	                        *\n");
	printf("         *     POSITION    |        BEST LAP         |      PILOTE      *\n");
	printf("         ****************************************************************\n");
	if(partie==4){ 
		if(passage==1) {
		qsort(tbPilote,nbPos,sizeof(tbPilote[nbPos]),fonction_tri); // tri du tableau par qsort
	
		for(compteur=0; compteur<nbClasses;compteur++) {
			if(compteur <= 9) {
			printf("               [%d]            [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else {	printf("               [%d]           [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
	}
			printf("         ****************************************************************\n\n");
	}

     }else if(passage==2) {      // fin Q1
     	qsort(tbPilote,15,sizeof(tbPilote[nbPos-8]),fonction_tri); // tri du tableau par qsort
	
    	for(compteur=0; compteur<=14;compteur++) {
			if(compteur <= 9) {
			printf("               [%d]            [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else {	printf("               [%d]           [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
	}
			printf("         ****************************************************************\n\n");
	}
     } else if(passage==3) { // fin Q2
      qsort(tbPilote,10,sizeof(tbPilote[nbPos-13]),fonction_tri); // tri du tableau par qsort
	
     	for(compteur=0; compteur<=9;compteur++) {
			if(compteur <= 9) {
			printf("               [%d]            [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else{	printf("               [%d]           [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
	}
			printf("         ****************************************************************\n\n");
}
} // fin Q3
}

else{
	   	qsort(tbPilote,nbPos,sizeof(tbPilote[nbPos]),fonction_tri); // tri du tableau par qsort
	for(compteur=0; compteur<nbClasses;compteur++) {
			if(compteur <= 9) {
			printf("               [%d]            [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
		} else {	printf("               [%d]           [1'%d.%d]             [%s %s]     \n",compteur+1,(int)tbPilote[compteur].lapTime,(int)tbPilote[compteur].deci,tbPilote[compteur].prenom,tbPilote[compteur].nom);
	}
			printf("         ****************************************************************\n\n");
}}

}

/*Affiche le temps enregistré du pilote*/

void affiche_temps(int a){
	int nbClasses= sizeof(tbPilote[nbPos])/sizeof(tbPilote[0]); // ou 22
	int i;	
	i=a;
	int n;// savoir quand on est au max de tour

	                 					
							printf("             **********************************************************\n");
							printf("             *               CLASSEMENT                               *\n");
							printf("             *   LAP TIME       | DIFF PREVIOUS LAP      | BEST LAP   *\n");
							printf("             **********************************************************\n");
							printf("             *   [1'%d.%d]      |      [+0.00]           | [1'%d.%d]*\n",(int)tbPilote[i].lapTime,(int)tbPilote[i].deci,(int)tbPilote[i].bestLap,(int)tbPilote[i].bestDeci);
							printf("             **********************************************************\n\n");	
						
	

}

void affiche_pilotes(){
	
	printf("             *********************************\n");
   printf("             *          GRILLE 2014          *\n");
   printf("             *      TEAM | Car | Pilotes     *\n");
   printf("             *********************************\n\n");
	int nbPilotes= sizeof(tbPilote)/sizeof(tbPilote[0]);
	int i;
	for(i=0;i<nbPilotes;i++){
		if(tbPilote[i].numVoiture < 10) {   // Condition if uniquement pour l'affichage
   	printf(" %s            %d         %s   %s [%s]\n",tbPilote[i].team,tbPilote[i].numVoiture,tbPilote[i].prenom,tbPilote[i].nom, tbPilote[i].nat);	
   	} else {printf(" %s            %d        %s   %s [%s]\n",tbPilote[i].team,tbPilote[i].numVoiture,tbPilote[i].prenom,tbPilote[i].nom, tbPilote[i].nat);	
   	}
	}

} 	

// affiche la différence de temps par tour

int fonction_diff_Sec(const void *a, const void *b){

		t_pilote *i1 = (t_pilote *)a;
		t_pilote *i2 = (t_pilote *)b;
	
	   return(i1[compteur].bestLap - i2[compteur].bestLap);
				
}

int fonction_diff_Dec(const void *a, const void *b){

		t_pilote *i1 = (t_pilote *)a;
		t_pilote *i2 = (t_pilote *)b;
	
	   return(i1[compteur].deci - i2[compteur].deci);
				
}
// compare 2 temps

int fonction_bestLap(const void *a, const void *b){

		t_pilote *i1 = (t_pilote *)a;
		t_pilote *i2 = (t_pilote *)b;
		
		if((i1[compteur].bestLap - i2[compteur].bestLap)==0){
		return(i1[compteur].deci - i2[compteur].deci);
		}else{return(i1[compteur].bestLap - i2[compteur].bestLap);}
		
}
void swap(int *a, int *b){
	
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;

}

// fonction d'enregistrement d'un fichier du classement final des qualifs.

void fileRecord(){

f=fopen(NOM,"rt+");
if(f==NULL) {
f=fopen(NOM,"wt+"); 
 }
if(f==NULL) {
printf("Erreur de création de fichier");
getchar();
exit(1);
}

printf("Appuyer sur enter pour enregistrer le classement final dans le fichier classement.txt...\n\n");
getchar();
for(compteur=0;compteur<=nbPos-1;compteur++) {
fprintf(f,"%s %d %s %s %s \n",tbPilote[compteur].team,tbPilote[compteur].numVoiture,tbPilote[compteur].nat,tbPilote[compteur].prenom,tbPilote[compteur].nom);
}
sleep(1);

printf("Enregistremen terminé!");
sleep(1);
system("clear");
fclose(f);

}

void *classement_thread(void *arg){
		int s1,s2,s3;
		int i,t,addr,dec3;

		
		int compteur=(int)arg;
		
		

		sleep(1);
		if(partie==4) {
					
	
		if(passage==1) {
		if(compteur==nbPos-1) {

		printf("\n           ****************************************************\n");
    	printf("             *   La premiere sceance de qualif est terminee     *\n");
        printf("             ****************************************************\n\n");
    	printf("\nAppuyer sur ENTER pour afficher le classement de la Q1\n");
    	getchar();
    	affiche_classement();
    	printf("\nAppuyer sur ENTER pour afficher le classement définitif de la Q1\n");
    	getchar();
    	printf("Pilote elimine en Q1:\n\n");
    	for(compteur=15;compteur<=21;compteur++){
      	printf("[%d] [%s] [%s]\n",compteur+1,tbPilote[compteur].prenom,tbPilote[compteur].nom)	;
    	}
    	printf("\n\nPilote encore en course pour la Q2:\n\n");
    	for(compteur=0;compteur<=14;compteur++) {
    	printf("[%d] [%s] [%s]\n",compteur+1,tbPilote[compteur].prenom,tbPilote[compteur].nom)	;
    
    	}
		printf("\nAppuyer sur ENTER pour continuer\n");
    	getchar();
    	system("clear");
		}
		} else if(passage==2) {
		if(compteur==14) {
		printf("\n           ****************************************************\n");
    	printf("             *   La deuxieme sceance de qualif est terminee     *\n");
        printf("             ****************************************************\n\n");
    	printf("\nAppuyer sur ENTER pour afficher le classement de la Q2\n");
    	getchar();
    	affiche_classement();
   	printf("\nAppuyer sur ENTER pour afficher le classement définitif de la Q2\n");
    	getchar();
    	 printf("Pilote elimine en Q2:\n\n");
    	for(compteur=10;compteur<=14;compteur++){
    
    	printf("[%d] [%s] [%s]\n",compteur+1,tbPilote[compteur].prenom,tbPilote[compteur].nom)	;
    	}
    	printf("\n\nPilote encore en course pour la Q3:\n\n");
    	for(compteur=0;compteur<=9;compteur++){
 
    	printf("[%d] [%s] [%s]\n",compteur+1,tbPilote[compteur].prenom,tbPilote[compteur].nom)	;
    	}
 		
    	printf("\nAppuyer sur ENTER pour continuer\n");
    	getchar();
    	system("clear");
		}
	}else if(passage==3)  {
		if(compteur==9) {
	    printf("\n           ****************************************************\n");
    	printf("             *   La troisieme sceance de qualif est terminee     *\n");
        printf("             ****************************************************\n\n");
    	printf("\nAppuyer sur ENTER pour afficher le classement de la Q3\n");
    	getchar();
    	printf("\nAppuyer sur ENTER pour afficher le classement définitif de la Q3\n");
    	getchar();
    	affiche_classement();
    	for(compteur=0;compteur<=9;compteur++){
    	printf("[%d] [%s] [%s]\n",compteur+1,tbPilote[compteur].prenom,tbPilote[compteur].nom)	;
      	
    	}
   	printf("\nAppuyer sur ENTER pour afficher le classement définitif de la pour la course\n");
    	getchar();
    	for(compteur=0;compteur<=nbPos-1;compteur++){ 
    	printf("[%d] [%s] [%s]\n",compteur+1,tbPilote[compteur].prenom,tbPilote[compteur].nom)	;
      	
    	}
    	fileRecord();
		}
	}
	
	}
	else {
		if(compteur==nbPos-1) {
    	printf("\n             *******************************************\n");
    	printf("             *   La sceance d'ESSAI %d est terminee     *\n",partie);
      printf("             *******************************************\n\n");
    	printf("\nAppuyer sur ENTER pour afficher le classement des pilotes de l'ESSAI %d...\n",partie);
    	getchar();
    	affiche_classement();
    
 		} 
 		 }
   	
    
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
/*Définition du thread PAR 3 étapes secteur1 = s1; secteur2 = s2; secteur3 = s3:*/

void *pilote_thread(void *arg)
		{
		int s1,s2,s3;
		time_t t1;
		int addr,i,nbsec;
		int compteur=(int)arg;
		int dec1,dec2,dec3;
		int diffSec,diffDec;
		int t;
		int nbTour;
		int evnt=1;
	

	
		/*Affichage avec 3 chiffres de précisions grâce au tant que*/   
		
			t=1;
			nbTour = rand()%2+1; // on random le nombre de tour ( au moins 1)				
     			 
			do {		
						if(evnt==0){
						evnt=1;     					
     					}else if(evnt==1){
							evnt=0;     					
     					}	
							

						nbsec = rand()%15; /* on random entre 0 et 15 secondes de différence que peut avoir deux voitures par tour*/
					
      				dec1 = rand()%899 + 100;			// Génération seconde jusque millième s3
      			
      		
      				dec2 = rand()%899 + 100;			// Génération seconde jusque millième s2
      	
      			
      				dec3 = rand()%899 + 100;			// Génération seconde jusque millième s3 (fin tour)
      		
						s1 = nbsec+1;
						//sleep(1/2);
						printf("Secteur 1: %d.%d secondes!\n", 30 + s1,dec1);
			
						s2 = nbsec+3;
						//sleep(1/2);
						if(s2<100) {
						printf("Secteur 2: 1'0%d.%d secondes!\n",s2,dec2);      // Condition if uniquement pour l'affichage
	   				} else { printf("Secteur 2: 1'%d.%d secondes!\n",s2,dec2);}
					
		
						s3 = nbsec;
						//sleep(1/2);
						printf("Secteur 3 et fin du tour: 1'%d.%d secondes!\n", 40 + s3,dec3);
						//sleep(1/10);
						printf("Lap time : 1'%d.%d secondes\n\n", 40+nbsec,dec3);
						addr= 40+nbsec;
						//sleep(1);	
						
						
						
					
						tbPilote[compteur].s1=(int*)s1;		
						tbPilote[compteur].s2=(int*)s2;		
						tbPilote[compteur].s3=(int*)s3;			
						tbPilote[compteur].lapTime=(int*)addr;  
						tbPilote[compteur].deci=(int*)dec3;  
						tbPilote[compteur].bestLap=tbPilote[compteur].lapTime;
						tbPilote[compteur].bestDeci=tbPilote[compteur].deci;
						tbPilote[compteur].nbTour=(int*) nbTour;			
						
						affiche_temps(compteur);
						//sleep(1/2);
				
						t++;		
						
						}while(t<=(int)tbPilote[compteur].nbTour);
						if(evnt==0){
							printf("%s %s   Car[%d] a roule %d tour !\nA la fin de son tour, il a ete victime d'un probleme moteur et a du abandonne la sceance.\n\n",tbPilote[compteur].prenom,tbPilote[compteur].nom,tbPilote[compteur].numVoiture,(int)tbPilote[compteur].nbTour); 	
										
						}else{printf("%s %s   Car[%d] a roule %d tour !\nLa team %s semble plutot satisfait de cette %d partie de week-end.\n\n",tbPilote[compteur].prenom,tbPilote[compteur].nom,tbPilote[compteur].numVoiture,(int)tbPilote[compteur].nbTour,tbPilote[compteur].team,partie); 	
						} 
						
						//On bloque le thread ecriture pour pouvoir lire les données écrites
						pthread_mutex_lock(&lock);
						creer_un_thread_classement();
						pthread_mutex_unlock(&lock);
			
						pthread_exit(NULL); /* termine le thread ecriture proprement */		
       		      
      
				
}
		
		

/*C'est ici que va se créer les threads et le temps aléatoire*/

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
// scéance de qualif

void qualif(){
						
 						int nbPilotes= sizeof(tbPilote)/sizeof(tbPilote[0]);
						int i;
						
						partie=4;
			
							passage=1; // pour Q1      
							system("clear");
							printf("             **********************************\n");
   						printf("             *       QUALIF 14:00 - 14:20     *\n");
    						printf("             *        SPA | SAM 23 AOUT       *\n");
   						printf("             **********************************\n\n");
						       
                     for(compteur=0;compteur<=nbPos;compteur++){     						
    						printf("[Q1] Signal de départ du concurrent %d ...  Taper Enter\n\n",compteur+1);
    						getchar();
    						printf("%s %s   Car[%d] commence son tour !\n\n",tbPilote[compteur].prenom, tbPilote[compteur].nom, tbPilote[compteur].numVoiture);  						
    						creer_un_thread_pilote();
    						
    						}
     						passage=2;
     						system("clear");
							printf("             **********************************\n");
   						printf("             *       QUALIF 14:20 - 14:35     *\n");
    						printf("             *        SPA | SAM 23 AOUT       *\n");
   						printf("             **********************************\n\n");
						
    						for(compteur=0;compteur<=14;compteur++){
    						printf("[Q2] Signal de départ du concurrent %d ...  Taper Enter\n\n",compteur+1);
    						getchar();
    						printf("%s %s   Car[%d] commence son tour !\n\n",tbPilote[compteur].prenom, tbPilote[compteur].nom, tbPilote[compteur].numVoiture);  						
    						creer_un_thread_pilote();
    						}
 		
    						passage=3;
    						system("clear");
							printf("             **********************************\n");
   						printf("             *       QUALIF 14:35 - 14:45     *\n");
    						printf("             *        SPA | SAM 23 AOUT       *\n");
   						printf("             **********************************\n\n");
						
    						for(compteur=0;compteur<=9;compteur++){
    						printf("[Q3] Signal de départ du concurrent %d ...  Taper Enter\n\n",compteur+1);
    						getchar();
    						printf("%s %s   Car[%d] commence son tour !\n\n",tbPilote[compteur].prenom, tbPilote[compteur].nom, tbPilote[compteur].numVoiture);  						
    						creer_un_thread_pilote();
    						}
    				
							printf("\n\nAppuyer sur ENTER pour continuer...");
							getchar();
							system("clear");
							printf("Nous remercions tous nos spectateurs d'avoir suivi cette permière partie de Week-end riche en émotions.\nRendez-vous donc demain pour la mythique course de Spa Francorchamps!\n\n");
							printf("Présenté par de Bellefroid Clément, Vander Stappen Benoît et Cap Sébastien.\n\n");
							printf("\n\nAppuyer sur ENTER pour quitter...");
							getchar();
							exit(0);
							
}

/*Toutes la scéances d'essai avec choix multiples 
(Lancer les scéances d'essais ; Lancer qualif directement ; ou quitter)*/

void essai(){
    int nbPilotes= sizeof(tbPilote)/sizeof(tbPilote[0]);
	 int i;
	 int choix1;
	 int choix2;
	 int choix3;
	 int choix4;
    int *classement[23];	
    passage=1;
	 system("clear");
    printf("             *****************************\n");
    printf("             *      Sceance d'essai      *\n");
    printf("             *****************************\n\n");
    
    
    while(choix1 <1 || choix1 >3)
		{
			
			printf("\n\n\n<1> Lancer la premiere sceance d'essai\n<2> Lancer directement les Qualifs\n<3> Quitter \n");
			printf("Choix: ");			
			scanf("%d",&choix1);
	 
			
			switch(choix1)
				{
					case 1:
						{
							
							partie=1;	
							passage=1;					
							system("clear");
							printf("             **********************************\n");
   						printf("             *      ESSAI 1 10:00 - 11:30     *\n");
    						printf("             *        SPA | VEN 22 AOUT       *\n");
   						printf("             **********************************\n\n");
                     for(compteur=0;compteur<nbPos;compteur++){
    						printf("Signal de départ du concurrent %d ...  Taper Enter\n\n",compteur+1);
    						getchar();
    						printf("%s %s   Car[%d] commence son tour !\n\n",tbPilote[compteur].prenom, tbPilote[compteur].nom, tbPilote[compteur].numVoiture);  						
											
    						creer_un_thread_pilote();						
    						}
						partie++;
						break;
							
						}
							
					case 2:
						{
							system("clear");
						
							qualif();
					
								break;
						}
						
					
					case 3:
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
							printf("Choix incorrect,entrer 1 , 2 ou 3 ! Essayer de nouveau...\n");
						
							break;
						}
						
				} /*fin du switch */
		} /* fin du while */ 
		
		
     while(choix2 <1 || choix2 >3)
		{
			
			printf("\n\n\n<1> Lancer la deuxieme sceance d'essai\n<2> Lancer directement les Qualifs\n<3> Quitter \n");
			printf("Choix: ");
			scanf("%d",&choix2);

			switch(choix2)
				{
					case 1:
						{
							partie=2;
							passage=1;
							system("clear");
							printf("             **********************************\n");
   						printf("             *      ESSAI 2 14:00 - 15:30     *\n");
    						printf("             *        SPA | VEN 22 AOUT       *\n");
   						printf("             **********************************\n\n");
                  	    for(compteur=0;compteur<nbPos;compteur++){
    						printf("Signal de départ du concurrent %d ...  Taper Enter\n\n",compteur+1);
    						getchar();
    						printf("%s %s   Car[%d] commence son tour !\n",tbPilote[compteur].prenom, tbPilote[compteur].nom, tbPilote[compteur].numVoiture);
    						creer_un_thread_pilote();
							}
    						
    					partie++;
    						break;
						}
					case 2:
						{
							system("clear");
						
							qualif();
							
							break;
						}
					
					case 3:
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
							printf("Choix incorrect,entrer 1 , 2 ou 3 ! Essayer de nouveau...\n");
							break;
						
						}
				} /*fin du switch */
		} /* fin du while */ 
    
    
    
    while(choix3 <1 || choix3 >3)
		{
			
			printf("\n\n\n<1> Lancer la troisieme sceance d'essai\n<2> Lancer directement les Qualifs\n<3> Quitter \n");
			printf("Choix: ");			
			scanf("%d",&choix3);
		
			switch(choix3)
				{
					case 1:
						{
							partie=3;
							
							system("clear");
							printf("             **********************************\n");
   						printf("             *      ESSAI 3 11:00 - 12:00     *\n");
    						printf("             *        SPA | SAM 22 AOUT       *\n");
   						printf("             **********************************\n\n");
               		    for(compteur=0;compteur<nbPos;compteur++){
    						printf("Signal de départ du concurrent %d ...  Taper Enter\n\n",compteur+1);
    						getchar();
    						printf("%s %s   Car[%d] commence son tour !\n",tbPilote[compteur].prenom, tbPilote[compteur].nom, tbPilote[compteur].numVoiture);
    						creer_un_thread_pilote();
							}
    						
    						partie++;
							break;
						}
					case 2:
						{
							system("clear");
							for(passage=1;passage<=3;passage++) {
							qualif(passage);
						}
							break;
						}
					
					case 3:
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
							printf("Choix incorrect,entrer 1 , 2 ou 3 ! Essayer de nouveau...\n");
							break;
						
						}
				} /*fin du switch */
		} /* fin du while */ 

    
   

while(choix4 < 1 || choix4 > 2)
		{
			
			printf("\n\n\n<1> Passer au Qualifs  <2> Quitter\n");
			printf("Choix: ");			
			scanf("%d",&choix4);
			
			switch(choix4)
				{
					case 1:
						{
							system("clear");
                    for(passage=1;passage<=3;passage++) {
							qualif(passage);
						}
                  	
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
							printf("Choix incorrect,entrer 1 ou 2 ! Essayer de nouveau...\n");
							break;
						
						}
				} /*fin du switch */
		} /* fin du while */  
} 


/*Interface de démarrage*/

void menu(){
  
    int choix;

    printf("             *******************************\n");
    printf("             *           BELGIUM           *\n");
    printf("             *      SPA | 22 - 24 AOUT     *\n");
    printf("             *******************************\n\n");
  
    printf("Essai 1  Ven 10:00 - 11.30       ~     Circuit de Spa-Francorchamps\n");
    printf("Essai 2  Ven 14:00 - 15:30       ~     Premier Grand prix  1950    \n");
    printf("Essai 3  Sam 11:00 - 12:00       ~     Nombre de tours  44\n");
    printf("Qualif   Sam 14:00 - 15:00       ~     Longueur du circuit  7.004 km\n");
    printf("Course   Dim 14:00 - 16:00       ~     Longueur totale de la course  308.052 km\n");
    printf("Meteo du WE  Ensoleillee(sec)    ~     Temps record  1:47.263 - (2009) S. Vettel\n\n");
  
    printf("\nAppuyer sur ENTER pour continuer...\n");
    getchar();
    affiche_pilotes();
   
  
    while(choix < 1 || choix > 2)
		{

			printf("\n<1> Démarrer le week-end  <2> Quitter\n");
			printf("Choix: ");			
			scanf("%d",&choix);
			
			switch(choix)
				{
					case 1:
						{
							system("clear");
                            essai();
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
		
  menu();
 
  return 0;
}