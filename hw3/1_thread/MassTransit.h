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

class	MassTransit
{
//  I.  Member vars:
//  PURPOSE:  To represent the Station instances in '*this' MassTransit
//	system.
  Station		redlineNorth;
  Station		brownlineNorth;
  Station		northTunnel;
  Station		southTunnel;
  Station		redlineSouth;
  Station		brownlineSouth;

//  PURPOSE:  To represent the Track instances in '*this' MassTransit
//	system.
  Track			redlineNorthTrack;
  Track			brownlineNorthTrack;
  Track			tunnelTrack;
  Track			redlineSouthTrack;
  Track			brownlineSouthTrack;

//  PURPOSE:  To hold 'true' while the simulation should continue or 'false'
//	otherwise.
  bool			shouldContinue;

//  PURPOSE:  To hold the array of pthreads.
//  YOUR CODE HERE TO DEFINE AN ARRAY OF 'NUM_TRAINS' pthreads
  pthread_t trainId[NUM_TRAINS];
//  PURPOSE:  To hold the lock that controls which thread can execute
//  	'print()'.
//  YOUR CODE HERE TO DEFINE A MUTEX FOR 'print()' METHOD:
  pthread_mutex_t printLock;
//  II.  Disallowed auto-generated methods:
//  No copy constructor:
  MassTransit			(const MassTransit&
    );

//  No copy assignment op:
  MassTransit&			operator=
  (const MassTransit&
    );

  protected :
//  III.  Protected methods:

  public :
//  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
//  PURPOSE:  To initialize '*this' to the beginning state of the mass
//	transit simulator.  Defines 'Track'-and-'Station' instance topology and 
  MassTransit			()
  throw();

//  PURPOSE:  To release resources.  No parameters.  No return value.
  ~MassTransit			()
  throw();

//  V.  Accessors:
//  PURPOSE:  To return 'true' while the simulation should continue or 'false'
//	otherwise.
  bool		getShouldContinue
  ()
  const
  throw()
  { return(shouldContinue); }

//  VI.  Mutators:


//  VII.  Methods that do main and misc. work of class.
//  PURPOSE:  To display the current state of '*this' MassTransit system.
//	No parameters.  No return value.
//  YOUR CODE SOMEWHERE IN HERE TO LOCK AND UNLOCK YOUR MUTEX.
//  WHAT NEEDS TO BE PROTECTED?
  void		print		()
  throw();

//  PURPOSE:  To run '*this' MassTransit simulation for 'numSecs' seconds.
//	No return value.
  void		simulate	(uint		numSecs
    )
  throw(const char*);

//  PURPOSE:  To update '*this' MassTransit system after a 'Train' instance
//	has moved.  No parameters.  No return value.
  void		update		();

};
