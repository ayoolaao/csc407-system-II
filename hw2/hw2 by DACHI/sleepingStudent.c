#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int canSleep = 1;

void handler(int sig){
  canSleep = 0;
}

int main(void){

  signal(SIGUSR1,handler);

  while (canSleep){
    printf("Student: \"(snore)\"\n");
    sleep(1);
  }
  printf("Student: \"Okay, okay.  I\'ll wake up!\"\n");
  return(EXIT_SUCCESS);
}
