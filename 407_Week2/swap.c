//Computer Systems - A Programmer's Perspective
//Chapter 7: Linking
// Figure 7.1 :Example program 1: The example program consists of two source files, main.c and swap.c. The main function initializes a two-element array of ints, and then calls the swap function to swap the pair.

/* swap.c */
extern int buf[];

int *bufp0 = &buf[0];
int *bufp1;

void swap()
{
	int temp;

	bufp1 = &buf[1];
	temp = *bufp0;
	*bufp0 = *bufp1;
	*bufp1 = temp;
}

