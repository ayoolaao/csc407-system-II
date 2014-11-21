#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>

#define MAX_LINE 256
#define	ALARMCLOCK_PROG	"alarmClock"
#define	SLEEPINGSTUDENT_PROG "sleepingStudent"

int main(void){
  //Ask for the number of seconds to the student should be allowed to sleep (from 1 to 3600)
  int numSecs;
  printf("How many seconds shall the student be allowed to sleep? ");
  scanf("%d", &numSecs);

  //fork() a process to run sleepingStudent. Keep the pid returned by fork().
  pid_t studentPid = fork();
  if (studentPid == 0) {
    execl(SLEEPINGSTUDENT_PROG,SLEEPINGSTUDENT_PROG,NULL);
  }

  //fork() a process to run alarmClock.
  pid_t alarmPid = fork();
  if (alarmPid == 0) {
    char pid[MAX_LINE];
    char secs[MAX_LINE];
    snprintf(pid,MAX_LINE,"%d",studentPid);
    snprintf(secs,MAX_LINE,"%d",numSecs);
    execl(ALARMCLOCK_PROG,ALARMCLOCK_PROG,pid,secs,NULL);
  }

  //wait() for both processes to finish
  wait(NULL);
  printf("Such a good student\n");
  return(EXIT_SUCCESS);
}

