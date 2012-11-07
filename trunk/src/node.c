#include "node.h"

node *make_node(instruction ins, node *arg1, node *arg2, int ival, char *strval)
{
	node *r;
	if ((r = (node *) malloc(sizeof(node)))) {
		r->ins = ins;
		r->arg1 = arg1;
		r->arg2 = arg2;
		r->ival = ival;
		if (strval != NULL) {
			memcpy(r->strval, strval, strlen(strval));
		}
		return r;
	}
	printf("Failure in make_node");
	exit(1);
}

node *const_integer(int val)
{
	printf("const_integer, val is: %d\n", val);
	return make_node(CONST_INTEGER, NULL, NULL, val, NULL);
}

node *const_double(double val)
{
	printf("const_double, val is: %f\n", val);
	node *n = make_node(CONST_DOUBLE, NULL, NULL, 0, NULL);
}

node *const_string(char *val)
{
	printf("const_string, val is: %s\n", val);
	return make_node(CONST_STRING, NULL, NULL, 0, val);
}

node *identifier(char *name)
{
	printf("identifier, name is: %s\n", name);
	return make_node(IDENTIFIER, NULL, NULL, 0, name);
}
