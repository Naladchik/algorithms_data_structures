#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <ncurses.h>
#include "queue.h"

void queue(){
	clear();
	mvaddstr(0, 0, "queue()");
	refresh();
	getch();
}
