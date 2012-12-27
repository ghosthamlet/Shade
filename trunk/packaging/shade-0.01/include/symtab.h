#ifndef SYMTAB_H
#define SYMTAB_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "utils.h"
typedef struct symtab_entry {
	char name[256];
	char location[256];
	char typecode[256];
	int size;
} symtab_entry;

list_node *current_symtab();
//void import_symtab(list_node *other);
void push_symtab();
void pop_symtab();
void new_symbol(char *name, char *typecode, char *location, int size);
symtab_entry *get_symbol_data(char *name);
char *get_symbol_location(char *name);
void set_symbol_location(char *name, char *location);
#endif
