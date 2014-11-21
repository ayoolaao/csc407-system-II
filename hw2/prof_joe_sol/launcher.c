#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define	MAX_LINE	256

#define	ALARMCLOCK_PROG	"alarmClock"

#define STUDENT_PROG	"sleepingStudent"


void	quit	(int	sig)
{
  printf("Problem launching student.\n");
  exit(EXIT_FAILURE);
}


int	main	()
{
  char	numText[MAX_LINE];
  int	numSecs;
  int	status;

  do
  {
    printf("How many seconds shall the student be allowed to sleep? ");
    fgets(numText,MAX_LINE,stdin);
    numSecs = atoi(numText);
  }
  while  (numSecs < 0  ||  numSecs > 60*60);

  signal(SIGCHLD,quit);

  pid_t	studentPid = fork();

  if  (studentPid < 0)
  {
    printf("Couldn't make the sleeping student process, sorry dude!\n");
    exit(EXIT_FAILURE);
  }

  if  (studentPid == 0)
  {
    execl(STUDENT_PROG,STUDENT_PROG,NULL);
    printf("Couldn't find the student program!\n");
    exit(EXIT_FAILURE);
  }

  sleep(1);
  signal(SIGCHLD,SIG_DFL);

  pid_t	clockPid	= fork();

  if  (clockPid < 0)
  {
    printf("Couldn't make the alarm clock process, sorry dude!\n");
    kill(studentPid,SIGUSR1);
    exit(EXIT_FAILURE);
  }

  if  (clockPid == 0)
  {
    char	pid[MAX_LINE];
    char	secs[MAX_LINE];

    snprintf(pid,MAX_LINE,"%d",studentPid);
    snprintf(secs,MAX_LINE,"%d",numSecs);

    execl(ALARMCLOCK_PROG,ALARMCLOCK_PROG,pid,secs,NULL);
    printf("Couldn't find the clock program!\n");
    kill(studentPid,SIGUSR1);
    exit(EXIT_FAILURE);
  }
  
  wait(&status);
  wait(&status);
  printf("Such a good student!\n");   
  return(EXIT_SUCCESS);
}

