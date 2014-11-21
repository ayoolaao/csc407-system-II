#include	<stdlib.h>
#include	<stdio.h>
#include	<pthread.h>

#define		N	4

int	globalVar	= 0;

int*	heapPtr;

void*	threadFnc	(void*	vPtr)
{
  printf("parameter vPtr lives at address %p\n",&vPtr);
  globalVar++;
  (*heapPtr)++;
  return(NULL);
}

int	main	()
{
  int		i;
  pthread_t	threadArray[N];

  heapPtr	= (int*)malloc(sizeof(int));

  printf("globalVar = %d\n"
	 "*heapPtr  = %d\n",globalVar,*heapPtr
	);

  for  (i = 0;  i < N;  i++)
  {
    pthread_create(&threadArray[i],NULL,threadFnc,NULL);
  }

  for  (i = 0;  i < N;  i++)
    pthread_join(threadArray[i],NULL);

  printf("globalVar = %d\n"
	 "*heapPtr  = %d\n",globalVar,*heapPtr
	);
  free(heapPtr);
  return(EXIT_SUCCESS);
}
