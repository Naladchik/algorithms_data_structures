#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>
#include "binary_tree.h"

#define NODE_NUM 7
#define ROOT_NUM 3 //key 4, the middle because it is a binary tree

#define ACT_BEGIN 5
#define HALF_STEP 2

static char s[300] = {'\0'};

struct vert{
	int key;
	struct vert * left;
	struct vert * right;
};

struct vert * head = NULL;

int key_matr[NODE_NUM] = {1, 2, 3, 4, 5, 6, 7};

int adj_matr[NODE_NUM][NODE_NUM] = {
		      /* 1  2  3  4  5  6  7 */
		/* 1 */ {0, 0, 0, 0, 0, 0, 0},
		/* 2 */ {1, 0, 1, 0, 0, 0, 0},
		/* 3 */ {0, 0, 0, 0, 0, 0, 0},
		/* 4 */ {0, 1, 0, 0, 0, 1, 0},
		/* 5 */ {0, 0, 0, 0, 0, 0, 0},
		/* 6 */ {0, 0, 0, 0, 1, 0, 1},
		/* 7 */ {0, 0, 0, 0, 0, 0, 0}
};

struct vert * create_from_matrix(){
	struct vert * v_arr = (struct vert *)malloc(sizeof(struct vert) * NODE_NUM);
	int lr;  // may be 0 or 1 what means left or right
	for(int i = 0; i < NODE_NUM; i++){
		v_arr[i].key = key_matr[i];
		v_arr[i].left = v_arr[i].right = NULL;
		lr = 0;
		for(int j = 0; j < NODE_NUM; j++){
			if(adj_matr[i][j]){
				if(lr == 0){
					v_arr[i].left = &v_arr[j];
					lr = 1;
				}else{
					v_arr[i].right = &v_arr[j];
					lr = 0;
				}
			}
		}
	}

	return &v_arr[ROOT_NUM];
}

struct vert * new_element(int k){
	struct vert * p = malloc(sizeof(struct vert *));
	p->key = k;
	p->left = p->right = NULL;
	return p;
}

struct vert * insert_element(struct vert * h, int k){
	if(h == NULL) return new_element(k);
	if(h->key == k) return h;
	if(h->key < k)
		h->right = insert_element(h->right, k);
	else
		h->left = insert_element(h->left, k);
	return h;
}

unsigned int return_height(struct vert * h){
	if(h == NULL){
		return -1;
	}

	int right_hight = return_height(h->right);
	int right_height = return_height(h->left);
	int max;
	max = (right_hight > right_height) ? right_hight : right_height;

	return (max + 1);
}

struct vert * fetch_node(struct vert * h, unsigned int layer, unsigned int shift){
	/* Attempt to fetch addresses of node by coordinates
	 * layer - 0 is root, 1 is root's children etc.
	 * shift - from left to right 0 is the most left, (layer + 1) ** 2 - 1 is the most right for current layer
	 */

	struct vert * p = h;
	// actually proper sequence of left-right should be generated
	// number of items in sequence is 'layer'
	// lefts and rights in sequence are the same as 0s and 1s in a binary form of 'shift' when we go from MSB to LSB
	unsigned int mask = ((unsigned int)1 << (layer - 1));  // b100 for layer = 3 e.g.
	for(unsigned int l_curr = 0; l_curr < layer; l_curr++){
		if(shift & mask){
			if(p->right != NULL){
							p = p->right;
						}else{
							return NULL;
						}
		}else{
			if(p->left != NULL){
							p = p->left;
						}else{
							return NULL;
						}
		}
		mask >>= 1;
	}
	return p;
}

void print_tree(struct vert * h){
	unsigned int t_height = return_height(h);
	unsigned int max_shift = 1;
	for(unsigned int i = 0; i <= t_height; i++){
		for(unsigned int j = 0; j < max_shift; j++){
			struct vert * p = fetch_node(h, i, j);
			if(p != NULL){
				sprintf(s, "%d", p->key);
			}else{
				sprintf(s, "%c", 'x');
			}
			mvaddstr(ACT_BEGIN + 2 * i, (pow(2, t_height - i) - 1 + j * pow(2, t_height - i + 1)) * HALF_STEP, s);
		}
		max_shift *= 2;
	}
}

void bin_tree(){
	//head = create_from_matrix();
	char ch;
	int elem_v;
//	srand(time(0));
//	elem_v = rand() % 100;
//	head = new_element(elem_v);
	for(;;){
		clear();
		srand(time(0));
		elem_v = rand() % 100;
		sprintf(s, "Binary tree. Press [a] to add [%d] or [q] to finish.", elem_v);
		mvaddstr(0, 0, s);
		if(head != NULL) print_tree(head);
		refresh();
		ch = getch();
		if('q' == ch){
			break;
		}else if('a' == ch){
			head = insert_element(head, elem_v);
		}
	}
}
