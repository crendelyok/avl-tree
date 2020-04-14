#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

//#include "rand_mem.h"

typedef struct avl_node node_t;

struct avl_node {
	int key;
	int height;
	node_t* left;
	node_t* right;
};

node_t* node_init (int);
int visitor(node_t*, void* (*func)(node_t*, void*), void*);
void* node_dump (node_t*, void*);
node_t* insert (node_t*, int);
node_t* remove_node (node_t*, int);


//RANDOM = 0 for no random
//RANDOM = 1 for no random
#define RANDOM 1
#define MAX_RAND 2
#define MAGIC_NUMBER 1

#endif //AVL_H

