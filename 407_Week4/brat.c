#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include  <unistd.h>

int	main	()
{
  // Set up struct to specify the new action.
  struct sigaction act; //Make a new action object
  /* Structure code below */
  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  act.sa_handler = SIG_IGN;// Ignore SIGINT 
      //.sa_handler is member variable
  sigaction(SIGINT,&act,NULL);
  sigaction(SIGKILL,&act,NULL);


  while  (1) //while(true) in C++
  {
    printf("You can't stop me!  Ngyeah-ngyeah, ngyeah-ngyeah!\n");
    sleep(2);
  }

  return(EXIT_SUCCESS);
}
