%{
	#include "node.h"
	#include "type.h"
	#include <stdio.h>
	extern int yylex();
	void yyerror(const char *s) { printf("ERROR: %s\n", s); }
	extern node *ROOT_NODE;
%}

%union token_val {
	int token;
	struct node *node_t;
	struct type_decl *type_t;
}

%token <token> END

%token <node_t> TIDENTIFIER
%token <node_t> TINTEGER
%token <node_t> TSTRING

%token <type_t> TINTEGER_T TBYTE_T TVOID_T

%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLSQUARE TRSQUARE TLBRACE TRBRACE TCOMMA TSEMICOLON TDOT
%token <token> TPLUS TMINUS TMUL TDIV

%token <token> TEXT TDEF TVAR
%token <token> TIF TWHILE

%token <token> TARROW

%type <token> operator

%type <node_t> program

%type <node_t> expr
%type <node_t> numeric

%type <node_t> stmt
%type <node_t> stmts
%type <node_t> block
%type <node_t> control_structure

%type <type_t> scalar_type
%type <type_t> vector_type
%type <type_t> func_type
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

program : stmts {ROOT_NODE = make_node(MAIN_PROGRAM, $1, NULL, null_value(), type_void());}
	;

stmts : stmt {$$ = make_node(STATEMENT_LIST, $1, NULL, null_value(), type_void());}
      | stmts stmt {$$ = make_node(STATEMENT_LIST, $2, $1, null_value(), type_void());}
      ;

stmt : expr TSEMICOLON {$$ = $1;}
     | var_decl TSEMICOLON {$$ = $1;}
     | func_decl {$$ = $1;}
     | external_decl TSEMICOLON {$$ = $1;}
     | control_structure {$$ = $1;}
     | block {$$ = $1;}
     ;

control_structure : TIF expr stmt {$$ = make_node(IF, $2, $3, null_value(), type_void());}
		  | TWHILE expr stmt {$$ = make_node(WHILE, $2, $3, null_value(), type_void());}
		  ;

block : TLBRACE stmts TRBRACE {$$ = make_node(BLOCK, $2, NULL, null_value(), type_void());}
      | TLBRACE TRBRACE {$$ = make_node(BLOCK, NULL, NULL, null_value(), type_void());}
      ;

type : scalar_type {$$ = $1;} 
     | vector_type {$$ = $1;}
     ;

ident_list : /*blank*/ {$$ = make_node(IDENT_LIST, NULL, NULL, null_value(), type_void());}
	   | TIDENTIFIER TARROW scalar_type {$$ = make_node(IDENT_LIST, $1, NULL, null_value(), $3);}
	   | TIDENTIFIER TARROW scalar_type TCOMMA ident_list {$$ = make_node(IDENT_LIST, $1, $5, null_value(), $3);}
	   ;

scalar_type : TINTEGER_T {$$ = $1;}
	    | TBYTE_T {$$ = $1;}
	    | TVOID_T {$$ = $1;}
	    | func_type {$$ = $1;}
	    ;

vector_type : type TLSQUARE TINTEGER TRSQUARE {$$ = type_array($1, $3->val.ival);}
	    ;

func_type : TLPAREN ident_list TRPAREN TARROW type {
	  type_decl *type = type_func($5, 0);
	  node *c;
	  for (c = $2; c != NULL; c = c->arg2) {
	  	insert_list(type->ftype->args, (void *) c->type);
	  }
	  $$ = type;
	  }

var_decl : TVAR ident_list {$$ = make_node(DECLARE_SCALAR, $2, NULL, null_value(), type_void());}
	 | TVAR TIDENTIFIER TARROW vector_type {$$ = make_node(DECLARE_VECTOR, $2, NULL, null_value(), $4);}

func_decl : TDEF TIDENTIFIER TLPAREN ident_list TRPAREN TARROW type stmt {
	  type_decl *type = type_func($7, 0);
	  node *c;
	  for (c = $4; c != NULL; c = c->arg2) {
	  	insert_list(type->ftype->args, (void *) c->type);
	  }
	  $$ = make_node(DECLARE_FUNCTION, $2, make_node(FUNCTION_BODY, $4, $8, null_value(), type_void()), null_value(), type);}
	  ;

external_decl : TEXT TIDENTIFIER ident_list TARROW scalar_type {
	  	type_decl *type = type_func($5, 0);
	  	node *c;
	  	for (c = $3; c != NULL; c = c->arg2) {
	  		insert_list(type->ftype->args, (void *) c->type);
	  	}
	      	$$ = make_node(EXTERNAL_FUNCTION, $2, NULL, null_value(), type);}
	      ;

numeric : TINTEGER {$$ = $1;}
/*	| TDOUBLE {$$ = $1;}*/
	;

subscript_array : TIDENTIFIER TLSQUARE expr TRSQUARE {$$ = make_node(SUBSCRIPT_ARRAY, $1, $3, null_value(), $1->type);}

expr : TIDENTIFIER {$$ = make_node(GET_SCALAR, $1, NULL, null_value(), type_void());}
     | subscript_array {$$ = make_node(GET_VECTOR, $1, NULL, null_value(), type_void());}
     | TIDENTIFIER TLPAREN call_args TRPAREN {$$ = make_node(CALL_FUNCTION, $1, $3, null_value(), type_void());}
     | numeric {$$ = $1;}
     | TSTRING {$$ = $1;}
     | TIDENTIFIER TEQUAL expr {$$ = make_node(ASSIGN_SCALAR, $1, $3, null_value(), $1->type);}
     | subscript_array TEQUAL expr {$$ = make_node(ASSIGN_VECTOR, $1, $3, null_value(), $1->type);}
     | expr operator expr {switch ($2) {
case TPLUS:
	$$ = make_node(PLUS, $1, $3, null_value(), $1->type);
	break;
case TMINUS:
	$$ = make_node(MINUS, $1, $3, null_value(), $1->type);
	break;
case TMUL:
	$$ = make_node(MUL, $1, $3, null_value(), $1->type);
	break;
case TDIV:
	$$ = make_node(DIV, $1, $3, null_value(), $1->type);
	break;
case TCEQ:
	$$ = make_node(EQ, $1, $3, null_value(), $1->type);
	break;
case TCNE:
	$$ = make_node(NE, $1, $3, null_value(), $1->type);
	break;
case TCLT:
	$$ = make_node(LT, $1, $3, null_value(), $1->type);
	break;
case TCLE:
	$$ = make_node(LE, $1, $3, null_value(), $1->type);
	break;
case TCGT:
	$$ = make_node(GT, $1, $3, null_value(), $1->type);
	break;
case TCGE:
	$$ = make_node(GE, $1, $3, null_value(), $1->type);
	break;
};}
     | TLPAREN expr TRPAREN {$$ = $2;}
     ;

call_args : /*blank*/  {$$ = make_node(EXPRESSION_LIST, NULL, NULL, null_value(), type_void());}
	  | expr {$$ = make_node(EXPRESSION_LIST, $1, NULL, null_value(), type_void());}
	  | call_args TCOMMA expr {$$ = make_node(EXPRESSION_LIST, $3, $1, null_value(), type_void());}
	  ;

operator : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE
	 | TPLUS | TMINUS | TMUL | TDIV
	 ;

%%
