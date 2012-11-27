#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"
typedef struct list_node {
	struct list_node *prev;
	struct list_node *next;
	void *data;
} list_node;
list_node *make_list_node(void *d);
list_node *make_list();
int find_list(list_node *l, void *data);
void insert_list(list_node *l, void *data);
void remove_list(list_node *l, void *data);
#endif
