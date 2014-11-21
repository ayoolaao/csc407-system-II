#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define FILENAME  "bubu.txt"

int main () {
	const char* wordsPtr;
	int  i;
	int  numBytes;
	int  pid;
	int  fd = open(FILENAME, O_WRONLY|O_CREAT|O_TRUNC,0660);

	if (fd < 0) {
		fprintf(stderr,
			"Sorry, I can't make the output file %s\n", FILENAME);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Too many processes ace!\n");
		exit(EXIT_FAILURE);
	}
	else if  (pid == 0)
		wordsPtr = "Baby says \"Gaga Gugu!\"\n";
	else
		wordsPtr = "Mama says \"Poor baby!\"\n";
	
	numBytes = strlen(wordsPtr);
	
	for  (i = 0;  i < 4;  i++)
	{
		sleep(1);
		write(fd,wordsPtr,numBytes);
		printf(wordsPtr);
		if (pid > 0) 
		{
			sleep(2);
			close(fd); 
		}
	}
	return(EXIT_SUCCESS);
}

