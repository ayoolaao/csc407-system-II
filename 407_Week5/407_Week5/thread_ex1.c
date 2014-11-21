/* Compile with:
 * gcc -lpthread thread_ex1.c -o thread_ex1 
 */

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <sys/types.h>

 const int N = 2;

/* thread routine */
 void *thread_routine(void *vargp) 
 {
 	int id = *(int*)vargp;
 	char* ptr;
 	printf("Hello from child thread %d\n", id); 
 	switch (id)
 	{
 		case 0: ptr = strdup("Hello "); break;
 		case 1: ptr = strdup("there!"); break;
 	}
 	return((void*)ptr);
 }

 int main() 
 {
 	int i;
 	char* msgPtr;
 	pthread_t tid[N];
 	for (i = 0; i < N; i++) 
 		pthread_create
 			(&tid[i], NULL, 
 				thread_routine, (void *)&i);
 	for (i = 0; i < N; i++) {
 		pthread_join(tid[i], (void**)&msgPtr); 
 		puts(msgPtr);
 		free(msgPtr);
 	}

 	return(0); 
 }
