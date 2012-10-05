#include "node.h"

node *make_node(instruction ins, node *arg1, node *arg2, void *val, size_t type_size) {
	node *r;
	if ((r = (node *) malloc(sizeof(node)))) {
		r->ins = ins;
		r->arg1 = arg1;
		r->arg2 = arg2;
		//if (val != NULL) {
		//	memcpy(r->val, val, type_size);
		//}
		r->val = val;
        if (r->val != NULL) printf("r->val=%d\n", *((int *) r->val));
		return r;
	}
	printf("Failure in make_node");
	exit(1);
}

node *const_double(double val) {
	printf("const_double, val is: %f\n", val);
	return make_node(CONST_DOUBLE, NULL, NULL, (void *) &val, sizeof(double));
}

node *const_integer(int val) {
	printf("const_integer, val is: %d\n", val);
	return make_node(CONST_INTEGER, NULL, NULL, (void *) &val, sizeof(int));
}

node *get_variable(const char *name) {
	printf("get_variable, name is: %s\n", name);
	return make_node(GET_VARIABLE, NULL, NULL, (void *) &name, strlen(name));
}
