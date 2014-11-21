/*

Is using FILE* as efficient as int fd?

Probably not (FILE* uses int fd), but it is buffered.

*/



#include <stdlib.h>
#include <stdio.h>
int main()
{
	printf("T");
	printf("h");
	printf("i");
	printf("s");
	printf(" ");
	printf("i");
	printf("s");
	printf("n");
	printf("'");
	printf("t");
	printf(" ");
	printf("e");
	printf("f");
	printf("f");
	printf("i");
	printf("c");
	printf("i");
	printf("e");
	printf("n");
	printf("t");
	printf("\n");
	fflush(stdout);
	return(EXIT_SUCCESS);
}
