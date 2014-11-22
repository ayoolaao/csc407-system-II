#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define string "A nice long, juicy string that says \"'sup!\" Go Cubs! Any other favorite team? I'm sure you don't want your instructor to go with his stream-of-conscious for too long."
const int MIN_ROW = 1;
const int MIN_COL = 1;
const int MAX_ROW = 15;
const int MAX_COL = 18;
const char QUIT = 27;

int main()
{
	int row = MIN_ROW;
	int col = MIN_COL;
	int deltaRow = +1;
	int deltaCol = +1;
	

	char c;

	initscr();
	cbreak();
	clear();
	noecho();
	move(0,5);
	addstr("Press ESC to quit"); 
	refresh();

//	for(c = getchar(); *c != QUIT; c = getchar())
	while((c =getchar()) != QUIT)
	{
		

		move(row, col);
		// wmove(stdscr, row, col);
		addch(c);
		
		refresh();

		row += deltaRow;
		col += deltaCol;

		if((row == MIN_ROW) || (row == MAX_ROW))
			deltaRow *= -1;
		if((col == MIN_COL) || (col == MAX_COL))
			deltaCol *= -1;

	}
	endwin();
	return(EXIT_SUCCESS);
}
