/*

Write a program that takes two parameters:
$ lineCounter string filename
that counts and returns the number of lines of filename that begin with string string.
– If filename cannot be opened it writes an error message to stderr.

$ ./lineCounter p file.txt

*/


#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		BUFFER_LEN	256

int	main	(int	argc,
		 char*	argv[]
		)
{
  if  (argc < 3) //argc is the length of argv[] begining with 1.
  {
    fprintf(stderr,"Usage:\tlineCounter <string> <filename>\n");
    exit(EXIT_FAILURE);
  }

  FILE*	filePtr	= fopen(argv[2],"r");

  if  (filePtr == NULL)
  {
    fprintf(stderr,"%s is not a valid file.\n",argv[2]);
    exit(EXIT_FAILURE);
  }

  int		count	= 0;
  const char*	lookFor	= argv[1];
  int		lookForLen	= strlen(lookFor);
  char		buffer[BUFFER_LEN];

  while  ( fgets(buffer,BUFFER_LEN,filePtr) != NULL )
  {
    if  (strncmp(buffer,lookFor,lookForLen) == 0)
      count++;
  }

  fclose(filePtr);
  printf("%d\n",count);
  return(EXIT_SUCCESS);
}
