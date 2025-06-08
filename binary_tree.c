#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <ncurses.h>
#include <time.h>
#include "binary_tree.h"

#define NODE_NUM 7
#define ROOT_NUM 3 //key 4, the middle because it is a binary tree

#define ACT_BEGIN 5
#define T_HIGHT 2
#define HALF_STEP 4

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
		/* 2 */ {1, 0, 0, 0, 0, 1, 0},
		/* 3 */ {0, 0, 0, 0, 0, 0, 0},
		/* 4 */ {0, 1, 0, 0, 0, 1, 0},
		/* 5 */ {0, 0, 0, 0, 0, 0, 0},
		/* 6 */ {0, 0, 0, 0, 1, 0, 1},
		/* 7 */ {0, 0, 0, 0, 0, 0, 0}
};

struct vert * create_from_matrix(){
	struct vert * v_arr = (struct vert *)malloc(sizeof(struct vert) * NODE_NUM);
//	int lr;  // may be 0 or 1 what means left or right
//	for(int i = 0; i < NODE_NUM; i++){
//		v_arr[i].key = key_matr[i];
//		v_arr[i].left = NULL;
//		v_arr[i].right = NULL;
//		lr = 0;
//		for(int j = 0; j < NODE_NUM; j++){
//			if(adj_matr[i][j]){
//				if(lr == 0){
//					v_arr[i].left = &v_arr[j];
//					lr = 1;
//				}else{
//					v_arr[i].right = &v_arr[j];
//					lr = 0;
//				}
//			}
//		}
//	}
	v_arr[0].key = 1;
	v_arr[1].key = 2;
	v_arr[2].key = 3;
	v_arr[3].key = 4;
	v_arr[4].key = 5;
	v_arr[5].key = 6;
	v_arr[6].key = 7;
	v_arr[3].left = &v_arr[1];
	v_arr[3].right = &v_arr[5];
	v_arr[1].left = &v_arr[0];
	v_arr[1].right = &v_arr[2];
	v_arr[5].left = &v_arr[4];
	v_arr[5].right = &v_arr[6];
	v_arr[0].left = NULL;
	v_arr[0].right = NULL;
	v_arr[2].left = NULL;
	v_arr[2].right = NULL;
	v_arr[4].left = NULL;
	v_arr[4].right = NULL;
	v_arr[6].left = NULL;
	v_arr[6].right = NULL;

	return &v_arr[ROOT_NUM];
}

int return_height(struct vert * h){
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

void print_crappy(struct vert * h){
//	unsigned int i = 0;
//	int j = 0;

	sprintf(s, "%d", fetch_node(h, 0, 0)->key);
	mvaddstr(ACT_BEGIN,     HALF_STEP * 3 , s);
	sprintf(s, "%d", fetch_node(h, 1, 0)->key);
	mvaddstr(ACT_BEGIN + 1, HALF_STEP * 1, s);
	sprintf(s, "%d", fetch_node(h, 1, 1)->key);
	mvaddstr(ACT_BEGIN + 1, HALF_STEP * 5, s);
	sprintf(s, "%d", fetch_node(h, 2, 0)->key);
	mvaddstr(ACT_BEGIN + 2, HALF_STEP * 0, s);
	sprintf(s, "%d", fetch_node(h, 2, 1)->key);
	mvaddstr(ACT_BEGIN + 2, HALF_STEP * 2, s);
	sprintf(s, "%d", fetch_node(h, 2, 2)->key);
	mvaddstr(ACT_BEGIN + 2, HALF_STEP * 4, s);
	sprintf(s, "%d", fetch_node(h, 2, 3)->key);
	mvaddstr(ACT_BEGIN + 2, HALF_STEP * 6, s);

//	for(unsigned int i = 0; i < T_HIGHT; i++){
//		for(int j = 0; j < (i <<= i); j++){
//
//		}
//	}
}

void bin_tree(){
	head = create_from_matrix();
	clear();
	int v = return_height(head);
	sprintf(s, "tree has hight: %d", v);
	mvaddstr(0, 0, s);
	print_crappy(head);
	refresh();
	getch();
}

//void bin_tree(){
//
//}
