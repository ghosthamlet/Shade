%{
	#include "node.h"
	#include <stdio.h>
	extern int yylex();
	void yyerror(const char *s) { printf("ERROR: %s\n", s); }
	extern node *ROOT_NODE;
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
%token <token> TDECLARE

%type <node_t> program
%type <node_t> stmts
%type <node_t> stmt
%type <node_t> block
%type <node_t> var_decl
%type <node_t> ident
%type <node_t> numeric
%type <node_t> expr
%type <node_t> call_args
%type <token> operator

%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : stmts {ROOT_NODE = make_node(MAIN_PROGRAM, $1, NULL, 0, NULL);}
	;

stmts : stmt {$$ = make_node(STATEMENT_LIST, $1, NULL, 0, NULL);}
      | stmts stmt {$1->arg2 = make_node(STATEMENT_LIST, $2, NULL, 0, NULL);}
      ;

stmt : var_decl TSEMICOLON {$$ = make_node(STATEMENT, $1, NULL, 0, NULL);}
     | expr TSEMICOLON {$$ = make_node(STATEMENT, $1, NULL, 0, NULL);}
     | block {$$ = $1;}
     ;

block : TLBRACE stmts TRBRACE {$$ = make_node(BLOCK, $2, NULL, 0, NULL);}
      | TLBRACE TRBRACE {$$ = make_node(BLOCK, NULL, NULL, 0, NULL);}
      ;

var_decl : ident ident {$$ = make_node(DECLARE_VAR, $1, $2, 0, NULL);}
	 ;

ident : TIDENTIFIER {$$ = $1;}
      ;

numeric : TINTEGER {$$ = $1;}
/*	| TDOUBLE {$$ = $1;}*/
	;

expr : ident TEQUAL expr {$$ = make_node(ASSIGN, $1, $3, 0, NULL);}
     | ident TLPAREN call_args TRPAREN {$$ = make_node(CALL_FUNCTION, $1, $3, 0, NULL);}
     | ident {$$ = make_node(GET_VARIABLE, $1, NULL, 0, NULL);}
     | numeric {$$ = $1;}
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
     | TLPAREN expr TRPAREN {$$ = $2;}
     ;

call_args : /*blank*/  {$$ = make_node(EXPRESSION_LIST, NULL, NULL, 0, NULL);}
	  | expr {$$ = make_node(EXPRESSION_LIST, $1, NULL, 0, NULL);}
	  | call_args TCOMMA expr {$$->arg2 = make_node(EXPRESSION_LIST, $3, NULL, 0, NULL);}
	  ;

operator : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE
	 | TPLUS | TMINUS | TMUL | TDIV
	 ;

%%
