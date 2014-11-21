#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int childsStatus;
	pid_t childId = fork();
	char* argsText = "Whatever hahaha!";

	if(childId == 0)
		execlp("doThisFile",..,argsText,..);
	waitpid(childId,&childsStatus,0);

	return(EXIT_SUCCESS);
}
