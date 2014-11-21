#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* naughtyCopy(const char* fromP, size_t n)
{
	int fromPLen = strlen(fromP);
	int length = (fromPLen < n) ? fromPLen : n;

	char* toP = (char*)malloc(length+1);
	int i;

	for (i = 0; i < length; i++)
		toP[i] = fromP[i];

	toP[i] = '\0';
	
	return(toP);
}

int main()
{
	char* cPtr0 = naughtyCopy("small string", 1000);
	char* cPtr1 = naughtyCopy("llllooooonnnnnngggg   sssssstttttttrrrrrriiiiiiinnnngggggggg",8);

	printf("%s\n", cPtr0);
	printf("%s\n", cPtr1);

	free(cPtr0);
	free(cPtr1);
	return(EXIT_SUCCESS);
}
