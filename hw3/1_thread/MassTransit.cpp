/*-------------------------------------------------------------------------*
*---									---*
*---		MassTransit.h						---*
*---									---*
*---	    This file declares a class that represent a MassTransit	---*
*---	system of multiple inter-connected Track and Station instances,	---*
*---	on which multiple Train instances each controlled by its own	---*
*---	pthread run.							---*
*---									---*
*---	----	----	----	----	----	----	----	----	---*
*---									---*
*---	Version 1.0		2013 May 10		Joseph Phillips	---*
*---									---*
*-------------------------------------------------------------------------*/

#include	"headers.h"

//  PURPOSE:  To initialize '*this' to the beginning state of the mass
//	transit simulator.  Defines 'Track'-and-'Station' instance topology and 
MassTransit::MassTransit	()
throw() :
redlineNorth("N Red Station"),
brownlineNorth("N Brown Station"),
northTunnel("N Tunnel Station"),
southTunnel("S Tunnel Station"),
redlineSouth("S Red Station"),
brownlineSouth("S Brown Station"),
redlineNorthTrack
("N Red Track",
  &redlineNorth,
  &northTunnel
  ),
brownlineNorthTrack
("N Brown Track",
  &brownlineNorth,
  &northTunnel
  ),
tunnelTrack	("Tunnel Track",
  &northTunnel,
  &southTunnel
  ),
redlineSouthTrack
("S Red Track",
  &southTunnel,
  &redlineSouth
  ),
brownlineSouthTrack
("S Brown Track",
  &southTunnel,
  &brownlineSouth
  ),
shouldContinue(true)
{
//  I.  Application validity check:

//  II.  Initialize other member vars:
//  II.A.  Tell 'Station' instances to which 'Track' instances they are
//	     connected:
  redlineNorth.  setTrackPtr(REDLINE,  SOUTH,&redlineNorthTrack);
  brownlineNorth.setTrackPtr(BROWNLINE,SOUTH,&brownlineNorthTrack);

  northTunnel.   setTrackPtr(REDLINE,  NORTH,&redlineNorthTrack);
  northTunnel.   setTrackPtr(BROWNLINE,NORTH,&brownlineNorthTrack);
  northTunnel.   setTrackPtr(REDLINE,  SOUTH,&tunnelTrack);
  northTunnel.   setTrackPtr(BROWNLINE,SOUTH,&tunnelTrack);

  southTunnel.   setTrackPtr(REDLINE,  SOUTH,&redlineSouthTrack);
  southTunnel.   setTrackPtr(BROWNLINE,SOUTH,&brownlineSouthTrack);
  southTunnel.   setTrackPtr(REDLINE,  NORTH,&tunnelTrack);
  southTunnel.   setTrackPtr(BROWNLINE,NORTH,&tunnelTrack);

  redlineSouth.  setTrackPtr(REDLINE,  NORTH,&redlineSouthTrack);
  brownlineSouth.setTrackPtr(BROWNLINE,NORTH,&brownlineSouthTrack);

//  II.B.  Initialize mutex for 'print()':
//  YOUR CODE HERE TO INITIALIZE YOUR MUTEX:
  pthread_mutex_init(&printLock, NULL);

//  II.C.  Create 'NUM_TRAINS' 'Train' instances and pthreads that operate
//	       them:
  Train*		trainPtrArray[NUM_TRAINS];

  for  (uint i = 0;  i < NUM_TRAINS;  i++)
  {
    bool		haveFoundGoodPlace	= false;
    TrainLocation*	locPtr;
    line_t		newLine;
    direction_t		newDir;

//  II.C.1.  Each iteration attempts to create a 'Train' instance with
//	   randomly-chosen parameters, subject to the constraint that
//	   at most 'MAX_ALLOWED_NUM_TRAINS_ON_TRACK' 'Train' instances
//	   are allowed on any one 'Track' instance:
    do
    {
      switch  (rand() % 11)
      {
        case  0 :
        locPtr	= &redlineNorth;
        newLine	= REDLINE;
        newDir	= SOUTH;
        break;
        case  1 :
        locPtr	= &brownlineNorth;
        newLine	= BROWNLINE;
        newDir	= SOUTH;
        break;
        case  2 :
        locPtr	= &northTunnel;
        newLine	= (rand() % 2) ? REDLINE : BROWNLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
        case  3 :
        locPtr	= &southTunnel;
        newLine	= (rand() % 2) ? REDLINE : BROWNLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
        case  4 :
        locPtr	= &redlineSouth;
        newLine	= REDLINE;
        newDir	= NORTH;
        break;
        case  5 :
        locPtr	= &brownlineSouth;
        newLine	= BROWNLINE;
        newDir	= NORTH;
        break;
        case  6 :
        locPtr	= &redlineNorthTrack;
        newLine	= REDLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
        case  7 :
        locPtr	= &brownlineNorthTrack;
        newLine	= BROWNLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
        case  8 :
        locPtr	= &tunnelTrack;
        newLine	= (rand() % 2) ? REDLINE : BROWNLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
        case  9 :
        locPtr	= &redlineSouthTrack;
        newLine	= REDLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
        case 10 :
        locPtr	= &brownlineSouthTrack;
        newLine	= BROWNLINE;
        newDir	= (rand() % 2) ? NORTH : SOUTH;
        break;
      }

    }
    while  ( ((dynamic_cast<Track*>(locPtr)) != NULL)	 &&
      (locPtr->getNumTrains() >= MAX_ALLOWED_NUM_TRAINS_ON_TRACK)
      );

//  II.C.2.  Create 'Train' instance:
      trainPtrArray[i]	= new Train(i,newLine,newDir,locPtr,*this);
    locPtr->arrive(trainPtrArray[i]);

//  II.C.3.  Create pthread for 'Train' instance:
//  YOUR CODE HERE TO INITIALIZE THE i-th pthread TO RUN
//  'simulateTrain()' GIVEN 'trainPtrArray[i]' AS A PARAMETER
    pthread_create(&trainId[i], NULL, simulateTrain, (void*)trainPtrArray[i]);
  }

//  III.  Finished:
}


