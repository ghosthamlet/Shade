#ifndef MODULE_H
#define MODULE_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <elf.h>
#include "symtab.h"
#include "type.h"
#include "debug.h"
#include "utils.h"

void modname_to_path(char *modname);
void load_module(char *path);
void convert_asm_to_module(char *asmpath, char *path);
Elf32_Ehdr *make_elf_header(); 
#endif
