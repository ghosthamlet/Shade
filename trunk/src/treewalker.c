#include "treewalker.h"
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
            printf("PLUS: arg1->ins=%d, arg2->ins=%d\n", n->arg1->ins, n->arg2->ins);
            printf("PLUS: arg1=%d, arg2=%d\n", n->arg1->ival, n->arg2->ival);
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall add,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case MINUS:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall sub,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case MUL:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall mul,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case DIV:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall div,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case EQ:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall eq,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case NE:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall ne,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case LT:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall lt,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case LE:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall le,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case GT:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall gt,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
		case GE:
            temp1 = get_argn();
            parse_node(n->arg1);
            temp2 = get_argn();
            parse_node(n->arg2);
            sprintf(sprintf_fodder, "shcall ge,_a%d,_a%d", temp1, temp2);
            generate_line(sprintf_fodder);
            dec_argn(); dec_argn(); //Binary operator, so move stack back 2.
            push_name("uscore");
			break;
	}
}
