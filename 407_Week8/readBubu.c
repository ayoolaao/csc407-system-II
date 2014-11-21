#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#define       BUFFER_SIZE     256
int main () {
  char buffer[BUFFER_SIZE];
  int  fd = open("bubu.txt",O_RDONLY,0660);
  read(fd,buffer,BUFFER_SIZE);
  printf("%s",buffer);
  close(fd);
  return(EXIT_SUCCESS);
}
