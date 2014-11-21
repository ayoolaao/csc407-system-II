/*

Same as before, except this time each time the user does 
press Ctrl­C it randomly prints one of the following: 
– “Ouch!”
– “Stop that!” 
– “That hurts!” 
– “Mercy!”
HINT: Use switch(rand()%4) {..} to jump to cases 0 to 3 
randomly

*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include  <unistd.h>

void	poke	(int	signal)
{
  const char*	cPtr;

  switch  (rand() % 4)
  {
    case 0 :
    cPtr = "Ouch!";
    break;
    case 1 :
    cPtr = "Stop that!";
    break;
    case 2 :
    cPtr = "That hurts!";
    break;
    case 3 :
    cPtr = "Mercy!";
    break;
  }

  printf("Received signal %d, %s\n",signal,cPtr);
}


int	main	()
{
  struct sigaction act;

  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  act.sa_handler = poke;
  sigaction(SIGINT,&act,NULL);

  while  (1)
  {
    printf("You can't stop me!  Ngyeah-ngyeah, ngyeah-ngyeah!\n");
    sleep(2);
  }

  return(EXIT_SUCCESS);
}
