//Computer Systems - A Programmer's Perspective
//Chapter 8 Exceptional Control Flow
//Section 8.4 Process Control
//Figure 8.15 Using fork to create a new process.

/* fork.c */
#include <sys/types.h>
#include <unistd.h>
#include "csapp.h"

int main()
{
	pid_t pid;
	int x = 1;

	pid = Fork();
	if (pid == 0) { //child
		printf("child : x=%d\n", ++x);
		exit(0);
	}

	printf("parent: x=%d\n", --x);
	exit(0);

}