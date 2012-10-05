#include "treewalker.h"
void parse_node(node *n) {
    printf("NODE: ins = %d, arg1 = %d, arg2 = %d\n", n->ins, n->arg1, n->arg2);
    char *sprintf_fodder = (char *) malloc(sizeof(char) * 1024);
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
			break;
		case STATEMENT_LIST:
            if (n->arg1 != NULL) {
                assert(n->arg2 != NULL);
                parse_node(n->arg1);
                parse_node(n->arg2);
            }
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
		case DECLARE_INTEGER:
            //TODO: IMPLEMENT
			break;
		case DECLARE_DOUBLE:
            //TODO: IMPLEMENT
			break;
		case DECLARE_STRING:
            //TODO: IMPLEMENT
			break;
		case CONST_INTEGER:
            printf("CONST_INTEGER: val=%d\n", *((int *) (n->val)));
            push_int(*((int *) (n->val)));
			break;
		case CONST_DOUBLE:
            //TODO: IMPLEMENT
            //push_const_double(*((int *) (n->val)));
			break;
		case GET_VARIABLE:
            sprintf(sprintf_fodder, "shget %s", *((char *) (n->val))); 
            generate_line(sprintf_fodder);
			break;
		case CALL_FUNCTION:
            //TODO: IMPLEMENT
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
            parse_node(n->arg1);
            parse_node(n->arg2);
            printf("PLUS: arg1->ins=%d, arg2->ins=%d\n", n->arg1->ins, n->arg2->ins);
            printf("PLUS: arg1=%d, arg2=%d\n", *((int *) (n->arg1->val)), *((int *) (n->arg2->val)));
            generate_line("shcall add");
            push_name("uscore");
			break;
		case MINUS:
            sprintf(sprintf_fodder, "shcall sub,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case MUL:
            sprintf(sprintf_fodder, "shcall mul,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case DIV:
            sprintf(sprintf_fodder, "shcall div,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case EQ:
            sprintf(sprintf_fodder, "shcall eq,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case NE:
            sprintf(sprintf_fodder, "shcall ne,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case LT:
            sprintf(sprintf_fodder, "shcall lt,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case LE:
            sprintf(sprintf_fodder, "shcall le,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case GT:
            sprintf(sprintf_fodder, "shcall gt,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
		case GE:
            sprintf(sprintf_fodder, "shcall ge,%d,%d", *((int *) (n->val)), *((int *) (n->val)));
            generate_line(sprintf_fodder);
            push_name("uscore");
			break;
	}
}
