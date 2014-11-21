#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	canSleep	= 1;

void	wakeUp	(int	sig)
{
  canSleep = 0;
}


int	main	()
{
  signal(SIGUSR1,wakeUp);

  while  (canSleep)
  {
    printf("Student: \"(snore)\"\n");
    sleep(1);
  }

  printf("Student: \"Okay, okay.  I'll wake up!\"\n");
  return(EXIT_SUCCESS);
}
