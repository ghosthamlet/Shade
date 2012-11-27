#ifndef TYPE_H
#define TYPE_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct type_decl {
	int size;
} type_decl;

type_decl* type_int();
#endif
