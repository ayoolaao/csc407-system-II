#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

int main()
{
	int i;
	WINDOW *windPtr1, *windPtr2;
	initscr();
	cbreak();
	clear();
	noecho();

	windPtr1 = newwin(5, 40, 4, 10);
	windPtr2 = newwin(5, 40, 15, 10);

	for(i = 0; i < 50; i++)
	{
		int ch = getch();

		waddch(windPtr1, ch);
		wrefresh(windPtr1);

		int freaky;
		if(isupper(ch)) freaky = tolower(ch);
		else freaky = toupper(ch);
		waddch(windPtr2, freaky);
		wrefresh(windPtr2);
	}

	delwin(windPtr2);
	delwin(windPtr1);

	endwin();
	return(EXIT_SUCCESS);
}
