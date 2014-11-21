#include	<stdlib.h>
#include	<stdio.h>

extern	char	begin;
extern	char	end;

#define	SIZE	4

void	enterBeginEnd	()
{
  char	array[SIZE];

  printf("Please enter a first char: ");
  fgets(array,SIZE,stdin);
  begin = array[0];

  do
  {
    printf("Please enter a second char greater than %c: ",begin);
    fgets(array,SIZE,stdin);
    end = array[0];
  }
  while  (end < begin);
}
