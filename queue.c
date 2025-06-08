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

void print_queue(struct vert * h){
	struct vert * p = h;
	char buf[10] = {'\0'};
	int num = 0;

	//clear();
	if(p != NULL){
		for(;;){
			if(num == 0)
				sprintf(buf, "   %d ", p->key);
			else
				sprintf(buf, "<- %d ", p->key);
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
		mvaddstr(ACT_BEGIN, 0, "QUEUE IS EMPTY    ");
	}
	refresh();
}

void enqueue(int k, struct vert ** h){
	struct vert * p = (struct vert *)malloc(sizeof(struct vert *));
	p->key = k;
	p->next = NULL;
	struct vert * temp_p;
	temp_p = *h;
	if((*h) == NULL){
		(*h) = p;
	}else{
		while(temp_p->next != NULL){
			temp_p = temp_p->next;
		}
		temp_p->next = p;
	}
}

int dequeue(struct vert ** h){
	int ret_v;
	ret_v = (*h)->key;
	struct vert * p;
	p = *h;
	*h = (*h)->next;
	free(p);
	return ret_v;
}

void queue(){
	int elem_v;
		char ch;
		for(;;){
			clear();
			mvaddstr(0, 0, "Unidirectional linked list queue implementation.\nEnqueue operation is done to tail of list, dequeue operation is done to the head of list.");
			elem_v = rand() % 100;
			if(head != NULL)
				sprintf(s, "Press [p] to enqueue [%d] to queue, [d] to dequeue [%d] from queue [q] to finish.", elem_v, head->key);
			else
				sprintf(s, "Press [p] to push [%d] to stack or [q] to finish.", elem_v);
			mvaddstr(3, 0, s);
			s[0] = '\0';
			print_queue(head);
			refresh();
			ch = getch();
			if('q' == ch)
				break;
			else if('p' == ch){
				enqueue(elem_v, &head);
			}
			else if('d' == ch){
				if(head != NULL) dequeue(&head);
			}
		}
}
