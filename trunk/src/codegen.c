#include <stdio.h>
#include "node.h"

node *ROOT_NODE;

int main() {
	yyparse();
	printf("ROOT_NODE: ins = %d, arg1 = %d, arg2 = %d\n", ROOT_NODE->ins, ROOT_NODE->arg1, ROOT_NODE->arg2);
}
