%option noyywrap

%{
#include <stdlib.h>      /* atof */
#include "parser.tab.h"  /* yylval, tokens */
%}

%%
[0-9]+(\.[0-9]+)?   { yylval.num = atof(yytext); return NUMBER; }
[ \t\n]+             ;
"+"                 return '+';
"-"                 return '-';
"*"                 return '*';
"/"                 return '/';
";"                 return ';';
.                   return yytext[0];
%%
