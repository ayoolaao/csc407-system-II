#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define string "A nice long, juicy string that says \"'sup!\" Go Cubs! Any other favorite team? I'm sure you don't want your instructor to go with his stream-of-conscious for too long."
const int MIN_ROW = 0;
const int MIN_COL = 0;
const int MAX_ROW = 15;
const int MAX_COL = 18;

int main()
{
	int row = MIN_ROW;
	int col = MIN_COL;
	int deltaRow = +1;
	int deltaCol = +1;

	char* cPtr;

	initscr();
	cbreak();
	clear();

	for(cPtr = string; *cPtr != '\0'; cPtr++)
	{
		char c = *cPtr;

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

		usleep(200000);

	}
	endwin();
	return(EXIT_SUCCESS);
}
