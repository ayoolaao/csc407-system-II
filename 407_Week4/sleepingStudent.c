/*
	Yuancheng Zhang	
	CSC407 Systems
	HW2 - a. A student program, that will sleep and sleep 
			 until he/she received SIGUSR1
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>

int canSleep;;

void wake (int signal)
{
	canSleep = 0;
}

int main()
{
	struct sigaction act;

	memset(&act,'\0',sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	act.sa_handler = wake;
	sigaction(SIGUSR1, &act, NULL);

	canSleep = 1;  

	while (canSleep)  
	{    
		printf("Student: \"(snore)\" \n");    
		sleep(1);  
	}

	printf("Student: \"Okay, okay.  I'll wake up!\"\n");

	return(EXIT_SUCCESS);
}



