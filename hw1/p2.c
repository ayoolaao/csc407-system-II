/*
  Yuancheng Zhang
  CSC407 Assignment #1
*/

/*
  p2.c 
*/
#include <stdlib.h>
#include <stdio.h>

extern int     minArrayLen;
extern int     maxArrayLen;
extern int     maxMaxRandVal;
extern void    enterValue();

int      length;
int*     intArray;
int      maxRandVal;

const char* descriptionPtr1 = "array's length";
const char* descriptionPtr2 = "maximum random value";

void     createArray     (){
  enterValue(descriptionPtr1,minArrayLen,maxArrayLen,&length);
  enterValue(descriptionPtr2,minArrayLen,maxArrayLen,&maxMaxRandVal);
  intArray = (int*)calloc(length,sizeof(int));
  int i = 0;
  while(i++ < length) intArray[i] = (rand() % (maxMaxRandVal+1));
}

//  PURPOSE:  To print the values in 'intArray[]'.  No parameters.  No return
//      value.
void     printArray      (){
  printf("The array is:\n");
  int i = 0;
  while(i++ < length) printf("intArray[%d] = %d\n", i, intArray[i]);   
}
