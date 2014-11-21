#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	main	(int argc, const char* argv[])
{

  if  (argc < 3)
  {
    fprintf(stderr,"Usage:\t%s <pid> <timeInSecs>\n",argv[0]);
    return(EXIT_FAILURE);
  }

  pid_t	siblingPid	= atoi(argv[1]);
  int	timeInSecs	= atoi(argv[2]);

  if  (siblingPid < 0)
  {
    fprintf(stderr,"Illegal pid.\n");
    return(EXIT_FAILURE);
  }

  if  (timeInSecs < 0)
  {
    fprintf(stderr,"Illegal number of seconds.\n");
    return(EXIT_FAILURE);
  }

  for  ( ;  timeInSecs > 0;  timeInSecs--)
  {
    int	hours	= timeInSecs / (60 * 60);
    int	mins	= (timeInSecs / 60) % 60;
    int	secs	= timeInSecs % 60;
    printf("Clock \"%02d:%02d:%02d\"\n",hours,mins,secs);
    sleep(1);
  }

  printf("Clock \"Ding! Ding! Ding!\"\n");
  kill(siblingPid,SIGUSR1);
  return(EXIT_SUCCESS);
}
