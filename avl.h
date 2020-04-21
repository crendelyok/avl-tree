#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>


typedef struct avl_node node_t;
typedef struct avl_tree tree_t;

struct avl_tree {
	node_t* head;
};

struct avl_node {
	int key;
	int height;
	node_t* left;
	node_t* right;
};

tree_t* tree_init(int);
int visitor(tree_t*, void* (*func)(node_t*, void*), void*);
int visitorLRN(tree_t*, void* (*func)(node_t*, void*), void*);
int insert(tree_t*, int);
int remove_by_key(tree_t*, int);
int tree_destroy(tree_t*);


//RANDOM = 0 for no random
//RANDOM = 1 for random

#define RANDOM 1
#define MAX_RAND 2
#define MAGIC_NUMBER 1

#endif //AVL_H

