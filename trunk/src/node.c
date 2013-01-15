#include "node.h"

value NULL_VALUE = {0};

value null_value()
{
	return NULL_VALUE;
}

value int_value(int i)
{
	value r;
	r.ival = i;
	return r;
}

value str_value(char *s)
{
	value r;
	if (s != NULL) {
		memset((void *) r.strval, 0x0, 256);
		memcpy(r.strval, s, strlen(s));
	}
	return r;
}

value double_value(double d)
{
	value r;
	r.dval = d;
	return r;
}

node *make_node(instruction ins, node *arg1, node *arg2, value val, type_decl *type)
{
	node *r;
	if ((r = (node *) malloc(sizeof(node)))) {
		r->ins = ins;
		r->arg1 = arg1;
		r->arg2 = arg2;
		r->val = val;
		r->type = type;
		return r;
	}
	printf("malloc failure in make_node");
	exit(1);
}

node *const_integer_node(int val)
{
	return make_node(CONST_INTEGER, NULL, NULL, int_value(val), type_int());
}

node *const_string_node(char *val)
{
	return make_node(CONST_STRING, NULL, NULL, str_value(val), type_array(type_char(), strlen(val)));
}

node *identifier_node(char *name)
{
	return make_node(IDENTIFIER, NULL, NULL, str_value(name), type_void());
}
