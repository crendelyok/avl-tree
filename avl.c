#include "avl.h"
#include "rand_mem.h"

#ifndef MY_RANDOM_MALLOC
void* my_malloc(size_t size, int rand_factor) {
	return calloc(1, size);
}
#endif //MY_RANDOM_MALLOC

int node_visitor(node_t* node, void* (*func)(node_t*, void*), void* args) {
	if (node == NULL)
		return 1;
	
	func(node, args);
	node_visitor(node -> left, func, args);
	node_visitor(node -> right, func, args);

	return 0;
}

static int node_visitorLRN(node_t* node, void* (*func)(node_t*, void*), void* args) {
	if (node == NULL)
		return 1;
	
	node_visitorLRN(node -> left, func, args);
	node_visitorLRN(node -> right, func, args);
	func(node, args);

	return 0;
}

int visitor(tree_t* tree, void* (*func)(node_t*, void*), void* args) {
        if (tree == NULL)
                return -1;
        if (tree -> head == NULL)
                return -2;
        if (func == NULL)
                return -3;

        return node_visitor(tree -> head, func, args);
}

//copy & paste = not good
int visitorLRN(tree_t* tree, void* (*func)(node_t*, void*), void* args) {
        if (tree == NULL)
                return -1;
        if (tree -> head == NULL)
                return -2;
        if (func == NULL)
                return -3;

        return node_visitorLRN(tree -> head, func, args);
}

//change defined "RANDOM" in this function in avl.h 
static inline node_t* node_init (int key) {
	node_t* node = my_malloc(sizeof(node_t), RANDOM);
	if (node == NULL)
		return NULL;
	node -> key = key;
	node -> height = 1;
	return node;
}

tree_t* tree_init(int val) {
        tree_t* tree = my_malloc(sizeof(tree_t), RANDOM);
        if (tree == NULL)
                return NULL;

        tree -> head = node_init(val);

        if (tree -> head == NULL) {
                free(tree);
                return NULL;
        }

        return tree;
}

static inline int height (const node_t* node) {
	if (node == NULL)
		return 0;

	return node -> height;
}

static inline int bfactor (const node_t* node) {
	return height(node -> right) - height(node -> left);
}

static void fixheight (node_t* node) {
	int h_left = height(node -> left);
	int h_right = height(node -> right);
	if (h_left > h_right) 
		node -> height = h_left + 1;
	else
		node -> height = h_right + 1;
}

static node_t* rotate_left(node_t* node) {
	node_t* temp = node -> right;
	node -> right = temp -> left;
	temp -> left = node;
	fixheight(node);
	fixheight(temp);
	return temp;
}

static node_t* rotate_right(node_t* node) {
	node_t* temp = node -> left;
	node -> left = temp -> right;
	temp -> right = node;
	fixheight(node);
	fixheight(temp);
	return temp;
}

static node_t* balance(node_t* node) {
	fixheight(node);
	if (bfactor(node) == 2) {
		if (bfactor(node -> right) < 0)
			node -> right = rotate_right(node -> right);
		return rotate_left(node);
	}
	if (bfactor(node) == -2) {
		if (bfactor(node -> left) > 0)
			node -> left = rotate_left(node -> left);
		return rotate_right(node);
	}
	return node;
}

static node_t* node_insert (node_t* node, int new_key) {
	if (node == NULL) 
		return node_init(new_key);
	
	if (new_key < node -> key)
		node -> left = node_insert(node -> left, new_key);
	else 
		node -> right = node_insert(node -> right, new_key);
	
	return balance(node);
}

int insert(tree_t* tree, int val) {
        if (tree == NULL)
                return 1;

        tree -> head = node_insert(tree -> head, val);
        if (tree -> head == NULL)
                return 2;

        return 0;
}

static inline node_t* find_min (node_t* node) {
	if (node -> left != NULL)
		return find_min(node -> left);
	return node;
}

static inline node_t* remove_min (node_t* node) {
	if (node -> left == NULL)
		return node -> right;
	node -> left = remove_min(node -> left);
	return balance(node);
}

static node_t* remove_node (node_t* node, int key) {
	if (node == NULL) 
		return NULL;

	if (key < node -> key)
		node -> left = remove_node(node -> left, key);
	else if (key > node -> key) 
		node -> right = remove_node(node -> right, key);
	else {
		node_t* tmp_l = node -> left;
		node_t* tmp_r = node -> right;
		free(node);
		if (tmp_r == NULL) 
			return tmp_l;
		node_t* tmp_min = find_min(tmp_r);
		tmp_min -> right = remove_min(tmp_r);
		tmp_min -> left = tmp_l;
		return balance(tmp_min);
	}
	return balance(node);
}

int remove_by_key(tree_t* tree, int val) {
        if (tree == NULL)
                return 1;
	if (tree -> head == NULL)
		return 1;
        tree -> head = remove_node(tree -> head, val);
        return 0;
}

static void* node_destroy(node_t* node, void* args) {
	if (node == NULL)
		return NULL;
	free(node);
	return NULL;
}

int tree_destroy(tree_t* tree) {
	if (tree == NULL)
		return 1; 
	if (tree -> head == NULL) {
		free(tree);
		return 0;
	}

	visitorLRN(tree, node_destroy, NULL);
	free(tree);
	return 0;
}
