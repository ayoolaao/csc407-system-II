/*

Yuancheng Zhang	
CSC407 Systems
HW2 - b. 
An alarm clock program, that is given the process id of 
the student and how many seconds the student is allowed to sleep. 
It counts the second down until reaching 0, 
then sends SIGUSR1 to the student.;

*/


#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>

#define		MAX_LINE	256


int	shouldContinue	= 1;

void	sigAlarmHandler	(int	signal)
{
  shouldContinue	= 0;
}

int	main	(int argc,char *argv[], char *envp[])
{
  // check pid
  pid_t pid = (pid_t)strtol(argv[1],NULL,10);
  if(pid <= 0){
    printf("Illegal pid.\n");
    exit(EXIT_FAILURE);
  }

  // chech second
  unsigned int time = strtol(argv[2],NULL,10);
  if (time <= 0){
    printf("Illegal number of seconds.\n");
    exit(EXIT_FAILURE);
  }

  //printf("pid: %d, time: %d\n", pid, time);

  // Set up struct to specify the new action.
  struct sigaction act;

  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO | SA_RESTART;
  act.sa_handler = sigAlarmHandler;
  sigaction(SIGALRM,&act,NULL);

  alarm(time);
  
  
  while  (shouldContinue)
  { 
    int second = alarm(0);
    printf("Clock \"%02d:%02d:%02d\"\n",
            second/3600, (second%3600)/60, second%60);
    alarm(second);   
    sleep(1);

  }

  kill(pid, SIGUSR1);
  printf("Clock \"Ding!  Ding!  Ding!\"\n");
  return(EXIT_SUCCESS);
}  








