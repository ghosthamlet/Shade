#ifndef SYMTAB_H
#define SYMTAB_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "debug.h"
#include "utils.h"
typedef struct symtab_entry {
	char name[256];
	char location[256];
	type_decl *type;
} symtab_entry;

list_node *current_symtab();
void push_symtab();
void pop_symtab();
void new_symbol(char *name, char *location, type_decl *type);
symtab_entry *get_symbol_data(char *name);

char *get_symbol_location(char *name);
void set_symbol_location(char *name, char *location);

type_decl *get_symbol_type(char *name);
void set_symbol_type(char *name, type_decl *type);
#endif
