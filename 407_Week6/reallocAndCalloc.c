#include <stdlib.h>
#include <stdio.h>
#define NUM_ELE 4

int main()
{
	int* iPtr;
	int* iPtr2;
	int i;

	iPtr = (int*)calloc(NUM_ELE, sizeof(int));
	iPtr2 = (int*)calloc(NUM_ELE, sizeof(int));

	for(i = 0; i < NUM_ELE; i++)
	{
		// Any other ways to access: *(iPtr+i) = i*10; 
		iPtr[i] = i * 10;
	}

	for(i = 0; i < NUM_ELE; i++)
	{
		printf("%3d is at %p\n", *(iPtr + i), (iPtr + i));
	}

	for(i = 0; i < NUM_ELE; i++)
	{
		printf("%3d is at %p\n", *(iPtr2 + i), (iPtr2 + i));
	}

	printf("Uh-oh, not enough space!\n");
	iPtr = (int*)realloc(iPtr, 4 * NUM_ELE * sizeof(int));

	for(i = 0; i < 4 * NUM_ELE; i++)
	{
		printf("%3d is at %p\n", *(iPtr + i), (iPtr + i));
	}

	free(iPtr2); //Very important!
	free(iPtr); //Very important!
	return(EXIT_SUCCESS);
}

