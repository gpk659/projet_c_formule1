/**
* @author : grégory
* test d'une création d'un thread pour la mémoire partagée.
**/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* parameter){
	int i=0;
	for (i=0; i<5; i++){
		printf("Id : %d.\n", i);
		sleep(1);
	}
	return 0;
}

int creerPilote(void){//on crée un thread...

	int threadPilote;
	pthread_t myThread;

	threadPilote=pthread_create(&myThread,0,thread_func,0);

	if(threadPilote!=0){
		printf("Create thread failed error: %d", threadPilote);
		return 1;	
	}

	pthread_join(myThread,0);
}

int main(int argc, char **argv){

	creerPilote();

	return 0;

}