//  PURPOSE:  To release resources.  No parameters.  No return value.
MassTransit::~MassTransit	()
throw()
{
//  I.  Application validity check:

//  II.  Release resources:
//	II.A.  Wait for thread and destroy 'Train' instances they give back:
  for  (uint i = 0;  i < NUM_TRAINS;  i++)
  {
    Train*	trainPtr;

//  YOUR CODE HERE TO WAIT FOR THE i-th pthread AND TO SET 'trainPtr' TO
//  THE 'Train' INSTANCE THAT IT GIVES BACK
    pthread_join(trainId[i], (void**)&trainPtr);

    safeDelete(trainPtr);
  }

//  II.B.  Destroy 'print()' mutex:
//  YOUR CODE HERE TO DESTROY YOUR MUTEX:
  pthread_mutex_destroy(&printLock);
//  III.  Finished:
}


//  PURPOSE:  To display the current state of '*this' MassTransit system.
//	No parameters.  No return value.
//  YOUR CODE SOMEWHERE IN HERE TO LOCK AND UNLOCK YOUR MUTEX.
//  WHAT NEEDS TO BE PROTECTED?
void		MassTransit::print	()
throw()
{
  pthread_mutex_lock(&printLock);
//  I.  Application validity check:

//  II.  Display system:
  clear();

  move( 1, 0);	brownlineNorth.print();
  move( 2, 6);	addstr("|");
  move( 3, 0);	brownlineNorthTrack.print();
  move( 4, 6);	addstr("|");

  move( 2,23);	redlineNorth.print();
  move( 3,29);	addstr("|");
  move( 4,23);	redlineNorthTrack.print();

  move( 5, 7);	addstr("\\");	move( 5,28);	addstr("/");
  move( 6, 8);	addstr("\\");	move( 6,27);	addstr("/");
  move( 7, 9);	addstr("\\");	move( 7,26);	addstr("/");

  move( 8, 9);	northTunnel.print();
  move( 9,18);	addstr("|");
  move(10, 9);	tunnelTrack.print();
  move(11,18);	addstr("|");
  move(12, 9);	southTunnel.print();

  move(13, 9);	addstr("/");	move(13,26);	addstr("\\");
  move(14, 8);	addstr("/");	move(14,27);	addstr("\\");
  move(15, 7);	addstr("/");	move(15,28);	addstr("\\");

  move(16, 6);	addstr("|");
  move(17, 0);	brownlineSouthTrack.print();
  move(18, 6);	addstr("|");
  move(19, 0);	brownlineSouth.print();

  move(16,23);	redlineSouthTrack.print();
  move(17,29);	addstr("|");
  move(18,23);	redlineSouth.print();

  if  (redlineNorthTrack.getNumTrains() > MAX_ALLOWED_NUM_TRAINS_ON_TRACK)
  {
    move(20,10);
    addstr("CRASH!  Redline North  ");
  }

  if  (brownlineNorthTrack.getNumTrains() > MAX_ALLOWED_NUM_TRAINS_ON_TRACK)
  {
    move(20,10);
    addstr("CRASH!  Brownline North");
  }

  if  (tunnelTrack.getNumTrains() > MAX_ALLOWED_NUM_TRAINS_ON_TRACK)
  {
    move(20,10);
    addstr("CRASH!  Tunnel         ");
  }

  if  (redlineSouthTrack.getNumTrains() > MAX_ALLOWED_NUM_TRAINS_ON_TRACK)
  {
    move(20,10);
    addstr("CRASH!  Redline South  ");
  }

  if  (brownlineSouthTrack.getNumTrains() > MAX_ALLOWED_NUM_TRAINS_ON_TRACK)
  {
    move(20,10);
    addstr("CRASH!  Brownline South");
  }

refresh();	// Makes changes visible

//  III.  Finished:
pthread_mutex_unlock(&printLock);
}


//  PURPOSE:  To run '*this' MassTransit simulation for 'numSecs' seconds.
//	No return value.
void		MassTransit::simulate
(uint		numSecs
  )
throw(const char*)
{
//  I.  Application validity check:

//  II.  Do simulution:
  print();
  sleep(numSecs);
  shouldContinue	= false;

//  III.  Finished:
}


//  PURPOSE:  To update '*this' MassTransit system after a 'Train' instance
//	has moved.  No parameters.  No return value.
void		MassTransit::update		()
{
//  I.  Application validity check:

//  II.  Update:
  print();

//  III.  Finished:
}
