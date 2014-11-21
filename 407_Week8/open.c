
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
int main () {
  int fd = open("bubu.txt",O_WRONLY|O_CREAT|O_APPEND,0660);
  printf("fd = %d\n",fd);
  close(fd);
  return(EXIT_SUCCESS);
}

