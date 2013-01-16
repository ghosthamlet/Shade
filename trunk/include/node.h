#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "type.h"
#include "symtab.h"
#include "debug.h"
#include "utils.h"

typedef enum instruction {
	MAIN_PROGRAM,
	STATEMENT_LIST,
	BLOCK,
	EXPRESSION_LIST,
	EXTERNAL_FUNCTION,
	DECLARE_FUNCTION,
	FUNCTION_BODY,
	DECLARE_SCALAR,
	DECLARE_VECTOR,
	GET_SCALAR,
	GET_VECTOR,
	ASSIGN_SCALAR,
	ASSIGN_VECTOR,
	CONST_INTEGER,
	CONST_DOUBLE,
	CONST_STRING,
	IDENTIFIER,
	IDENT_LIST,
	CALL_FUNCTION,
	SUBSCRIPT_ARRAY,
	LAMBDA_EXPR,
	IF,
	WHILE,
	RETURN,
	PLUS,
	MINUS,
	MUL,
	DIV,
	EQ,
	NE,
	LT,
	LE,
	GT,
	GE
} instruction;

typedef union value {
	int ival;
	char strval[256];
	double dval;
} value;

typedef struct node {
	instruction ins;
	struct node *arg1;
	struct node *arg2;
	value val;
	type_decl *type;
} node;

value null_value();
value int_value(int i);
value str_value(char *s);
value double_value(double d);

node *make_node(instruction ins, node *arg1, node *arg2, value val, type_decl *type);

node *const_integer_node(int val);
node *const_string_node(char *val);

node *identifier_node(char *name);

#endif
