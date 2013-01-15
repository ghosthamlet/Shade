#ifndef TYPE_H
#define TYPE_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "utils.h"

struct type_decl;

typedef struct func_type {
	struct type_decl *rtype;
	list_node *args;
} func_type;

typedef struct type_decl {
	int size;
	char *typecode;
	struct type_decl *abase;
	func_type *ftype;
} type_decl;

type_decl *type_void();
type_decl *type_int();
type_decl *type_char();
type_decl *type_array(type_decl *base, int length);
type_decl *type_func(type_decl *ret, int num, ...);
#endif
