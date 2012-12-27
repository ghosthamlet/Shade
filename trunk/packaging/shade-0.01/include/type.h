#ifndef TYPE_H
#define TYPE_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct type_decl {
	int size;
	char *typecode;
	struct type_decl *abase;
} type_decl;

type_decl *type_int();
type_decl *type_char();
type_decl *type_array(type_decl *base, int length);
#endif
