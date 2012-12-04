%{
#include "shade.tab.h"
#include "node.h"
#include "type.h"
#define TOKEN(t) yylval.token = t; return t
//[0-9]+\.[0-9]*          yylval.node_t = const_double(atof(yytext)); return TDOUBLE;
//"string"                yylval.type_t = type_string(); return TSTRING_T;
%}

%option noyywrap

%%

[ \t\n]                 ;
"parsedbg"              printf("parsedbg");
"if"                    TOKEN(TIF);
"while"                 TOKEN(TWHILE);
"declare"               TOKEN(TDECLARE);
"int"                   yylval.type_t = type_int(); return TINTEGER_T;
"char"                  yylval.type_t = type_char(); return TCHAR_T;
[a-zA-Z_][a-zA-Z0-9_]*  yylval.node_t = identifier(yytext); return TIDENTIFIER;
L?\"(\\.|[^\\"])*\"     yylval.node_t = const_string(yytext); return TSTRING;
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
