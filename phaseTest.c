/**tableau avec numéro du pilote
*meilleur temps segment 1
    placer le meilleur temps
*meilleur temps segment 2
*meilleur temps segment 3
*meilleur temps total
  additionner les 3 meilleurs segments
*tour 1
*tour 2
*tour 3
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double random_number(double min_num, double max_num);



      double random_number(double min_num, double max_num)
        {
            int result=0,low_num=0,hi_num=0;
            if(min_num<max_num)
            {
                low_num=min_num;
                hi_num=max_num+1; // this is done to include max_num in output.
            }else{
                low_num=max_num+1;// this is done to include max_num in output.
                hi_num=min_num;
            }
            srand(time(NULL));
            result = (rand()%(hi_num-low_num))+low_num;
            return result;
        }
int main(){
	int voiture = 22;

	double segment1=random_number(2.00,50.00);
	double segment2=random_number(0,150);
	double segment3=random_number(0,300);


	//etats
    int stand[2];
    stand[0]="false";//faux
    stand[1]="true";//vrai

    if(stand[0]=="false"){
        printf("encore sur le circtuit");
    }else if(stand[1]=="true"){
        printf("arreté au stand");
    }

    int tableau[5], i=0;

    tableau[0]=voiture;
    tableau[1]=sizeof(segment1);
    tableau[2]=segment2;
    tableau[3]=segment3;
    tableau[4]=(segment1+segment2+segment3);

    printf("\ntableau des resultats :\n");
    printf("-----------------------\n");
    printf("| n  | s1 | s2 | s3 | t.t.\n");
    printf("==========================\n");
        for (i = 0 ; i < 5 ; i++)
    {
        printf("| %d ", tableau[i]);

    }
}
