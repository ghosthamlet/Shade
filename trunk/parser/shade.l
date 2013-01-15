%{
#include "shade.tab.h"
#include "node.h"
#include "type.h"
#define TOKEN(t) yylval.token = t; return t
//[0-9]+\.[0-9]*          yylval.node_t = const_double(atof(yytext)); return TDOUBLE;
%}

%option noyywrap

%%

[ \t\n]                 ;
"parsedbg"              printf("parsedbg");
"def"                   TOKEN(TDEF);
"var"                   TOKEN(TVAR);
"ext"                   TOKEN(TEXT);
"if"                    TOKEN(TIF);
"while"                 TOKEN(TWHILE);
"Integer"               yylval.type_t = type_int(); return TINTEGER_T;
"Byte"                  yylval.type_t = type_char(); return TBYTE_T;
"Void"                  yylval.type_t = type_void(); return TVOID_T;
[a-zA-Z_][a-zA-Z0-9_]*  yylval.node_t = identifier_node(yytext); return TIDENTIFIER;
L?\"(\\.|[^\\"])*\"     yylval.node_t = const_string_node(yytext); return TSTRING;
[0-9]+                  yylval.node_t = const_integer_node(atoi(yytext)); return TINTEGER;
"->"                    TOKEN(TARROW);
"="                     TOKEN(TEQUAL);
"=="                    TOKEN(TCEQ);
"!="                    TOKEN(TCNE);
"<"                     TOKEN(TCLT);
"<="                    TOKEN(TCLE);
">"                     TOKEN(TCGT);
">="                    TOKEN(TCGE);
"("                     TOKEN(TLPAREN);
")"                     TOKEN(TRPAREN);
"["                     TOKEN(TLSQUARE);
"]"                     TOKEN(TRSQUARE);
"{"                     TOKEN(TLBRACE);
"}"                     TOKEN(TRBRACE);
"."                     TOKEN(TDOT);
","                     TOKEN(TCOMMA);
";"                     TOKEN(TSEMICOLON);
"+"                     TOKEN(TPLUS);
"-"                     TOKEN(TMINUS);
"*"                     TOKEN(TMUL);
"/"                     TOKEN(TDIV);
.                       printf("Unknown token!\n"); yyterminate();

%%
