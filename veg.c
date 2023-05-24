#include <ncurses.h>
#include "veg.h"
#include "pairs.h"

void veg_selected(int y, int x)
{
	veg_select(y, x, RED_PAIR);
}

void veg_select(int y, int x, int pair)
{
	attron(COLOR_PAIR(pair));
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	y++;
	x=x-4;
	
	for (int i = 0; i < 3; i++) {
		mvprintw(y, x, "▒");
		x=x+4;
		mvprintw(y, x, "▒");
		y++;
		x=x-4;
	}
	
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	x++;
	mvprintw(y, x, "▒");
	y++;
	x=x-4;
	
	attron(COLOR_PAIR(WHITE_PAIR));
}

void veg_draw(int y, int x, int veg)
{
    switch (veg) {
		case BLANK:
            attron(COLOR_PAIR(WHITE_PAIR));
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            attron(COLOR_PAIR(WHITE_PAIR));
            break;
        case PUMPKIN:
            attron(COLOR_PAIR(GREEN_PAIR));
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, "φ");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            attron(COLOR_PAIR(YELLOW_PAIR));
            mvprintw(y, x, "▒");
            x++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, "▒");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            mvprintw(y, x, "▒");
            x++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, "▒");
            x++;
            mvprintw(y, x, " ");
            attron(COLOR_PAIR(WHITE_PAIR));
            break;
        case BEET:
            attron(COLOR_PAIR(GREEN_PAIR));
            mvprintw(y, x, "\\");
            x++;
            mvprintw(y, x, "|");
            x++;
            mvprintw(y, x, "/");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            attron(COLOR_PAIR(MAGENTA_PAIR));
            mvprintw(y, x, "┌");
            x++;
            mvprintw(y, x, "┴");
            x++;
            mvprintw(y, x, "┐");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            mvprintw(y, x, "\\");
            x++;
            mvprintw(y, x, "_");
            x++;
            mvprintw(y, x, "/");
            x++;
            mvprintw(y, x, " ");
            attron(COLOR_PAIR(WHITE_PAIR));
            break;
        case TOMATO:
            attron(COLOR_PAIR(GREEN_PAIR));
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, "¥");
            x++;
            mvprintw(y, x, " ");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            attron(COLOR_PAIR(RED_PAIR));
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, " ");
            x=x-3;
            y++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, "█");
            x++;
            mvprintw(y, x, " ");
            attron(COLOR_PAIR(WHITE_PAIR));
            break;
    }
}
