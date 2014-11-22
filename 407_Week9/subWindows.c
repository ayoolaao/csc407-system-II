/*
Compile with
$ gcc subWindows.c -o subWindows -lncurses
*/

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define LINE_LEN 10

int main()
{
	char line[LINE_LEN];
	int i;
	WINDOW *windPtr1, *windPtr2;
	initscr();
	cbreak();	// Turn off the buffering
	clear();
	windPtr1 = newwin(5, 10, 4, 10);
	windPtr2 = newwin(5, 10, 14, 50);
	scrollok(windPtr1, TRUE);
	scrollok(windPtr2, TRUE);
	for (i = 0; i < 80; i++)
	{
		snprintf(line, LINE_LEN, " %d", i);
		waddstr(((i%2)==0) ? windPtr1 : windPtr2, line);
		wrefresh(((i%2)==0)? windPtr1 : windPtr2);
		usleep(400000);
	}

	delwin(windPtr1);	// delete windows 
	delwin(windPtr2);

	endwin();

	return(EXIT_SUCCESS);

}

