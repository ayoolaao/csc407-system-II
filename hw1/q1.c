/* 
  CSC 407 System II
  Assignment #1
  
  Q:1

  q1.c 
*/

#include <stdlib.h>
#include <stdio.h>

#define	unsigned int uint

#define	 LENGTH	((uint) 512*64)

int	initializeArray	(uint	len, int*	intArray)
{
  uint	i;

  for (i = 0; i < len; i++)
    intArray[i] = (rand() % 64);
}



uint countAdjacent (int	maxIndex, int* intArray, int direction)
{
  uint i;
  uint sum	= 0;

  for(i = 0; i < maxIndex; i++)
    if(
        (intArray[i] == (intArray[i+1] + direction)) &&
    	  (intArray[i] == (intArray[i+2] + 2*direction))
    	)
      sum++;

  return(sum);
}



uint funkyFunction(uint	len, int*	intArray)
{
  uint i;  
  uint sum = 0;  
  uint countUp = 7*countAdjacent(len-2,intArray,+1);  
  uint countDn = 17*countAdjacent(len-2,intArray,-1);  
  for(i = 0; i < len-1; i++)    
    if  ( (i % 8) == 0x3 )      
      sum += countUp;    
    else      
      sum += countDn;

  return(sum);
}


int	main()
{
  int* intArray	= (int*)calloc(LENGTH,sizeof(int));

  initializeArray(LENGTH,intArray);
  printf("funkyFunction() == %d\n",funkyFunction(LENGTH,intArray));
  free(intArray);
  return(EXIT_SUCCESS);
}




