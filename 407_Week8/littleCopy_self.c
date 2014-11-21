#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define       BUFFER_SIZE     256

int main (int argc, const char* argv[])
{
	const char* fromFileCPtr;
	const char* toFileCPtr;
	if (argc < 3) {
		fprintf(stderr,
			"Usage: littleCopy <fromFile> <toFile>\n"
			);
		return(EXIT_FAILURE);
	}
	fromFileCPtr = argv[1];
	toFileCPtr   = argv[2];
  /* YOUR CODE HERE */
	int inFd = open(fromFileCPtr, O_RDONLY, 0);
	if (inFd < 0)
	{
		fprintf(stderr, "Can not open %s\n", fromFileCPtr);
		exit(EXIT_FAILURE);
	}

	int outFd = open(toFileCPtr, O_WRONLY|O_CREAT|O_TRUNC,  440);
	if(outFd < 0)
	{
		fprintf(stderr, "Can not open %s\n", toFileCPtr);
		close(inFd);
		exit(EXIT_FAILURE);
	}

	char buffer[BUFFER_SIZE];

	int numBytes;

	while((numBytes = read(inFd,  buffer, BUFFER_SIZE))>0)
		write(outFd, buffer, numBytes);

	close(outFd);
	close(inFd);
	return(EXIT_SUCCESS);
}

