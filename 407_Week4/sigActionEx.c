/* More advanced sig handlers take */
/* tell which process sent the signal */
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void    signal_handler(
	int sig, siginfo_t* infoPtr, void* dataPtr)
{
	printf("signal:[%d], pid:[%d], uid:[%d]\n", 
		sig, infoPtr->si_pid, infoPtr->si_uid );
  //  dataPtr is not used so much
}

int main (int argc, char *argv[])
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask );
	sa.sa_flags= SA_SIGINFO //Install sa_sigaction // (as opposed to
                            //sa_handler)
               | SA_RESTART;//If interrupted in
                          // sys call then
                          // restart sys call
                          // after signal handler
    sa.sa_sigaction = signal_handler;
    sigaction(SIGINT, &sa, NULL);

    int i;
    for (i=0; i<60; i++)
    {
             	printf("%2d of 60\n",i);
             	sleep (1); 
    }
    return(EXIT_SUCCESS);
}


