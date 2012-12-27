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
	char sprintf_fodder[100];
	int temp1;
	node *tempnode;
	switch (n->ins) {
		case MAIN_PROGRAM:
			start_generation();
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			else {
				log_err("MAIN_PROGRAM node has NULL arg1");
				exit(1);
			}
			stop_generation();
			break;
		case STATEMENT_LIST:
			if (n->arg2 != NULL) {
				parse_node(n->arg2);
			}
			if (n->arg1 != NULL) {
				parse_node(n->arg1);
			}
			break;
		case STATEMENT:
			parse_node(n->arg1);
			break;
		case EXPRESSION_LIST:
			debug("EXPRESSION_LIST");
			if (n->arg1 != NULL) {
				debug("n->arg1->ins=%d", n->arg1->ins);
				parse_node(n->arg1);
			}
			if (n->arg2 != NULL) {
				debug("n->arg2->ins=%d", n->arg2->ins);
				parse_node(n->arg2);
			}
			break;
		case BLOCK:
			debug("BLOCK");
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
			generate_func(sprintf_fodder);
			generate_func("push ebp\nmov ebp,esp\nsub esp,0x40");
			set_func_context(1);
			push_symtab();
			parse_node(n->arg2);
			pop_symtab();
			set_func_context(0);
			generate_func("mov esp,ebp\npop ebp");
			generate_func("ret");
			break;
		case FUNCTION_BODY:
			parse_node(n->arg2);
			break;
		case DECLARE_VECTOR:
			debug("DECLARE_VECTOR");
			declare_vector(n->arg1->strval, n->arg1->strval, n->ival);
			break;
		case DECLARE_SCALAR:
			debug("DECLARE_SCALAR");
			for (tempnode = n->arg1; tempnode != NULL; tempnode = tempnode->arg2) {
				declare_scalar(tempnode->arg1->strval, tempnode->strval, tempnode->ival);
			}
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
		case GET_SCALAR:
			debug("GET_SCALAR");
			get_scalar(n->arg1->strval);
			break;
		case GET_VECTOR:
			debug("GET_VECTOR");
			parse_node(n->arg1->arg2);
			get_vector(n->arg1->arg1->strval);
			break;
		case CALL_FUNCTION:
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "call %s", n->arg1->strval);
			generate_line(sprintf_fodder);
			generate_line("push eax");
			break;
		case ASSIGN_SCALAR:
			debug("ASSIGN_SCALAR");
			parse_node(n->arg2);
			generate_line("pop eax");
			sprintf(sprintf_fodder, "mov dword [%s],eax", get_symbol_location(n->arg1->strval));
			generate_line(sprintf_fodder);
			break;
		case ASSIGN_VECTOR:
			debug("ASSIGN_VECTOR");
			parse_node(n->arg1->arg2);
			//generate_line("pop ebx");
			//sprintf(sprintf_fodder, "mov ecx, %s", get_symbol_location(n->arg1->arg1->strval));
			//generate_line(sprintf_fodder);
			//generate_line("mov eax, 4");
			//generate_line("mul ebx");
			//generate_line("add ebx, ecx");

			generate_line("pop ebx");
			parse_node(n->arg2);
			generate_line("pop eax");
			sprintf(sprintf_fodder, "mov [%s+ebx*%d], eax", get_symbol_location(n->arg1->arg1->strval), 4);
			generate_line(sprintf_fodder);
			break;
		case IF:
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("cmp eax, 0");
			//We increment IF_END_COUNT here so we can nest these.
			temp1 = IF_END_COUNT;
			sprintf(sprintf_fodder, "jz __end%d", IF_END_COUNT++);
			generate_line(sprintf_fodder);
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "__end%d:", temp1);
			generate_line(sprintf_fodder);
			break;
		case WHILE:
			temp1 = LOOP_COUNT;
			sprintf(sprintf_fodder, "__start%d:", LOOP_COUNT++);
			generate_line(sprintf_fodder);
			parse_node(n->arg1);
			generate_line("pop eax");
			generate_line("cmp eax, 0");
			sprintf(sprintf_fodder, "jz __end%d", temp1);
			generate_line(sprintf_fodder);
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "jmp __start%d", temp1);
			generate_line(sprintf_fodder);
			sprintf(sprintf_fodder, "__end%d:", temp1);
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
