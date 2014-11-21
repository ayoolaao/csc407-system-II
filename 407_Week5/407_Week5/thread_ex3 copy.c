// prove that all threads use the same heap.

#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 

#define N 4

int globalVar = 0;
int* heapPtr;

void* threadFnc(void* vPtr){
	printf("parameter vPtr lives at address %p\n", &vPtr);
	globalVar++;
	(*heapPtr)++;
	return(NULL);
}

int main()
{
	int i;
	pthread_t threadArray[N];

	heapPtr = (int*)malloc(sizeof(int));

	printf("globalVar = %d\n"
		   "*heapPtr  = %d\n", globalVar, *heapPtr
			);

	for(i = 0; i < N; i++)
	{
		pthread_create(&threadArray[i], NULL, threadFnc, NULL);
	}

	for(i = 0; i < N; i++)
	{
		pthread_join(threadArray[i],NULL);
	}

	printf("globalVar = %d\n"
		   "*heapPtr  = %d\n", globalVar, *heapPtr
			);

	free(heapPtr);
	return(EXIT_SUCCESS);
}

/*
OUTPUT:
$ ./thread_ex3
globalVar = 0
*heapPtr  = 0
parameter vPtr lives at address 0xb7f533d0
parameter vPtr lives at address 0xb75523d0
parameter vPtr lives at address 0xb6b513d0
parameter vPtr lives at address 0xb61503d0
globalVar = 4
*heapPtr  = 4
*/

