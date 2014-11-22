#include	<ncurses.h>
#include	<pthread.h>

#define		STOP_CHAR	27

struct	ThreadInfo
{
  int		fd_;
  WINDOW*	windPtr_;
};

int	shouldContinue	= 1;

void*	doLocal	(void*	vPtr)
{
  struct ThreadInfo*	infoPtr	= (struct ThreadInfo*)vPtr;

  while  (1)
  {
    int	typed	= getch();

    if  (!shouldContinue)
      break;

    if  (typed == ERR)
      continue;

    int nTyped	= htonl(typed);

    write(infoPtr->fd_,&nTyped,sizeof(nTyped));

    if  (typed == STOP_CHAR)
      break;

    waddch(infoPtr->windPtr_,typed);
    wrefresh(infoPtr->windPtr_);
  }

  if  (shouldContinue)
    shouldContinue	= 0;
  else
  {
    int nTyped	= htonl(STOP_CHAR);

    write(infoPtr->fd_,&nTyped,sizeof(nTyped));
  }
}


void*	doRemote (void* vPtr)
{
  struct ThreadInfo*	infoPtr = (struct ThreadInfo*)vPtr;

  while  (1)
  {
    int	typed;
    int	nTyped;

    read(infoPtr->fd_,&nTyped,sizeof(nTyped));
    typed = ntohl(nTyped);

    if  (typed == STOP_CHAR)
      break;

    waddch(infoPtr->windPtr_,typed);
    wrefresh(infoPtr->windPtr_);
  }

  shouldContinue	= 0;
}


void	doTalk	(int	fd)
{
  pthread_t		localId;
  pthread_t		remoteId;
  struct ThreadInfo	localThreadInfo;
  struct ThreadInfo	remoteThreadInfo;

  initscr();
  cbreak();
  clear();
  halfdelay(10);
  noecho();
  move(0,3);
  addstr("Press ESC to stop:");
  refresh();

  localThreadInfo.fd_		= fd;
  localThreadInfo.windPtr_	= newwin(10,36, 1, 1);
  remoteThreadInfo.fd_		= fd;
  remoteThreadInfo.windPtr_	= newwin(10,36,12, 1);

  pthread_create(&localId, NULL,doLocal, &localThreadInfo);
  pthread_create(&remoteId,NULL,doRemote,&remoteThreadInfo);

  pthread_join(localId,NULL);
  pthread_join(remoteId,NULL);

  delwin(remoteThreadInfo.windPtr_);
  delwin(localThreadInfo.windPtr_);
  endwin();
}
