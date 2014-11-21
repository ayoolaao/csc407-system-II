#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#include	<wait.h>

#define		MAX_LINE	256

int	main	()
{
  char	line[MAX_LINE];

  printf("What program would you like to run? ");
  fgets(line,MAX_LINE,stdin);

  char*	cPtr	= strchr(line,'\n');

  if  (cPtr != NULL)
    *cPtr = '\0';

  pid_t	pid	= fork();

  if  (pid == 0)
  {
    execl(line,line,NULL);
    printf("Sorry!  I could not find %s\n",line);
    exit(EXIT_FAILURE);
  }

  int	status;

  wait(&status);
  printf("Parent hanging out for child %d\n",pid);
  return(EXIT_SUCCESS);
}
