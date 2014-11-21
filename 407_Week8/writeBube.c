#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
int main () {
  int fd = open("bubu.txt",O_WRONLY|O_CREAT|O_APPEND,0660);

  if(fd < 0){
  	fprintf(stderr, "Can't do anything boss!\n");
  	exit(EXIT_FAILURE);
  }
  
  write(fd, "\tMabu!\n",7);
  close(fd);
  system("ls -lh ./bubu.txt");
  return(EXIT_SUCCESS);
}

