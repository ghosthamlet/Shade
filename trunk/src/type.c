#include "type.h"

type_decl *type_int()
{
	type_decl *ret = (type_decl *) malloc(sizeof(type_decl));
	ret->size = sizeof(int);
}
