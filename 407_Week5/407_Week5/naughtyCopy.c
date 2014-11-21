#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * naughtyCopy(const char* fromP)
{	
	char* begin =  (char*)malloc(strlen(fromP) + 1);
	char *toP ;

	for (toP = begin; *fromP != '\0'; fromP++, toP++)
		*toP = *fromP;

	*toP = '\0';
	//free(fromP);
	return(toP);
}

int main()
{
	char* cPtr = naughtyCopy("Okay I'll have to think of something!\n");
	printf(cPtr);
	free(cPtr);
	return(EXIT_SUCCESS);
}