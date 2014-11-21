#include	<stdlib.h>
#include	<stdio.h>

int	main	()
{
  int i,j,n;

  n = sscanf( "10 20", "%d %d", &i,&j);

  printf("i = %d, j = %d, n = %d\n",i,j,n);
  return(EXIT_SUCCESS);
}
