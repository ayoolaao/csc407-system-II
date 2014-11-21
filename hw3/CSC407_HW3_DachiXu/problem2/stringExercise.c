#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define	MAX_LINE 256

//  PURPOSE:  To return a user-entered integer between 'min' and 'max'
//	inclusive.
int enterIntegerInRange(int min,int max)
{
  //  YOUR CODE HERE
  char input[MAX_LINE];
  int length = -1;

  while (length < min || length > max){
    printf("Please enter an integer between %d-%d:",min,max);
    fgets(input,MAX_LINE,stdin);
    length = strtol(input,NULL,10);
  }
  return length;
}

//  PURPOSE:  To have the user enter up to 'length'-1 chars of text (not
//	including the ending '\0') into 'text'.  It should get rid of the
//	ending '\n' character, if present.  No return value.
void enterText(char* text, int length)
{
  //  YOUR CODE HERE
  printf("Please enter some text:");
  fgets(text,length,stdin);
  size_t textLength = strlen(text) - 1;
  if(text[textLength] == '\n'){
    text[textLength] = '\0';
  }
}

//  PURPOSE:  To create *ON THE HEAP* a string of 'fieldWidth'+1 chars.
//	The first 'numTabs' chars are spaces.
//	Then, as much of 'text' as fits is placed in the space.
//	If any space remains then it filled with spaces.
//	The last character (index 'fieldWidth') has the string-ending '\0'.
//	The created string is returned.
char* createField(int fieldWidth,int numTabs,const char* text)
{
  //  YOUR CODE HERE
  char* fieldPtr = (char*)malloc(fieldWidth+1);
  char* fieldPtrCopy = fieldPtr;

  int i = 0;
  int count = 0;

  for(i = 0; i < numTabs; i++,fieldPtr++){
    *fieldPtr = ' ';
  }
  
  for(i = numTabs + 1; *text != '\0'; i++,text++,fieldPtr++){
    if(i > fieldWidth)
      break;
      
    *fieldPtr = *text;
    count = i;
    printf("loop: %d/%d\n",i,fieldWidth);
  }

  for(i = count; i < fieldWidth; i++,fieldPtr++){
    printf("pointer: %p\n",fieldPtr);
    *fieldPtr = ' ';
  }

  *fieldPtr = '\0';
  
  return fieldPtrCopy;
}

//  PURPOSE:  To run the main program.  Ignore command line parameters.
//	Returns 'EXIT_SUCCESS' to OS.
int main(void)
{
  char	text[MAX_LINE];
  int	fieldWidth;
  int	numTabs;
  char*	fieldPtr;

  while (1)
  {
    fieldWidth = enterIntegerInRange(0,MAX_LINE-1);
    
    //Testing enterIntegerInRange
    //printf("Max Length: %d\n",fieldWidth);
    
    if  (fieldWidth == 0)
      break;
    
    numTabs = enterIntegerInRange(1,fieldWidth-1);
    enterText(text,MAX_LINE);

    //Testing enterText
    //printf("text : %s\n",text);
    
    fieldPtr = createField(fieldWidth,numTabs,text);

    printf("\"%s\"\n",fieldPtr);
    free(fieldPtr);
  }

  return(EXIT_SUCCESS);
}

