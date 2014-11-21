#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>

int	main	(int	argc,
		 char*	argv[]
		)
{
  const char*	dirName	= (argc < 2) ? "." : argv[1]; 
    // lists the item in the current directory(".")
  DIR*		dirPtr	= opendir(dirName);

  if  (dirPtr == NULL)
  {
    fprintf(stderr,"Could not open directory %s.\n",dirName);
    exit(EXIT_FAILURE);
  }

  struct dirent*	entryPtr;

  while  ( (entryPtr = readdir(dirPtr)) != NULL )
    printf("%s\n",entryPtr->d_name);

  closedir(dirPtr);
  return(EXIT_SUCCESS);
}

/* Output:

$ ./lister /home/CSTCIS/yzhang96/csc407/407_Week7/
lister
.
error.txt
stdoutVsStderr
lister.c
intPairCounter.c
printf_sys_call_ex.log
..
stdoutVsStderr.c
lineCounter
printf_sys_call_ex.c
lister2.c
printf_sys_call_ex
file.txt
lineCounter.c
intPair.txt

// every directory has "." and ".."
*/
