%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}
%option noyywrap

%%

[0-9]+(\.[0-9]+)?      { yylval.num = strtod(yytext, NULL); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return IDENT; }

[ \t]+                 ;     /* 공백 무시 */
\n                     { return '\n'; }

"=="                   { return '='; }  /* 방어: 실수로 == 써도 =로 처리 */
"="                    { return '='; }
"("                    { return '('; }
")"                    { return ')'; }
"+"|"-"|"*"|"/"        { return yytext[0]; }

.                      { /* 알 수 없는 문자 */
                         fprintf(stderr, "unknown char: '%s'\n", yytext);
                       }

%%

