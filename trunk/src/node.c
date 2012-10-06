#include "node.h"

node *make_node(instruction ins, node *arg1, node *arg2, int ival, char *strval) {
	node *r;
	if ((r = (node *) malloc(sizeof(node)))) {
		r->ins = ins;
		r->arg1 = arg1;
		r->arg2 = arg2;
		r->ival = ival;
		r->strval = strval;
		return r;
	}
	printf("Failure in make_node");
	exit(1);
}

node *const_integer(int val) {
	printf("const_integer, val is: %d\n", val);
	return make_node(CONST_INTEGER, NULL, NULL, val, NULL);
}

node *get_variable(char *name) {
	printf("get_variable, name is: %s\n", name);
	return make_node(GET_VARIABLE, NULL, NULL, 0, name);
}
