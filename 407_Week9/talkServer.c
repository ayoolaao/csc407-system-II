#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>//For socket()
#include <netinet/in.h>//For sockaddr_in and htons()
#include <netdb.h> //For getaddrinfo()
#include <errno.h> //For errno var
#include <sys/stat.h> //For open(), read(),write()
#include <fcntl.h> // and close()
#include <signal.h>
#include <wait.h>

#define	BUFFER_LEN	256

void	handleClient	(int	fd)
{
  char	buffer[BUFFER_LEN];
  int	numRead	= read(fd,buffer,BUFFER_LEN);
  int	i;

  for  (i = 0;  i < numRead;  i++)
    buffer[i] = toupper(buffer[i]);

  write(fd,buffer,numRead);
  close(fd);
}

void	sigChildHandler	(int	sig)
{
  int	status;
  pid_t	childId;

  while ( (childId = waitpid(-1,&status,WNOHANG)) > 0)
  {
    printf("Child %d finished.\n",childId);
  }
}


void	installSigChildHandler	()
{
  // Set up struct to specify the new action.
  struct sigaction act;
  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_NOCLDSTOP | SA_RESTART;;
  act.sa_handler = sigChildHandler;
  // Handle with simpleHandler()
  sigaction(SIGCHLD,&act,NULL);
}

void	doTalk	(int	fileDescriptor);

int	main	()
{
  int	port;
  char	buffer[BUFFER_LEN];

  printf("Please enter port number to monopolize: ");
  fgets(buffer,BUFFER_LEN,stdin);
  port	= strtol(buffer,NULL,10);

  // Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
			        SOCK_STREAM, // Reliable TCP
			        0);

  // We'll fill in this datastruct
  struct sockaddr_in socketInfo;
  // Fill socketInfo with 0's
  memset(&socketInfo,'\0',sizeof(socketInfo));
  // Use std TCP/IP
  socketInfo.sin_family = AF_INET;
  // Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);
  // Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY;
  // Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
		    (struct sockaddr*)&socketInfo,
		    sizeof(socketInfo)
		   );

  if  (status < 0)
  {
    fprintf(stderr,"Could not bind to port %d\n",port);
    exit(EXIT_FAILURE);
  }

  listen(socketDescriptor,5);
  installSigChildHandler();

  // Accept connection to client
  int clientDescriptor = accept(socketDescriptor,NULL,NULL);
  
  doTalk(clientDescriptor);
  close(clientDescriptor);
  close(socketDescriptor);

  return(EXIT_SUCCESS);
}
