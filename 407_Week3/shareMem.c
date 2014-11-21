#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

int	bss	= 0;
int	data	= 10;

int	main	()
{
  int	stack	= 12;
  int*	heapPtr	= (int*)malloc(sizeof(int));

  *heapPtr	= 20;

  pid_t	pid	= fork();

  if  (pid == 0)
  {
    bss++;
    data++;
    stack++;
    (*heapPtr)++;
  }
  else
  {
    bss--;
    data--;
    stack--;
    (*heapPtr)--;
  }

  printf("Process %d has bss %d, data %d, stack %d, heap %d\n",
	 getpid(),bss,data,stack,*heapPtr
	);
  return(EXIT_SUCCESS);
}
