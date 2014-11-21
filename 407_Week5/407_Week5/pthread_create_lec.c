void* functionName (void: voidPtr)
{
	...
}


{
	pthread_t threadId;

	// create a thread;
	int status = pthread_create(&threadId, NULL, functionName, &param);

	// wait for thread;
	pthread_join(threadId, &returnValuePtr);

}
