#ifndef RAND_MEM_H
#define RAND_MEM_H

#include "avl.h"

//define MY_RANDOM_MALLOC for random malloc
#define MY_RANDOM_MALLOC

node_t* rand_node_init(int);
node_t* rand_insert(node_t*, int);
static void* num_of_elements(node_t*, void*);
void* my_malloc(size_t, int);

#endif //RAND_MEM_H
