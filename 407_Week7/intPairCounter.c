#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		BUFFER_LEN	256
#define		COMMENT_CHAR	'#'

int	main	(int	argc,
		 char*	argv[]
		)
{
  if  (argc < 2)
  {
    fprintf(stderr,"Usage:\tintPairCounter <filename>\n");
    exit(EXIT_FAILURE);
  }

  FILE*	filePtr	= fopen(argv[1],"r");

  if  (filePtr == NULL)
  {
    fprintf(stderr,"Could not read %s\n",argv[1]);
    exit(EXIT_FAILURE);
  }

  char	buffer[BUFFER_LEN];
  int	count			= 0;
  int	lineNum			= 0;

  while  (fgets(buffer,BUFFER_LEN,filePtr) != NULL)
  {
    char*	cPtr;
    int		i,j;

    lineNum++;

    for  (cPtr = &buffer[0];  isspace(*cPtr);  cPtr++);

    if  (*cPtr == COMMENT_CHAR  ||  *cPtr == '\0')
      continue;

    if  (sscanf(cPtr,"%d %d",&i,&j) < 2)
      fprintf(stderr,"Syntax error on line %d.\n",lineNum);
    else
      count++;

  }

  fclose(filePtr);
  printf("%d\n",count);
  return(EXIT_SUCCESS);
}
