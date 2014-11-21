#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const int	BUFFER_SIZE	= 256;

/* Continued on next slide */
/* From previous slide */

int main (int argc, const char* argv[])
{
  const char* fromFileCPtr;

  if  (argc < 2)
  {
    fprintf(stderr,
            "Usage: lineCounter <fromFile>\n"
           );
    exit(EXIT_FAILURE);
  }

  fromFileCPtr = argv[1];

  /* YOUR CODE HERE */
  int	inFd	= open(fromFileCPtr,O_RDONLY,0);

  if  (inFd < 0)
  {
    fprintf(stderr,"Cannot open %s\n",fromFileCPtr);
    exit(EXIT_FAILURE);
  }

  char	buffer[BUFFER_SIZE];
  int  numBytes;
  int	counter	= 0;

  while  ( (numBytes = read(inFd,buffer,BUFFER_SIZE)) > 0 )
  {
    int	i;

    for  (i = 0;  i < numBytes;  i++)
      if  (buffer[i] == '\n')
        counter++;
  }

  printf("%d\n",counter);
  close(inFd);
  return(EXIT_SUCCESS);
}
