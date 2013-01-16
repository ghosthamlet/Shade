#include "symtab.h"

list_node *SYMBOL_TABLE_STACK[256];
int SYMBOL_STACK_INDEX = 0;

list_node *current_symtab()
{
	if (SYMBOL_TABLE_STACK[SYMBOL_STACK_INDEX] == NULL) {
		SYMBOL_TABLE_STACK[SYMBOL_STACK_INDEX] = make_list();
	}
	return SYMBOL_TABLE_STACK[SYMBOL_STACK_INDEX];
}

void push_symtab()
{
	SYMBOL_STACK_INDEX++;
}

void pop_symtab()
{
	list_node *symtab = current_symtab();
	list_node *c;
	for (c = symtab->next; c->next != NULL; c = c->next) {
		if (((symtab_entry *) c->data) != NULL) {
			c->prev->next = c->next;
			c->next->prev = c->prev;
			free((symtab_entry *) c->data);
		}
	}
	SYMBOL_STACK_INDEX--;
}

void new_symbol(char *name, char *location, type_decl *type)
{
	symtab_entry *new;
	list_node *symtab = current_symtab();
	list_node *c;
	for (c = symtab->next; c->next != NULL; c = c->next) {
		if (((symtab_entry *) c->data) != NULL) {
			if (strcmp(((symtab_entry *) c->data)->name, name) == 0) {
				log_err("attempt to redefine variable %s", name);
				return;
			}
		}
	}
	new = (symtab_entry *) malloc(sizeof(symtab_entry));
	if (new != NULL) {
		strcpy(new->name, name);
		strcpy(new->location, location);
		new->type = type;
		insert_list(symtab, new);
	} else {
		log_err("failed to allocate memory");
	}
	debug("new_symbol: name=%s, location=%s", new->name, new->location);
}

symtab_entry *get_symbol_data(char *name)
{
	debug("get_symbol_data: name=%s", name);
	list_node *symtab = current_symtab();
	list_node *c;
	for (c = symtab->next; c->next != NULL; c = c->next) {
		if (((symtab_entry *) c->data) != NULL) {
			if (strcmp(((symtab_entry *) c->data)->name, name) == 0) {
				return (symtab_entry *) c->data;
			}
		}
	}
	log_err("undefined variable %s", name);
	return NULL;
}

char *get_symbol_location(char *name)
{
	symtab_entry *sym = get_symbol_data(name);
	debug("get_symbol_location: name=%s, sym->name=%s", name, sym->name);
	debug("get_symbol_location: sym->location=%s", sym->location);
	if (sym != NULL) {
		return sym->location;
	}
	log_err("undefined variable %s", name);
}

void set_symbol_location(char *name, char *location)
{
	symtab_entry *e = get_symbol_data(name);
	if (e == NULL) {
		log_err("undefined variable %s", name);
	} else {
		strcpy(e->location, location);
	}
}

type_decl *get_symbol_type(char *name)
{
	symtab_entry *sym = get_symbol_data(name);
	if (sym != NULL) {
		return sym->type;
	}
	log_err("undefined variable %s", name);
}

void set_symbol_type(char *name, type_decl *type)
{
	symtab_entry *e = get_symbol_data(name);
	if (e == NULL) {
		log_err("undefined variable %s", name);
	} else {
		e->type = type;
	}
}
