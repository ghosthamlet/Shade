#include "treewalker.h"

#define BIN_OP(op) \
	generate_line("push ebx");\
	parse_node(n->arg2);\
	generate_line("mov ebx, eax");\
	parse_node(n->arg1);\
	generate_line(op " eax, ebx");\
	generate_line("pop ebx");

int IF_END_COUNT = 0;
int LOOP_COUNT = 0;
int LAMBDA_COUNT = 0;

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
		case EXPRESSION_LIST:
			debug("EXPRESSION_LIST");
			if (n->arg1 != NULL) {
				debug("n->arg1->ins=%d", n->arg1->ins);
				parse_node(n->arg1);
				generate_line("push eax");
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
			debug("EXTERNAL_FUNCTION: %s", n->arg1->val.strval);
			sprintf(sprintf_fodder, "extern %s", n->arg1->val.strval);
			generate_extern(sprintf_fodder);
			declare_scalar(n->arg1->val.strval, n->type);
			sprintf(sprintf_fodder, "mov eax, %s", n->arg1->val.strval);
			generate_line(sprintf_fodder);
			assign_scalar(n->arg1->val.strval);
			break;
		case LAMBDA_EXPR:
			sprintf(sprintf_fodder, "global _lambda_%d\n_lambda_%d:", LAMBDA_COUNT, LAMBDA_COUNT);
			generate_lambda(sprintf_fodder);
			set_lambda_context(1);
			push_symtab();
			generate_line("push ebp\nmov ebp,esp\nsub esp,0x40");
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("mov esp,ebp\npop ebp");
			generate_line("ret");
			pop_symtab();
			set_lambda_context(0);
			sprintf(sprintf_fodder, "mov eax, _lambda_%d", LAMBDA_COUNT);
			generate_line(sprintf_fodder);
			LAMBDA_COUNT++;
			break;
		case DECLARE_FUNCTION:
			sprintf(sprintf_fodder, "global _%s\n_%s:", n->arg1->val.strval, n->arg1->val.strval);
			generate_func(sprintf_fodder);
			declare_scalar(n->arg1->val.strval, n->type);
			sprintf(sprintf_fodder, "mov eax, _%s", n->arg1->val.strval);
			generate_line(sprintf_fodder);
			assign_scalar(n->arg1->val.strval);
			set_func_context(1);
			push_symtab();
			parse_node(n->arg2);
			pop_symtab();
			set_func_context(0);
			break;
		case IDENT_LIST:
			temp1 = 8;
			for (tempnode = n; tempnode != NULL; tempnode = tempnode->arg2) {
				debug("IDENT_LIST: %s", tempnode->arg1->val.strval);
				declare_scalar(tempnode->arg1->val.strval, tempnode->type);
				sprintf(sprintf_fodder, "mov eax, dword [ebp+%d]", temp1);
				generate_line(sprintf_fodder);
				assign_scalar(tempnode->arg1->val.strval);
				temp1 += tempnode->type->size;
			}
			break;
		case FUNCTION_BODY:
			generate_line("push ebp\nmov ebp,esp\nsub esp,0x40");
			parse_node(n->arg1);
			parse_node(n->arg2);
			generate_line("mov esp,ebp\npop ebp");
			generate_line("ret");
			break;
		case DECLARE_VECTOR:
			debug("DECLARE_VECTOR");
			declare_vector(n->arg1->val.strval, n->type);
			break;
		case DECLARE_SCALAR:
			debug("DECLARE_SCALAR");
			for (tempnode = n->arg1; tempnode != NULL; tempnode = tempnode->arg2) {
				debug("name = %s", tempnode->arg1->val.strval);
				declare_scalar(tempnode->arg1->val.strval, tempnode->type);
			}
			break;
		case CONST_INTEGER:
			debug("CONST_INTEGER: val=%d\n", n->val.ival);
			push_int(n->val.ival);
			break;
		case CONST_DOUBLE:
			//TODO: IMPLEMENT
			break;
		case CONST_STRING:
			debug("CONST_STRING: val=%s\n", n->val.strval);
			push_string(n->val.strval);
			break;
		case GET_SCALAR:
			debug("GET_SCALAR");
			get_scalar(n->arg1->val.strval);
			break;
		case GET_VECTOR:
			debug("GET_VECTOR");
			parse_node(n->arg1->arg2);
			get_vector(n->arg1->arg1->val.strval);
			break;
		case CALL_FUNCTION:
			debug("CALL_FUNCTION: %s", n->arg1->val.strval);
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			call_function(n->arg1->val.strval);
			generate_line("pop ebx");
			break;
		case ASSIGN_SCALAR:
			debug("ASSIGN_SCALAR");
			parse_node(n->arg2);
			assign_scalar(n->arg1->val.strval);
			break;
		case ASSIGN_VECTOR:
			debug("ASSIGN_VECTOR");
			generate_line("push ebx");
			parse_node(n->arg1->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg2);
			assign_vector(n->arg1->arg1->val.strval);
			generate_line("pop ebx");
			break;
		case IF:
			parse_node(n->arg1);
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
			generate_line("cmp eax, 0");
			sprintf(sprintf_fodder, "jz __end%d", temp1);
			generate_line(sprintf_fodder);
			parse_node(n->arg2);
			sprintf(sprintf_fodder, "jmp __start%d", temp1);
			generate_line(sprintf_fodder);
			sprintf(sprintf_fodder, "__end%d:", temp1);
			generate_line(sprintf_fodder);
			break;
		case RETURN:
			parse_node(n->arg1);
			return_statement();
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
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			compare("sete");
			generate_line("pop eax");
			break;
		case NE:
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			compare("setne");
			generate_line("pop eax");
			break;
		case LT:
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			compare("setl");
			generate_line("pop eax");
			break;
		case LE:
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			compare("setle");
			generate_line("pop eax");
			break;
		case GT:
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			compare("setg");
			generate_line("pop eax");
			break;
		case GE:
			generate_line("push ebx");
			parse_node(n->arg2);
			generate_line("mov ebx, eax");
			parse_node(n->arg1);
			compare("setge");
			generate_line("pop eax");
			break;
	}
}
