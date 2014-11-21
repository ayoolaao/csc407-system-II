#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include	<unistd.h>

#define		MAX_LINE	16


void	sigChildhandler
		(int		signal,
		 siginfo_t*	infoPtr,
		 void*		dataPtr
		)
{
  if  (getppid() == (*infoPtr).si_pid)
    printf("Hee hee, that tickles!\n");
  else
    printf("Keep your hands to yourself, MISTER!\n");
}


void	installSigChildHandler	()
{
  struct sigaction sa;
  memset(&sa,'\0',sizeof(struct sigaction));
  sigemptyset(&sa.sa_mask );

  sa.sa_flags= SA_SIGINFO //Install sa_sigaction
                          // (as opposed to
                          //  sa_handler)
             | SA_RESTART;//If interrupted in
                          // sys call then
                          // restart sys call
                          // after signal handler

  sa.sa_sigaction = sigChildhandler;
  sigaction(SIGINT, &sa, NULL);
}

void	doChild	()
{
  installSigChildHandler();

  while  (1)
    sleep(1);
}


int	main	()
{
  pid_t	childId	= fork();

  if  (childId == 0)
  {
    doChild();
    exit(EXIT_SUCCESS);
  }

  int	i;
  char	line[MAX_LINE];

  printf("The PID of the child is %d\n",childId);

  for  (i = 0;  i < 4;  i++)
  {
    printf("Press enter to tickle child:\n");
    fgets(line,MAX_LINE,stdin);
    kill(childId,SIGINT);
  }

  kill(childId,SIGKILL);
  return(EXIT_SUCCESS);
}
