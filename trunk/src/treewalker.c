#include "treewalker.h"

#define BIN_OP(op) \
	parse_node(n->arg1);\
	parse_node(n->arg2);\
	generate_line("pop eax");\
	generate_line("pop ebx");\
	generate_line(op " eax,ebx");\
	generate_line("push eax")

void parse_node(node *n) {
	printf("NODE: ins = %d, arg1 = %d, arg2 = %d\n", n->ins, n->arg1, n->arg2);
	char sprintf_fodder[100];
	int temp1;
	int temp2;
	switch (n->ins) {
		case MAIN_PROGRAM:
			start_generation();
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			else {
				compmsg("MAIN_PROGRAM n has NULL arg1");
				exit(1);
			}
			stop_generation();
			break;
		case STATEMENT_LIST:
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			break;
		case STATEMENT:
			parse_node(n->arg1);
			break;
		case EXPRESSION_LIST:
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			if (n->arg2 != NULL) {
				parse_node(n->arg2);
			}
			break;
		case BLOCK:
			assert(n->arg1 != NULL);
			//Eventually more things can be added here, such as support
			//for lexical scoping.
			parse_node(n->arg1);
			break;
		case DECLARE_VAR:
			//TODO: IMPLEMENT
			break;
		case CONST_INTEGER:
			printf("CONST_INTEGER: val=%d\n", n->ival);
			push_int(n->ival);
			break;
		case CONST_DOUBLE:
			//TODO: IMPLEMENT
			//push_const_double(*((int *) (n->val)));
			break;
		case GET_VARIABLE:
			sprintf(sprintf_fodder, "shget %s", n->strval); 
			generate_line(sprintf_fodder);
			break;
		case CALL_FUNCTION:
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "call %s", n->arg1->strval);
			generate_line(sprintf_fodder);
			generate_line("push eax");
			break;
		case ASSIGN:
			//TODO: IMPLEMENT
			break;
		case IF:
			//TODO: IMPLEMENT
			break;
		case WHILE:
			//TODO: IMPLEMENT
			break;
		case PLUS:
			BIN_OP("add");
			break;
		case MINUS:
			BIN_OP("sub");
			break;
		case MUL:
			BIN_OP("imul");
			break;
		case DIV:
			BIN_OP("idiv");
			break;
		case EQ:
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("sete al");
			generate_line("movsx eax,al");
			break;
		case NE:
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setne al");
			generate_line("movsx eax,al");
			break;
		case LT:
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setl al");
			generate_line("movsx eax,al");
			break;
		case LE:
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setle al");
			generate_line("movsx eax,al");
			break;
		case GT:
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setg al");
			generate_line("movsx eax,al");
			break;
		case GE:
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setge al");
			generate_line("movsx eax,al");
			break;
	}
}
