%{
	#include "node.h"
	#include "type.h"
	#include <stdio.h>
	extern int yylex();
	void yyerror(const char *s) { printf("ERROR: %s\n", s); }
	extern node *ROOT_NODE;
%}

%union value {
	int token;
	struct node *node_t;
	struct type_decl *type_t;
}

%token <token> END

%token <node_t> TIDENTIFIER
%token <node_t> TINTEGER
%token <node_t> TSTRING

%token <type_t> TINTEGER_T TBYTE_T

%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLSQUARE TRSQUARE TLBRACE TRBRACE TCOMMA TSEMICOLON TDOT
%token <token> TPLUS TMINUS TMUL TDIV

%token <token> TEXT TDEF TVAR
%token <token> TIF TWHILE

%token <token> TARROW

%type <token> operator

%type <node_t> program

%type <node_t> expr
%type <node_t> ident
%type <node_t> numeric

%type <node_t> stmt
%type <node_t> stmts
%type <node_t> block
%type <node_t> control_structure

%type <type_t> scalar_type
%type <type_t> vector_type
%type <type_t> type

%type <node_t> ident_list

%type <node_t> var_decl

%type <node_t> func_decl

%type <node_t> external_decl

%type <node_t> subscript_array

%type <node_t> call_args

%left TPLUS TMINUS
%left TMUL TDIV

%start program

%error-verbose

%%

program : stmts {ROOT_NODE = make_node(MAIN_PROGRAM, $1, NULL, 0, NULL);}
	;

stmts : stmt {$$ = make_node(STATEMENT_LIST, $1, NULL, 0, NULL);}
      | stmts stmt {$$ = make_node(STATEMENT_LIST, $2, $1, 0, NULL);}
      ;

stmt : expr TSEMICOLON {$$ = make_node(STATEMENT, $1, NULL, 0, NULL);}
     | var_decl TSEMICOLON {$$ = make_node(STATEMENT, $1, NULL, 0, NULL);}
     | func_decl {$$ = make_node(STATEMENT, $1, NULL, 0, NULL);}
     | external_decl TSEMICOLON {$$ = make_node(STATEMENT, $1, NULL, 0, NULL);}
     | control_structure {$$ = $1;}
     | block {$$ = $1;}
     ;

control_structure : TIF expr stmt {$$ = make_node(IF, $2, $3, 0, NULL);}
		  | TWHILE expr stmt {$$ = make_node(WHILE, $2, $3, 0, NULL);}
		  ;

block : TLBRACE stmts TRBRACE {$$ = make_node(BLOCK, $2, NULL, 0, NULL);}
      | TLBRACE TRBRACE {$$ = make_node(BLOCK, NULL, NULL, 0, NULL);}
      ;

type : scalar_type {$$ = $1;} 
     | vector_type {$$ = $1;}
     ;

ident_list : /*blank*/ {$$ = make_node(IDENT_LIST, NULL, NULL, 0, NULL);}
	   | ident TARROW scalar_type {$$ = make_node(IDENT_LIST, $1, NULL, $3->size, $3->typecode);}
	   | ident TARROW scalar_type TCOMMA ident_list {$$ = make_node(IDENT_LIST, $1, $5, $3->size, $3->typecode);}
	   ;

scalar_type : TINTEGER_T {$$ = $1;}
	    | TBYTE_T {$$ = $1;}
	    ;

vector_type : type TLSQUARE TINTEGER TRSQUARE {$$ = type_array($1, $3->ival);}
	    ;

var_decl : TVAR ident_list {$$ = make_node(DECLARE_SCALAR, $2, NULL, 0, NULL);}
	 | TVAR ident TARROW vector_type {$$ = make_node(DECLARE_VECTOR, $2, NULL, $4->size, NULL);}

func_decl : TDEF ident ident_list TARROW scalar_type stmt {
	  $2->ival = $5->size;
	  $$ = make_node(DECLARE_FUNCTION, $2, make_node(FUNCTION_BODY, $3, $6, 0, NULL), 0, NULL);}
	  ;

external_decl : TEXT ident ident_list TARROW scalar_type {
	      $$ = make_node(EXTERNAL_FUNCTION, $2, NULL, 0, NULL);}
	      ;

ident : TIDENTIFIER {$$ = $1;}
      ;

numeric : TINTEGER {$$ = $1;}
/*	| TDOUBLE {$$ = $1;}*/
	;

subscript_array : ident TLSQUARE expr TRSQUARE {$$ = make_node(SUBSCRIPT_ARRAY, $1, $3, 0, NULL);}

expr : ident {$$ = make_node(GET_SCALAR, $1, NULL, 0, NULL);}
     | subscript_array {$$ = make_node(GET_VECTOR, $1, NULL, 0, NULL);}
     | ident TLPAREN call_args TRPAREN {$$ = make_node(CALL_FUNCTION, $1, $3, 0, NULL);}
     | numeric {$$ = $1;}
     | TSTRING {$$ = $1;}
     | ident TEQUAL expr {$$ = make_node(ASSIGN_SCALAR, $1, $3, 0, NULL);}
     | subscript_array TEQUAL expr {$$ = make_node(ASSIGN_VECTOR, $1, $3, 0, NULL);}
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
	  | call_args TCOMMA expr {$$ = make_node(EXPRESSION_LIST, $3, $1, 0, NULL);}
	  ;

operator : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE
	 | TPLUS | TMINUS | TMUL | TDIV
	 ;

%%
