#include	<stdlib.h>
#include	<stdio.h>

class XYCoord
{
 int x; int y;
public:
 XYCoord(int nX,int nY){x=nX; y=nY;}
 int getX() const { return(x); }
 int getY() const { return(y); }

 void	print	() { printf("%d %d\n",x,getY()); }

};


int	main	()
{
  XYCoord*	xyCoordPtr	= new XYCoord(10,20);

  xyCoordPtr->print();
  (*xyCoordPtr).print();

  return(EXIT_SUCCESS);
}
