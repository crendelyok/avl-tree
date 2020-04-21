#ifndef RAND_MEM_H
#define RAND_MEM_H

#include "avl.h"

#define MY_RANDOM_MALLOC

#define __TIMEOUT__ 4096
tree_t* rand_tree_init(int);
int rand_insert(tree_t*, int);
void* my_malloc(size_t, int);


#endif //RAND_MEM_H
