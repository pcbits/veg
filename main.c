#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <stdbool.h>
#include "pairs.h"
#include "veg.h"

#define DELAY 250000

#define COLS_DOWN 25
#define COLS_RIGHT 80

int veggies[COLS_DOWN][COLS_RIGHT];
int direction = 5;
int selected_x = 0, selected_y = 0, next_x = 0, next_y = 0;
int selected_i = 0, selected_j = 0, swaped_i = 0, swaped_j = 0;
int selected_veggie = BLANK, swaped_veggie = BLANK;
bool selected = false, swaped = false;


int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
		//mvprintw(0, 0, "i: %i", ch);
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void init (void)
{
	int i = 0, j = 0;
	
	srand(time(0));
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();
    nodelay(stdscr, TRUE);
    
    if (has_colors() == FALSE) {
        endwin();
        puts("Your terminal does not support color");
        exit(1);
    }
    start_color();

    init_pair(WHITE_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(MAGENTA_PAIR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
    
    for (i = 1; i <= COLS_DOWN; i=i+direction) {
		for (j = 1; j <= COLS_RIGHT; j=j+direction) {
			veggies[i][j] = ((rand() % (VEG_MAX - VEG_MIN + 1)) + VEG_MIN);
		}
	}
}

bool clear_matches()
{
	int i = 0, j = 0, c = 0;
	int start_j = 0, start_i = 0;
	int count_j = 1, count_i = 1;
	bool cleared = false;
	//right to left
	for (i = 1; i <= COLS_DOWN; i=i+direction) {
		for (j = 1; j <= COLS_RIGHT; j=j+direction) {
			
			if (j > 1 && veggies[i][(j-direction)] == veggies[i][j]) {
				count_j++;
				if (start_j == 0) {
					start_j = (j-direction);
				}
			} else {
				if (count_j > 2) {
					for (c = start_j; c < j; c=c+direction) {
						cleared = true;
						veggies[i][c] = BLANK;
					}
				}
				start_j = j;
				count_j = 1;
			}
			
		}
		if (count_j > 2) {
			for (c = start_j; c <= j; c=c+direction) {
				cleared = true;
				veggies[i][c] = BLANK;
			}
		}
	}
	//top to bottom
	for (j = 1; j <= COLS_RIGHT; j=j+direction) {
		for (i = 1; i <= COLS_DOWN; i=i+direction) {
			
		
			if (i > 1 && veggies[(i-direction)][j] == veggies[i][j]) {
				count_i++;
				if (start_i == 0) {
					start_i = (i-direction);
				}
			} else {
				if (count_i > 2) {
					for (c = start_i; c < i; c=c+direction) {
						cleared = true;
						veggies[c][j] = BLANK;
					}
				}
				start_i = i;
				count_i = 1;
			}
		}
		if (count_i > 2) {
			for (c = start_i; c <= i; c=c+direction) {
				cleared = true;
				veggies[c][j] = BLANK;
			}
		}
		count_i = 1;
		start_i = 1;
	}
	return cleared;
}

void draw_veggies()
{
	int i = 0, j = 0;
	for (i = 1; i <= COLS_DOWN; i=i+direction) {
		for (j = 1; j <= COLS_RIGHT; j=j+direction) {
			veg_draw(i, j, veggies[i][j]);
		}
	}
}

void update_rand_veggies()
{
	int i = 0, j = 0;
	while(clear_matches()) {
		for (i = 1; i <= COLS_DOWN; i=i+direction) {
			for (j = 1; j <= COLS_RIGHT; j=j+direction) {
				if (veggies[i][j] == BLANK) {
					veggies[i][j] = ((rand() % (VEG_MAX - VEG_MIN + 1)) + VEG_MIN);
				}
			}
		}	
	}
}

bool handle_keyboard_input()
{
	bool exit = false;
	if (kbhit()) {
		switch (getch()) {
			case 119: // w
				next_y = next_y - direction;
				if (next_y >= COLS_DOWN || next_y < 0) {
					next_y = 0;
				}
				break;
			case 115: // s
				next_y = next_y + direction;
				
				if (next_y >= COLS_DOWN || next_y < 0) {
					next_y = COLS_DOWN - direction;
				}
				break;
			case 100: // d
				next_x = next_x + direction;
				if (next_x >= COLS_RIGHT || next_x < 0) {
					next_x = COLS_RIGHT - direction;
				}
				break;
			case 97: // a
				next_x = next_x - direction;
				if (next_x >= COLS_RIGHT || next_x < 0) {
					next_x = 0;
				}
				break;
			case 32: // ' ' space
				if (selected) {
					swaped = true;
					if (next_x < 1) {
						swaped_j = 1;
					} else {
						swaped_j = next_x + 1;
					}
					if (next_y < 1) {
						swaped_i = 1;
					} else {
						swaped_i = next_y + 1;
					}
					swaped_veggie = veggies[swaped_i][swaped_j];
					
					// swap selected items
					veggies[selected_i][selected_j] = swaped_veggie;
					veggies[swaped_i][swaped_j] = selected_veggie;
					
					selected = false;
				} else {
					selected = true;
					selected_x = next_x;
					selected_y = next_y;
					if (selected_x < 1) {
						selected_j = 1;
					} else {
						selected_j = selected_x + 1;
					}
					if (selected_y < 1) {
						selected_i = 1;
					} else {
						selected_i = selected_y + 1;
					}
					selected_veggie = veggies[selected_i][selected_j];
				}
				break;
			case 113: // q
				exit = true;
				break;
		}
	}
	return exit;
}

void draw_red_cursor()
{
	if (selected) {
		veg_selected(selected_y, selected_x);
	}
}

void draw_white_cursor()
{
	veg_select(next_y, next_x, WHITE_PAIR);
}

void update_veggies()
{
	if(clear_matches() == false) {
		veggies[selected_i][selected_j] = selected_veggie;
		veggies[swaped_i][swaped_j] =  swaped_veggie;
	}
	update_rand_veggies();
}

int main(int argc, char *argv[])
{
    init();
	
    while(1) {
		update_veggies();
		
        clear();

		draw_veggies();
        if(handle_keyboard_input()) {
			goto exit_loop;
		}
		draw_red_cursor();
		draw_white_cursor();

		refresh();
		usleep(DELAY);
    }
    exit_loop:;
    endwin();
}
