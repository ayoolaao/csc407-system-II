// Code by Prof. Joe
// run another program: printCmdLineParams 

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	execl("./printCmdLineParams", // For the OS, so it knows what to run
		  "printCmdLineParams",   // For the process itself, so it knows
		  						  //  which program it is running
		  "A",                    // Optional
		  "B",					  // Optional
		  "C",					  // Optional
		  "Mary had a little lamb", // Optional
		  "Whose fleece was white as snow", // Optional
		  "Something else",       // Optional
		  NULL					  // NEED because it marks the last
		  );

	printf("Will this code here ever run?\n"); // NO
}
