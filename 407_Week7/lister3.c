/*

Revise your lister program into lister2 that for files will print:
– the size in bytes for files
– "(dir)" for directories
– "(other)" of entries other than a file or directory

Revise lister2 to print the last change (write) time for all entries
How would you modify your program to recursively descend into directories (other than “.” and “..”)

*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> /* directory */
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

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
      printf("%20s\t(%d)\t%30s",(*entryPtr).d_name,statBuffer.st_size, 
        ctime(&(statBuffer.st_ctime)));
    // ctime() terminates with '\n'
    // (*entryPtr).d_name is equivalent as entryPtr->d_name;
    // entryPtr is pointer and points to an object;
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
$ ./lister3
              lister  (5621)       Sun Nov 16 13:07:33 2014
                   .  (dir)
           error.txt  (19)       Sun Nov 16 12:24:20 2014
      stdoutVsStderr  (5196)       Sun Nov 16 12:24:06 2014
            lister.c  (870)      Sun Nov 16 13:23:41 2014
    intPairCounter.c  (905)      Sun Nov 16 11:33:20 2014
printf_sys_call_ex.log  (1676)       Sun Nov 16 12:32:00 2014
                  ..  (dir)
           lister3.c  (2107)       Sun Nov 16 14:20:02 2014
    stdoutVsStderr.c  (466)      Sun Nov 16 13:24:43 2014
         lineCounter  (6027)       Sun Nov 16 11:53:31 2014
printf_sys_call_ex.c  (496)      Sun Nov 16 12:36:43 2014
           lister2.c  (1830)       Sun Nov 16 13:56:46 2014
  printf_sys_call_ex  (5185)       Sun Nov 16 12:36:51 2014
            file.txt  (49)       Sun Nov 16 11:33:19 2014
             lister3  (6284)       Sun Nov 16 14:20:06 2014
             lister2  (6179)       Sun Nov 16 13:54:26 2014
       lineCounter.c  (1026)       Sun Nov 16 13:23:27 2014
         intPair.txt  (94)       Sun Nov 16 11:33:20 2014
*/

