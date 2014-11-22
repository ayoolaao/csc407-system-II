#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

int main(){
	initscr();	// Truns ncurses on
	clear();	// Clears screen
	move(10,35);	// Move cursor to row 10, column 35
	addstr("Hello world!");	//Write given text to current cursor laction
	refresh();	// VERY IMPORTANT, SEE NOTHING UNTIL DO THIS!
	sleep(10);
	endwin();	// Turns ncurses off
	return(EXIT_SUCCESS);
}
