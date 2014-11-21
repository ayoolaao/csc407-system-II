// Code by Prof. Joe
// run another program: printCmdLineParams 

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	execl("ls", // For the OS, so it knows what to run
		  "",   // For the process itself, so it knows
		  						  //  which program it is running
		  NULL					  // NEED because it marks the last
		  );

	printf("Will this code here ever run?\n"); // NO
}
