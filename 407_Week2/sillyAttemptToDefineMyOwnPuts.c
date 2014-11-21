#include	<stdlib.h>
#include	<stdio.h>

int	puts	(const char*	cPtr)
{
  int	i = printf("%s\n",cPtr);

  return(i);
}


int	main	()
{
  puts("Hello world!");
  return(EXIT_SUCCESS);
}
