%{
#include "shade.tab.h"
#include "node.h"
#define TOKEN(t) yylval.token = t; return t
%}

%option noyywrap

%%

[ \t\n]                 ;
"parsedbg"              
[a-zA-Z_][a-zA-Z0-9_]*  yylval.node_t = get_variable(yytext) return TIDENTIFIER;
[0-9]+\.[0-9]*          yylval.node_t = const_double(atof(yytext)); return TDOUBLE;
[0-9]+                  yylval.node_t = const_integer(atoi(yytext)); return TINTEGER;
"="                     TOKEN(TEQUAL);
"=="                    TOKEN(TCEQ);
"!="                    TOKEN(TCNE);
"<"                     TOKEN(TCLT);
"<="                    TOKEN(TCLE);
">"                     TOKEN(TCGT);
">="                    TOKEN(TCGE);
"("                     TOKEN(TLPAREN);
")"                     TOKEN(TRPAREN);
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
