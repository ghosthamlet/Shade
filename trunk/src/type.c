#include "type.h"

type_decl *TYPE_VOID = NULL;
type_decl *TYPE_INT = NULL;
type_decl *TYPE_CHAR = NULL;

type_decl *type_void()
{
	if (TYPE_VOID == NULL) {
		TYPE_VOID = (type_decl *) malloc(sizeof(type_decl));
		TYPE_VOID->size = 0;
		TYPE_VOID->typecode = "void";
	}
	return TYPE_VOID;
}

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
	ret->abase = base;
	char sprintf_fodder[100];
	sprintf(sprintf_fodder, "%s[%d]", base->typecode, length);
	ret->typecode = sprintf_fodder;
	return ret;
}

type_decl *type_func(type_decl *rtype, int num, ...)
{
	type_decl *ret = (type_decl *) malloc(sizeof(type_decl));
	ret->size = sizeof(void *);
	ret->ftype = (func_type *) malloc(sizeof(func_type));
	ret->ftype->rtype = rtype;
	ret->ftype->args = make_list();

	va_list args;
	va_start(args, num);
	
	int c;
	for (c = 0; c < num; c++) {
		insert_list(ret->ftype->args, (void *) va_arg(args, type_decl *));
	}

	return ret;
}
