//Computer Systems - A Programmer's Perspective
//Chapter 7: Linking
// Figure 7.1 :Example program 1: The example program consists of two source files, main.c and swap.c. The main function initializes a two-element array of ints, and then calls the swap function to swap the pair.

/* main.c */

void swap();

int buf[2] = {1, 2};

int main()
{
	swap();
	return 0;
}

