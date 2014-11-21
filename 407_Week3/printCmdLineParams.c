// Code by Prof. Joe

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[]) // argument count, argument vector
{
	printf("I have %d command line parameter(s) and thery are:\n", argc);

	int i;

	for (i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);

	return(EXIT_SUCCESS);

}

