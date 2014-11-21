#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
	int child_status;

	if (fork() == 0)
	{
		printf("HC: hello from child %d\n",getpid());
		return(50);
	}
	else
	{
		printf("HP: hello from parent\n"
			"In another shell say 'ps aux'\n"
			"Look for '<defunct>'.\n"
			);
		sleep(20);
		wait(&child_status);
		printf("CT: child has terminated and has givenus %d\n", 
			WEXITSTATUS(child_status)
			);
	}
	printf("Bye\n");
	return(EXIT_SUCCESS);
}
