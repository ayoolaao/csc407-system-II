// fork() example 1
// Code by Prof. Joe

#include <stdio.h>
#include <stdlib.h>

int main()
{
	puts("L0");
	fork();
	puts("L1");
	fork();
	printf("Bye from process %d\n", getpid());
	return(EXIT_SUCCESS);
}
