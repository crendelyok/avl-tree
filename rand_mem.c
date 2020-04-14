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

node_t* rand_node_init(int x) {
        node_t* node = node_init(x);
        while(node == NULL)
                node = node_init(x);
        return node;
}

node_t* rand_insert(node_t* node, int x) {
        int allocated = 0;
        visitor(node, num_of_elements, &allocated);

        node_t* temp = node;
        node = insert(node, x);
        
        int allocated2 = 0;
        visitor(node, num_of_elements, &allocated2);

        while (allocated == allocated2) {
                allocated2 = 0;
                node = temp; 
                node = insert(node, x);
                visitor(node, num_of_elements, &allocated2);
        }
        return node;
}


