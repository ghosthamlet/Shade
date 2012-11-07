#include "treewalker.h"

#define BIN_OP(op) \
	parse_node(n->arg2);\
	parse_node(n->arg1);\
	generate_line("pop eax");\
	generate_line("pop ebx");\
	generate_line(op " eax,ebx");\
	generate_line("push eax")

int IF_END_COUNT = 0;
int LOOP_COUNT = 0;

void parse_node(node *n) {
	debug("NODE: ins = %d, arg1 = %d, arg2 = %d\n", n->ins, n->arg1, n->arg2);
	char sprintf_fodder[100];
	int temp1;
	int temp2;
	node *tempnode;
	switch (n->ins) {
		case MAIN_PROGRAM:
			start_generation();
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			else {
				debug("MAIN_PROGRAM node has NULL arg1");
				exit(1);
			}
			stop_generation();
			break;
		case STATEMENT_LIST:
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			if (n->arg2 != NULL) {
				parse_node(n->arg2);
			}
			break;
		case STATEMENT:
			parse_node(n->arg1);
			break;
		case EXPRESSION_LIST:
			if (n->arg2 != NULL) {
				parse_node(n->arg2);
			}
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			break;
		case BLOCK:
			assert(n->arg1 != NULL);
			//Eventually more things can be added here, such as support
			//for lexical scoping.
			parse_node(n->arg1);
			break;
		case EXTERNAL_FUNCTION:
			sprintf(sprintf_fodder, "extern %s", n->arg1->strval);
			generate_extern(sprintf_fodder);
			break;
		case DECLARE_FUNCTION:
			sprintf(sprintf_fodder, "global %s\n%s:", n->arg1->strval, n->arg1->strval);
			generate_line(sprintf_fodder);
			generate_line("push ebp\nmov ebp,esp");
			temp1 = 0;
			tempnode = n->arg2->arg2;
			while (n != NULL) {

			sprintf(sprintf_fodder, "sub esp", n->arg
			break;
		case DECLARE_VAR:
			sprintf(sprintf_fodder, "%s: resb %d", n->arg1->strval, n->ival);
			generate_bss(sprintf_fodder);
			break;
		case CONST_INTEGER:
			debug("CONST_INTEGER: val=%d\n", n->ival);
			push_int(n->ival);
			break;
		case CONST_DOUBLE:
			//TODO: IMPLEMENT
			//push_const_double(*((int *) (n->val)));
			break;
		case CONST_STRING:
			debug("CONST_STRING: val=%s\n", n->strval);
			push_string(n->strval);
			break;
		case GET_VARIABLE:
			sprintf(sprintf_fodder, "push dword [%s]", n->arg1->strval);
			generate_line(sprintf_fodder);
			break;
		case CALL_FUNCTION:
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "call %s", n->arg1->strval);
			generate_line(sprintf_fodder);
			generate_line("push eax");
			break;
		case ASSIGN:
			parse_node(n->arg2);
			generate_line("pop eax");
			sprintf(sprintf_fodder, "mov dword [%s],eax", n->arg1->strval);
			generate_line(sprintf_fodder);
			break;
		case IF:
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("cmp eax, 0");
			//We increment IF_END_COUNT here so we can nest these.
			sprintf(sprintf_fodder, "jz __end%d", IF_END_COUNT++);
			generate_line(sprintf_fodder);
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "__end%d:", IF_END_COUNT-1);
			generate_line(sprintf_fodder);
			break;
		case WHILE:
			sprintf(sprintf_fodder, "__start%d:", LOOP_COUNT++);
			generate_line(sprintf_fodder);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("cmp eax, 0");
			sprintf(sprintf_fodder, "jz __end%d", LOOP_COUNT-1);
			generate_line(sprintf_fodder);
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "jmp __start%d", LOOP_COUNT-1);
			generate_line(sprintf_fodder);
			sprintf(sprintf_fodder, "__end%d:", LOOP_COUNT-1);
			generate_line(sprintf_fodder);
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
			parse_node(n->arg2);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("sete al");
			generate_line("movsx eax,al");
			generate_line("push eax");
			break;
		case NE:
			parse_node(n->arg2);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setne al");
			generate_line("movsx eax,al");
			generate_line("push eax");
			break;
		case LT:
			parse_node(n->arg2);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setl al");
			generate_line("movsx eax,al");
			generate_line("push eax");
			break;
		case LE:
			parse_node(n->arg2);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setle al");
			generate_line("movsx eax,al");
			generate_line("push eax");
			break;
		case GT:
			parse_node(n->arg2);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setg al");
			generate_line("movsx eax,al");
			generate_line("push eax");
			break;
		case GE:
			parse_node(n->arg2);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("pop ebx");
			generate_line("cmp eax,ebx");
			generate_line("setge al");
			generate_line("movsx eax,al");
			generate_line("push eax");
			break;
	}
}
