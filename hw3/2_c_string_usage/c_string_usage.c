/*
Yuancheng Zhang
CSC 407 HW3 Problem 2 - C String usage! (30 Points)

Finish the program below by writing enterIntegerInRange(), enterText(), and createField().
int enterIntegerInRange (int min, int max) should let the user enter an integer between 'min' and 'max' inclusive. It should make sure the number is in that range.
void enterText (char* text, int length) should have the user enter up to 'length'-1 chars of text (not including the ending '\0') into 'text'. (HINT: fgets(~,length,~) does this for you automatically.) It should get rid of the ending '\n' character, if present.
char* createField (int fieldWidth, int numTabs, const char* text) should create ON THE HEAP a string of 'fieldWidth'+1 chars.
The first 'numTabs' chars are spaces.
Then, as much of 'text' as fits is placed in the space.
If any space remains then it filled with spaces.
The last character (index 'fieldWidth') has the string-ending '\0'.
The created string is returned.

*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		MAX_LINE	256

//  PURPOSE:  To return a user-entered integer between 'min' and 'max'
//	inclusive.
int	enterIntegerInRange	(int min, int max)
{
//  YOUR CODE HERE
	char line[MAX_LINE];
	int number = (int)malloc(sizeof(int));

	while (1)
	{
		printf("Please enter an integer between %d-%d:", min, max);
		fgets(line, MAX_LINE, stdin);
		number = atol(line);
		if(min <= number && number <= max)
			break;
	}
	return number;
}


//  PURPOSE:  To have the user enter up to 'length'-1 chars of text (not
//	including the ending '\0') into 'text'.  It should get rid of the
//	ending '\n' character, if present.  No return value.
void enterText (char* text, int length)
{
//  YOUR CODE HERE
	printf("Please enter some text:");
	fgets(text, length, stdin);
	int textLen = (int)strlen(text) - 1;
	if(text[textLen] == '\n')
		text[textLen] = '\0';
	
}


//  PURPOSE:  To create *ON THE HEAP* a string of 'fieldWidth'+1 chars.
//	The first 'numTabs' chars are spaces.
//	Then, as much of 'text' as fits is placed in the space.
//	If any space remains then it filled with spaces.
//	The last character (index 'fieldWidth') has the string-ending '\0'.
//	The created string is returned.
char* createField (int fieldWidth, int numTabs, const char*	text)
{
//  YOUR CODE HERE
	char* fieldPtr = (char*)malloc(fieldWidth+1);
	char* c = fieldPtr;
	int i;

	while(i++<numTabs)
	{
		*fieldPtr++ = ' ';
		//i++
	}

	while(*text != '\0')
	{	
		if(i > fieldWidth) break;
		*fieldPtr++ = *text++;
		i++;
	}

	while(i++ < fieldWidth)
	{
		*fieldPtr++ = ' ';
	}

	*fieldPtr = '\0';

	return c;
}

//  PURPOSE:  To run the main program.  Ignore command line parameters.
//	Returns 'EXIT_SUCCESS' to OS.
int	main()
{
	char text[MAX_LINE];
	int	fieldWidth;
	int	numTabs; //space
	char* fieldPtr;

	while  (1)
	{
		fieldWidth	= enterIntegerInRange(0,MAX_LINE-1);

		if  (fieldWidth == 0)
			break;

		numTabs	= enterIntegerInRange(1,fieldWidth-1);
		enterText(text,MAX_LINE);

		fieldPtr	= createField(fieldWidth,numTabs,text);

		printf("\"%s\"\n",fieldPtr);
		free(fieldPtr);
	}

	return(EXIT_SUCCESS);
}
