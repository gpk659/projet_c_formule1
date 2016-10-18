//les librairies

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//declaration de toutes les variables et tableaux


//mes structures
struct Pilote {
  int pilote_id;
 double segment1,segment2,segment3;
 double tour;
  double results[5][3];
/*
 * {,,} les id des pilotes
 * {,,} le segment 1
 * {,,} le segment 2
 * {,,} le segment 3
 * {,,} le tour
 * 
 */
  
};

/*
//mes fonctions
double participant(){
}

double creerTour(){
}
//calcul des meilleurs //////temps
double meilleurSegment(){
 // 
}
double meilleurTour(){
}*/

//fonction principale qui permet de lancer le programme
int main( ) {
 struct Pilote Pilote1;
  /* specification pilote */
  //Pilote1.pilote_id=22;
	Pilote1.results[0][0]={22};
	printf("id : %d\n", Pilote1.results[0][0]);
return 0;
}
