#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef enum instruction {
	MAIN_PROGRAM,
	STATEMENT_LIST,
	STATEMENT,
	BLOCK,
	EXPRESSION_LIST,
	EXTERNAL_FUNCTION,
	DECLARE_FUNCTION,
	DECLARE_VAR,
	CONST_INTEGER,
	CONST_DOUBLE,
	CONST_STRING,
	GET_VARIABLE,
	IDENTIFIER,
	CALL_FUNCTION,
	ASSIGN,
	IF,
	WHILE,
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

typedef struct node {
	instruction ins;
	struct node *arg1;
	struct node *arg2;
	int ival;
	char strval[256];
	double dval;
} node;

node *make_node(instruction ins, node *arg1, node *arg2, int val, char *strval);
node *const_integer(int val);
node *const_string(char *val);
node *identifier(char *name);

#endif
