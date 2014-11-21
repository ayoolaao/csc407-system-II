/*

Revise your lister program into lister2 that for files will print:
– the size in bytes for files
– "(dir)" for directories
– "(other)" of entries other than a file or directory

*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> /* directory */
#include <sys/stat.h>
#include <unistd.h>

#define		STRING_LEN	512

int	main	(int	argc, char*	argv[])
{
  const char*	dirName	= (argc < 2) ? "." : argv[1];
  DIR*		dirPtr	= opendir(dirName);

  if  (dirPtr == NULL)
  {
    fprintf(stderr,"Could not open directory %s.\n",dirName);
    exit(EXIT_FAILURE);
  }

  struct dirent*	entryPtr; 

  while  ( (entryPtr = readdir(dirPtr)) != NULL )
  {
    char	filename[STRING_LEN];
    struct stat	statBuffer;

    snprintf(filename,STRING_LEN,"%s/%s",dirName,entryPtr->d_name);
    stat(filename,&statBuffer);

    if  ( S_ISREG(statBuffer.st_mode) )
      printf("%20s\t(%d)\n",(*entryPtr).d_name,statBuffer.st_size);
// (*entryPtr).d_name is equivalent as entryPtr->d_name;
//  entryPtr is pointer and points to an object;
// so (*entryPtr) is the object;
    else if  ( S_ISDIR(statBuffer.st_mode) )
      printf("%20s\t(dir)\n",entryPtr->d_name);
    else
      printf("%20s\t(other)\n",entryPtr->d_name);
  }

  closedir(dirPtr);
  return(EXIT_SUCCESS);
}

/*
Outputs:

$ ./lister2
              lister  (5621)
                   .  (dir)
           error.txt  (19)
      stdoutVsStderr  (5196)
            lister.c  (870)
    intPairCounter.c  (905)
printf_sys_call_ex.log  (1676)
                  ..  (dir)
    stdoutVsStderr.c  (466)
         lineCounter  (6027)
printf_sys_call_ex.c  (496)
           lister2.c  (1122)
  printf_sys_call_ex  (5185)
            file.txt  (49)
             lister2  (6179)
       lineCounter.c  (1026)
         intPair.txt  (94)

*/

