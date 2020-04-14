#include "unit_def"
#include "avl.h"
#include "rand_mem.h"
#include <string.h>

void* test_node_dump (node_t* node, void* args) {	
	FILE* out = (FILE*) args;
	if (out == NULL)
		return NULL;

	printf(      "{%d} ", node -> key);
	fprintf(out, "{%d} ", node -> key);

	if (node -> left != NULL) {
		printf(      "{%d} ", node -> left -> key);
		fprintf(out, "{%d} ", node -> left -> key);
	}
	else {
		printf(      "{} ");
		fprintf(out, "{} ");
	}

	if (node -> right != NULL) {
		printf(      "{%d} ", node -> right -> key);
		fprintf(out, "{%d} ", node -> right -> key);
	}
	else {
		printf(      "{} ");
		fprintf(out ,"{} ");
	}

	printf(      "\n");
	fprintf(out, "\n");
	return NULL;
}

void unit_test(int j) {
	node_t* node = NULL;

	//open origin test file input
	char test_name[TEST_NAME_MAX_SIZE] = TEST_PATH;
	char test_name_n[TEST_NAME_MAX_SIZE] = "";
	sprintf(test_name_n, "%d", j);
	strcat(test_name, test_name_n);
	FILE* test = fopen(test_name, "r");

	
	//open origin test file output
	char ans_test_name[ANS_TEST_NAME_MAX_SIZE] = TEST_ANS_PATH;
	char ans_test_name_n[ANS_TEST_NAME_MAX_SIZE] = "";
	sprintf(ans_test_name_n, "%d", j);
	strcat(ans_test_name, ans_test_name_n);
	FILE* ans_test = fopen(ans_test_name, "r");
	

	//make test file output
	char this_ans_test_name[THIS_ANS_TEST_NAME_MAX_SIZE] = TMP_ANS_PATH;
	char this_ans_test_name_n[THIS_ANS_TEST_NAME_MAX_SIZE] = "";
	sprintf(this_ans_test_name_n, "%d", j);
	strcat(this_ans_test_name, this_ans_test_name_n);
	FILE* this_ans_test = fopen(this_ans_test_name, "w");
	

	//putting elements to the tree
	int x = 0;
	int i = 0;
	int input[TEST_MAX_INPUT] = {};

	printf("\n\nTESTING\n%s\n\n", test_name);

	//futher loop requires "rand_mem.h"
	while (fscanf(test, "%d", &x) == 1) {
		if (i == 0)
			node = rand_node_init(x);
		else
			node = rand_insert(node, x);
		input[i] = x;
		++i;
	
	}

	//managing tree with test_node_dump
	visitor(node, test_node_dump, this_ans_test);

	//freeing memory
	for (int k = 0; k < i; ++k) {
		node = remove_node(node, input[k]);
	}

	fclose(test);
	fclose(ans_test);
	fclose(this_ans_test);
}

int main() {


	for (int j = 1; j <= NUM_OF_UNIT_TESTS; ++j)
		unit_test(j);
	
	//null test
	node_t* node = NULL;
	remove_node(node, 0);
	test_node_dump(node, NULL);

	return 0;
}
