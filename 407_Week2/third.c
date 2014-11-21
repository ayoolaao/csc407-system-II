#include	<stdlib.h>
#include	<stdio.h>

extern	char	begin;
extern	char	end;

void	printFromBeginToEnd	()
{
  char	c;

  for  (c = begin;  c <= end;  c++)
    printf("%3d\t%c\n",c,c);

}
