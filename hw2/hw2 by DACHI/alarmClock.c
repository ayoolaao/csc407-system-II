#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc,char *argv[], char *envp[]){
  pid_t pid = (pid_t)strtol(argv[1],NULL,10);
  int timer = (int)strtol(argv[2],NULL,10);

  if ( pid < 0){
    printf("Illegal pid.\n");
  }

  if ( timer < 0){
    printf("Illegal number of seconds.\n");
  }

  while(timer > 0){
   printf("Clock \"00:00:%02d\"\n",timer);
   sleep(1);
   timer--;
  }

  printf("Clock \"Ding! Ding! Ding!\"\n");
  kill(pid,SIGUSR1);
  return(EXIT_SUCCESS);
}
