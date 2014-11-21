/*
Yuancheng Zhang	
CSC407 Systems
HW2 - c. 
A launcher program, that asks for the number of seconds 
the student should be allowed to sleep, launches the student program, 
launches the alarm clock program, and waits for them both to end.
*/


#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<wait.h>

#define	MAX_LINE	256
#define ALARMCLOCK_PROG "alarmClock"
#define SLEEPINGSTUDENT "sleepingStudent"

int	main()
{
	

	unsigned int time;

	int numSecs;

	printf("How many seconds shall the student be allowed to sleep? ");
	fgets(secs,MAX_LINE,stdin);
	time = strtol(secs,NULL,5);
	if(time <= 0 || time >3600)
	{
		printf("Illegal seconds\n");
		return(EXIT_SUCCESS);
	}

	pid_t std_pid = fork();

	if (std_pid == 0)
	{	  
		execl(SLEEPINGSTUDENT,SLEEPINGSTUDENT,NULL);
	}

	pid_t alarm_pid = fork();
  
	if(alarm_pid == 0)
	{
		char pid[MAX_LINE];
		char secs[MAX_LINE];
		snprintf(pid,MAX_LINE,"%d",std_pid);
    	snprintf(secs,MAX_LINE,"%d",numSecs);
		execl(ALARMCLOCK_PROG,ALARMCLOCK_PROG,std_pid,time,NULL);	
	}	

	wait(NULL);
	printf("Such a good student\n");
	return(EXIT_SUCCESS);
}  
