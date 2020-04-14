#include "avl.h"
#include "rand_mem.h"

#ifndef MY_RANDOM_MALLOC
void* my_malloc(size_t size, int rand_factor) {
	return calloc(1, size);
}
#endif //MY_RANDOM_MALLOC

int visitor(node_t* node, void* (*func)(node_t*, void*), void* args) {
	if (node == NULL) {
		return 1;
	}
	
	func(node, args);
	visitor(node -> left, func, args);
	visitor(node -> right, func, args);	

	return 0;
}


//change defined "RANDOM" in this function in avl.h 
node_t* node_init (int key) {
	node_t* node = my_malloc(sizeof(node_t), RANDOM);
	if (node == NULL)
		return NULL;
	node -> key = key;
	node -> height = 1;
	return node;
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

node_t* insert (node_t* node, int new_key) {
	if (node == NULL) 
		return node_init(new_key);
	
	if (new_key < node -> key)
		node -> left = insert(node -> left, new_key);
	else 
		node -> right = insert(node -> right, new_key);
	
	return balance(node);
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

node_t* remove_node (node_t* node, int key) {
	if (node == NULL) {
		errno = EINVAL;
		return NULL;
	}
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
