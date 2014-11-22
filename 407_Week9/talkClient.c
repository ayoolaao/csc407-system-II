#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>//For socket()
#include <netinet/in.h>//For sockaddr_in and htons()
#include <netdb.h> //For getaddrinfo()
#include <errno.h> //For errno var
#include <sys/stat.h> //For open(), read(),write()
#include <fcntl.h> // and close()

#define	BUFFER_LEN	256

void	doTalk	(int	socketDescriptor);

int	main	()
{
  char	buffer[BUFFER_LEN];
  char	machineName[BUFFER_LEN];
  int	port;

  printf("Machine name (e.g. localhost.localdomain)? ");
  fgets(machineName,BUFFER_LEN,stdin);

  char*	cPtr	= strchr(machineName,'\n');

  if  (cPtr != NULL)
    *cPtr = '\0';

  printf("Port number? ");
  fgets(buffer,BUFFER_LEN,stdin);
  port = strtol(buffer,NULL,10);

  // Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
				SOCK_STREAM, // Reliable TCP
				0);
  struct addrinfo* hostPtr;
  int status = getaddrinfo(machineName,NULL,NULL,&hostPtr);

  if (status != 0)
  {
    fprintf(stderr,gai_strerror(status));
    exit(EXIT_FAILURE);
  }

  // Connect to server
  struct sockaddr_in server;
  // Clear server datastruct
  memset(&server, 0, sizeof(server));
  // Use TCP/IP
  server.sin_family = AF_INET;
  // Tell port # in proper network byte order
  server.sin_port = htons(port);
  // Copy connectivity info from info on server ("hostPtr")
  server.sin_addr.s_addr =
  ((struct sockaddr_in*)hostPtr->ai_addr)->sin_addr.s_addr;
  status = connect(socketDescriptor,(struct sockaddr*)&server,sizeof(server));

  if  (status < 0)
  {
    fprintf(stderr,"Could not connect %s:%d\n",machineName,port);
    return(EXIT_FAILURE);
  }

  doTalk(socketDescriptor);
  close(socketDescriptor);
  return(EXIT_SUCCESS);
}
