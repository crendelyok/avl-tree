#include "rand_mem.h"

static void* num_of_elements(node_t* node, void* args) {
	(*(int*)args)++;
	return NULL;
}

void* my_malloc(size_t size, int rand_factor) {
        int random = rand() % MAX_RAND;
        random *= rand_factor;
        if (random == MAGIC_NUMBER) {
                return NULL;
        }
        return calloc(1, size);
}

//timeout as well
int rand_insert(tree_t* tree, int val) {
	if (tree == NULL)
		return 1;

	int allocated = 0;
        visitor(tree, num_of_elements, &allocated);

	tree_t* temp = tree;
        insert(temp, val);
        
        int allocated2 = 0;
        visitor(tree, num_of_elements, &allocated2);

	int timeout = 0;
        while (allocated == allocated2) {
		timeout++;
		assert(timeout != __TIMEOUT__);

                allocated2 = 0;
                tree = temp; 
                insert(tree, val);
                visitor(tree, num_of_elements, &allocated2);
        }
	return 0;
}

//make timeout
tree_t* rand_tree_init(int val) {
	tree_t* tree = tree_init(val);

	int timeout = 0;
	while(tree == NULL) {
		timeout++;
		assert(timeout != __TIMEOUT__);

		tree = tree_init(val);
	}
	return tree;
}


