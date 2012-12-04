#include "type.h"

type_decl *TYPE_INT = NULL;
type_decl *TYPE_CHAR = NULL;

type_decl *type_int()
{
	if (TYPE_INT == NULL) {
		TYPE_INT = (type_decl *) malloc(sizeof(type_decl));
		TYPE_INT->size = sizeof(int);
		TYPE_INT->typecode = "int";
	}
	return TYPE_INT;
}

type_decl *type_char()
{
	if (TYPE_CHAR == NULL) {
		TYPE_CHAR = (type_decl *) malloc(sizeof(type_decl));
		TYPE_CHAR->size = sizeof(char);
		TYPE_CHAR->typecode = "char";
	}
	return TYPE_CHAR;
}

type_decl *type_array(type_decl *base, int length)
{
	type_decl *ret = (type_decl *) malloc(sizeof(type_decl));
	ret->size = base->size * length;
	return ret;
}
