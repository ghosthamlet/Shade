#include <stdio.h>
#include "node.h"
#include "treewalker.h"
#include "shade.tab.h"

node *ROOT_NODE;

int main(int argc, char *argv[]) {
	extern FILE *yyin;

	if (argc >= 2) {
		yyin = fopen(argv[1], "r");
	}
	
	yyparse();
	if (ROOT_NODE != NULL) {
		parse_node(ROOT_NODE);
		system("nasm -g -f elf a.out.asm");
		system("cc -m32 -o a.out a.out.o");
	}
	return 0;
}
