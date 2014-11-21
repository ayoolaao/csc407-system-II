#include <stdlib.h>
#include <stdio.h>

int OS_EVERYTHING_OKAY = 0;

#define MSG "Hello world!"

void hello_world()
{
	puts(MSG);
}

int main()
{
	hello_world();
	return(OS_EVERYTHING_OKAY);
}

