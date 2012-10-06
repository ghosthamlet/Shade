%{
	#include "node.h"
	#include <stdio.h>
	extern int yylex();
	void yyerror(const char *s) { printf("ERROR: %s\n", s); }
	extern node *ROOT_NODE;
	//yydebug = 1;
%}

%union value {
	int token;
	struct node *node_t;
}

%error-verbose
%debug

%token <token> END
%token <node_t> TIDENTIFIER
%token <node_t> TDOUBLE
%token <node_t> TINTEGER
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TSEMICOLON TDOT
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TIF TWHILE

%type <node_t> atom
%type <node_t> expr
%type <node_t> expr_list
%type <token> operator
%type <node_t> control_structure
%type <node_t> if while
%type <node_t> statement
%type <node_t> statement_list
%type <node_t> program

%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

atom : TDOUBLE
	 | TINTEGER
	 | TIDENTIFIER
	 ;

expr : atom {$$ = $1;}
	 | expr operator expr {switch ($2) {
case TPLUS:
	$$ = make_node(PLUS, $1, $3, 0, NULL);
	break;
case TMINUS:
	$$ = make_node(MINUS, $1, $3, 0, NULL);
	break;
case TMUL:
	$$ = make_node(MUL, $1, $3, 0, NULL);
	break;
case TDIV:
	$$ = make_node(DIV, $1, $3, 0, NULL);
	break;
case TCEQ:
	$$ = make_node(EQ, $1, $3, 0, NULL);
	break;
case TCNE:
	$$ = make_node(NE, $1, $3, 0, NULL);
	break;
case TCLT:
	$$ = make_node(LT, $1, $3, 0, NULL);
	break;
case TCLE:
	$$ = make_node(LE, $1, $3, 0, NULL);
	break;
case TCGT:
	$$ = make_node(GT, $1, $3, 0, NULL);
	break;
case TCGE:
	$$ = make_node(GE, $1, $3, 0, NULL);
	break;
};}
	 | expr TLPAREN expr_list TRPAREN {$$ = make_node(CALL_FUNCTION, $3, NULL, 0, NULL);}
	 ;

expr_list : /* blank */ {$$ = make_node(EXPRESSION_LIST, NULL, NULL, 0, NULL);}
		  | expr {$$ = make_node(EXPRESSION_LIST, $1, NULL, 0, NULL);}
		  | expr TCOMMA expr_list {$$ = make_node(EXPRESSION_LIST, $1, $3, 0, NULL);}
		  ;

operator : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE
		 | TPLUS | TMINUS | TMUL | TDIV
		 ;

control_structure : if {$$ = $1;}
				  | while {$$ = $1;}
				  ;

if : TIF TLPAREN expr TRPAREN statement {$$ = make_node(IF, $3, $5, 0, NULL);}
   ;

while : TWHILE TLPAREN expr TRPAREN statement {$$ = make_node(WHILE, $3, $5, 0, NULL);}
	  ;

statement : expr TSEMICOLON {$$ = $1;}
		  | control_structure {$$ = $1;}
		  | TLBRACE statement_list TRBRACE {$$ = make_node(BLOCK, $2, NULL, 0, NULL);}
		  ;

statement_list : /* blank */ {$$ = make_node(STATEMENT_LIST, NULL, NULL, 0, NULL);}
			   | statement statement_list {$$ = make_node(STATEMENT_LIST, $1, $2, 0, NULL);}
			   ;

program : /* blank */ {$$ = ROOT_NODE = make_node(MAIN_PROGRAM, NULL, NULL, 0, NULL); YYACCEPT;}
		| statement {$$ = ROOT_NODE = make_node(MAIN_PROGRAM, $1, NULL, 0, NULL); YYACCEPT;}
		;
%%
