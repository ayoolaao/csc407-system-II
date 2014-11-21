#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main()
{
	pthread_t childId;
	SendObject arg = "Whatever Hehehe!";
	ReceiveObject* childsStatusPtr;

	pthread_create(&childId, NULL, doThisFnc, &arg);

	pthread_join(childId, &childsStatusPtr);
	return(EXIT_SUCCESS);
}
