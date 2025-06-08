#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <ncurses.h>
#include <time.h>
#include "queue.h"

#define ACT_BEGIN 5

static char s[300] = {'\0'};

struct vert{
	int key;
	struct vert * next;
};

static struct vert * head = NULL;

void print_stack(struct vert * h){
	struct vert * p = h;
	char buf[10] = {'\0'};
	int num = 0;

	//clear();
	if(p != NULL){
		for(;;){
			if(num == 0)
				sprintf(buf, "   %d ", p->key);
			else
				sprintf(buf, "-> %d ", p->key);
			strcat(s, buf);
			num++;
			if(num % 15 == 0){
				strcat(s, "\n");
			}
			p = p->next;
			if(p == NULL)break;
		}
		mvaddstr(ACT_BEGIN, 0, s);
	}else{
		mvaddstr(ACT_BEGIN, 0, "STACK IS EMPTY    ");
	}
	refresh();
}

void push(int k, struct vert ** h){
	struct vert * p = (struct vert *)malloc(sizeof(struct vert *));
	p->key = k;
	p->next = *h;
	*h = p;
}

int pop(struct vert ** h){
	int ret_v;
	ret_v = (*h)->key;
	struct vert * p;
	p = *h;
	*h = (*h)->next;
	free(p);
	return ret_v;
}

void stack(){
	int push_v;
	char ch;
	for(;;){
		clear();
		mvaddstr(0, 0, "Unidirectional linked list stack implementation.\nPush and pop operations are done to the head of list.");
		push_v = rand() % 100;
		if(head != NULL)
			sprintf(s, "Press [p] to push [%d] to stack, [d] to pop [%d] stack or [q] to finish.", push_v, head->key);
		else
			sprintf(s, "Press [p] to push [%d] to stack or [q] to finish.", push_v);
		mvaddstr(3, 0, s);
		s[0] = '\0';
		print_stack(head);
		refresh();
		ch = getch();
		if('q' == ch)
			break;
		else if('p' == ch){
			push(push_v, &head);
		}
		else if('d' == ch){
			if(head != NULL) pop(&head);
		}
	}

}
