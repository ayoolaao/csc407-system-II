/* p1.c 
*/

#include <stdlib.h>
#include <stdio.h>

//
//      Declarations go here:
//
//  PURPOSE:  To hold the length of the array pointed to by 'intArray'.

extern int      length;

//  PURPOSE:  To hold the array of integers.
extern int*     intArray;

//  PURPOSE:  To hold the maximum value that may place in array 'intArray'.
extern int      maxRandVal;

//  PURPOSE:  To:
//      (1) have user enter 'length' (by calling 'enterValue()'),
//      (2) have user enter 'maxRandVal' (by calling 'enterValue()'), 
//      (3) define 'intArray' (say 'intArray =(int*)calloc(length,sizeof(int))')
//      (4) fill 'intArray' with random numbers between 0-'maxRandVal'
//          (use expression '(rand() % (maxRandVal+1))')
//      No parameters.  No return value.

extern void     createArray     ();

//  PURPOSE:  To print the values in 'intArray[]'.  No parameters.  No return
//      value.
extern void     printArray      ();

//
//      Function and variables go here:
//

//  PURPOSE:  To hold the minimum value for 'length'.
int     minArrayLen     = 1;

//  PURPOSE:  To hold the maximum value for 'length'.
int     maxArrayLen     = 256;

//  PURPOSE:  To hold the maximum value for 'maxRandVal'.
int     maxMaxRandVal   = 256;

//  PURPOSE:  To hold the length of C-string 'line'.
#define MAX_LINE        256

//  PURPOSE:  To hold the a C-string.
char    line[MAX_LINE];

//  PURPOSE:  To have the user enter the variable pointed to by 'valuePtr',
//      which must be between 'min' and 'max', and which is described by
//      '*descriptionPtr'.  No parameters.  No return value.
void    enterValue      (const char*    descriptionPtr,
                         int            min,
                         int            max,
                         int*           valuePtr
                        )
{  
  do  
  {    
    printf("Please enter the %s (%d-%d): ",descriptionPtr,min,max);    
    fgets(line,MAX_LINE,stdin);    
    *valuePtr = strtol(line,NULL,10);  
  }  
  while  ( (*valuePtr < min) || (*valuePtr > max) );
}

//  PURPOSE:  To free 'intArray'.  No parameters.  No return value.
//
void    freeArray       ()
{  
  free(intArray);
}

//  PURPOSE:  To define the array, print an array, and free the array.  No
//      Ignores parameters.  Returns 'EXIT_SUCCESS' to OS.
int     main            ()
{  
  createArray();  
  printArray();  
  freeArray();  
  return(EXIT_SUCCESS);
}

