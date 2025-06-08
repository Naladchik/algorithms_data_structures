#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <ncurses.h>
#include "queue.h"
#include "stack.h"
#include "binary_tree.h"

#define QUANTITY 3

typedef void (*fptr_t)(void);

char * name_list[QUANTITY] = {
		"Queue",
		"Stack",
		"Binary Tree operations"
};

fptr_t catalogue[QUANTITY] = {queue, stack, bin_tree};

void foo(){

}

static char s[100] = {'\0'};

int main(){
	initscr();
	cbreak();
	noecho();

	clear();

	mvaddstr(0, 0, "Possible to run:");

	int i = 0;

	for(; i<QUANTITY; i++){
		sprintf(s, "%d. %s\n", i, name_list[i]);
		mvaddstr(i+1, 0, s);
	}

	sprintf(s, "Use 0 to %d key to make choice.\n", QUANTITY - 1);
	mvaddstr(i+1, 0, s);
	i += 2;
	char k;
	for(;;){
		k = getch();
		mvaddstr(i, 0, "            ");
		if((((int)k - (int)'0') < QUANTITY) && (((int)k - (int)'0') >= 0))
			break;
		else
			mvaddstr(i, 0, "WRONG KEY!");
		refresh();
	}
	catalogue[k - '0']();

	refresh();
	getch();
	endwin();
	exit(0);
}
