/* 

stdout vs. stderr

Q: Why might it be useful to distinguish between 
	output messages and error messages?

A: For debugging!

*/


#include <stdlib.h>
#include <stdio.h>
/* $ ./stdoutVsStderr
* I'm an ordinary msg.
* I'm the error msg.
* $ ./stdoutVsStderr 2> error.txt 
* I'm an ordinary msg.
* $ cat error.txt
* I'm the error msg.
*/
int main ()
{
	fprintf(stdout,"I'm an ordinary msg.\n"); 
	fprintf(stderr,"I'm the error msg.\n"); 
	return(EXIT_SUCCESS);
}
