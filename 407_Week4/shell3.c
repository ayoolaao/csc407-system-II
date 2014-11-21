#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#include	<signal.h>
#include	<wait.h>

#define		MAX_LINE	256

void	sigChldHandler	(int	signal
			)
{
  pid_t pid;
  int   status;

  while( (pid=waitpid(-1,&status,WNOHANG)) > 0)
    if  (WIFEXITED(status) != 0)
      printf("%d returned %d\n",pid,WEXITSTATUS(status));
    else
      printf("%d crashed!\n",pid);

}


int	main	()
{
  char	line[MAX_LINE];
  // Set up struct to specify the new action.
  struct sigaction act;

  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_NOCLDSTOP | SA_RESTART;

  act.sa_handler = sigChldHandler;
               // Handle with simpleHandler()
  sigaction(SIGCHLD,&act,NULL);

  do
  {
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

  }
  while  (1);

  return(EXIT_SUCCESS);
}
