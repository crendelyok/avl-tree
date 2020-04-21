#include "unit_def"
#include "avl.h"
#include "rand_mem.h"
#include <string.h>

#include "debug_unit_test"


static void* test_node_dump (node_t* node, void* args) {	
	FILE* out = (FILE*) args;
	if (out == NULL)
		return NULL;

	DBG printf(  "{%d} ", node -> key);
	fprintf(out, "{%d} ", node -> key);

	if (node -> left != NULL) {
		DBG printf(  "{%d} ", node -> left -> key);
		fprintf(out, "{%d} ", node -> left -> key);
	}
	else {
		DBG printf(  "{} ");
		fprintf(out, "{} ");
	}

	if (node -> right != NULL) {
		DBG printf(  "{%d} ", node -> right -> key);
		fprintf(out, "{%d} ", node -> right -> key);
	}
	else {
		DBG printf(  "{} ");
		fprintf(out ,"{} ");
	}

	DBG printf(  "\n");
	fprintf(out, "\n");
	return NULL;
}


static void check_unit_test(int j, FILE* origin, FILE* created) {
	assert(origin != NULL);
	assert(created != NULL);

	rewind(created);
	rewind(origin);

	printf("UNIT TEST NUMBER %d :", j);

	int ch_origin = 0, ch_created = 0;
	int line = 1;
	while (!feof(origin) && !feof(created) && (ch_origin == ch_created)) {
		ch_origin = fgetc(origin);
		ch_created = fgetc(created);
		if (ch_origin == '\n' && ch_created == '\n')
			line++;
	}	
	if (ch_origin == ch_created)
		printf("SUCCESS\n");
	else
		printf("FAILED on the line number %d\n", line);
}

static void unit_test(int j) {
	tree_t* tree = NULL;

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
	FILE* this_ans_test = fopen(this_ans_test_name, "w+");
	

	//putting elements to the tree
	int x = 0;
	int i = 0;
	int input[TEST_MAX_INPUT] = {};

	DBG printf("\n\nTESTING\n%s\n\n", test_name);

	//futher loop requires "rand_mem.h"
	while (fscanf(test, "%d", &x) == 1) {
		if (i == 0)
			tree = rand_tree_init(x);
		else
			rand_insert(tree, x);
		input[i] = x;
		++i;	
	}

	//managing tree with test_node_dump
	visitor(tree, test_node_dump, this_ans_test);

	check_unit_test(j, ans_test, this_ans_test);	

	for (int k = 0; k < i; ++k)
		remove_by_key(tree, input[k]);

	for (int k = 0; k < i; ++k)
		rand_insert(tree, input[k]);
	tree_destroy(tree);


	fclose(test);
	fclose(ans_test);
	fclose(this_ans_test);
}

void null_test() {

	tree_t* tree = NULL;
	tree_destroy(tree);

	node_t* node = NULL;
	test_node_dump(node, NULL);
	
	rand_insert(tree, 666);

	visitor(tree, test_node_dump, NULL);
	visitorLRN(tree, test_node_dump, NULL);
		
	tree = calloc(1, sizeof(tree_t));
	visitor(tree, NULL, NULL);
	visitorLRN(tree, NULL, NULL);
	tree -> head = NULL;
	remove_by_key(tree, 123);
	tree_destroy(tree); //
	tree = NULL;
	remove_by_key(tree, 1);

	insert(tree, 666);
	tree = rand_tree_init(123);
	visitor(tree, NULL, NULL);
	visitorLRN(tree, NULL, NULL);
	tree_destroy(tree);
	tree = NULL;

	visitorLRN(tree, NULL, NULL);
}

int main() {

	
	for (int j = 1; j <= NUM_OF_UNIT_TESTS; ++j)
		unit_test(j);
	
	null_test();

	return 0;
}
