#ifndef GEN_H
#define GEN_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
void generate_line(char *line);
void start_generation();
void stop_generation();
void push_int(int i);
int get_argn();
void set_argn(int i);
void inc_argn();
void dec_argn();
#endif
