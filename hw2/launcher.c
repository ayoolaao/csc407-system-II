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
	
	char line[MAX_LINE];

	int numSecs;

	printf("How many seconds shall the student be allowed to sleep? ");
	fgets(line,MAX_LINE,stdin);
	numSecs = strtol(line,NULL,10);
	printf("%d\n", numSecs );
	if(numSecs <= 0 || numSecs > 3600)
	{
		printf("Illegal seconds\n");
		exit(EXIT_FAILURE);
	}

	// student
	pid_t std_pid = fork();

	if (std_pid == 0)
	{	 
		printf("pid: %d, numSecs: %d\n", std_pid, numSecs); 
		execl(SLEEPINGSTUDENT,SLEEPINGSTUDENT,NULL);
	}

	// alarm
	pid_t alarm_pid = fork();

	if(alarm_pid == 0)
	{
		char pid[MAX_LINE];
		char secs[MAX_LINE];
		snprintf(pid,MAX_LINE,"%d",std_pid);
		snprintf(secs,MAX_LINE,"%d",numSecs);
		execl(ALARMCLOCK_PROG,ALARMCLOCK_PROG,pid,secs,NULL);	
	}	

	wait(NULL);
	printf("Such a good student\n");
	return(EXIT_SUCCESS);
}  
