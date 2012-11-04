#include <stdio.h>
#include "node.h"

node *ROOT_NODE;

int main() {
	yyparse();
	printf("ROOT_NODE: ins = %d, arg1 = %d, arg2 = %d\n", ROOT_NODE->ins, ROOT_NODE->arg1, ROOT_NODE->arg2);
	//printf("ROOT_NODE->arg1: ins = %d, arg1 = %d, arg2 =%d\n", ROOT_NODE->arg1->ins, ROOT_NODE->arg1->arg1, ROOT_NODE->arg1->arg2);
	//printf("ROOT_NODE->arg1->arg1->arg1: ins = %d, arg1 = %d, arg2 = %d, strval = %s\n",
	//		ROOT_NODE->arg1->arg1->arg1->ins,
	//		ROOT_NODE->arg1->arg1->arg1->arg1,
	//		ROOT_NODE->arg1->arg1->arg1->arg2,
	//		ROOT_NODE->arg1->arg1->arg1->arg1->strval);
	parse_node(ROOT_NODE);
	system("nasm -f elf a.out.asm");
	system("gcc a.out.o");
}
