%option noyywrap

%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

/* 패턴 */
ID      [A-Za-z_][A-Za-z0-9_]*
NUM     [0-9]+
WS      [ \t\r]+

%%

{ID}        { yylval.sval = strdup(yytext); return T_ID; }
{NUM}       { yylval.ival = atoi(yytext);   return T_NUMBER; }

"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"="         { return '='; }
"("         { return '('; }
")"         { return ')'; }

\n          { return '\n'; }
{WS}        { /* skip */ }

.           { /* 알 수 없는 문자: 무시하거나 에러 처리 가능 */
              /* fprintf(stderr, "unknown char: %s\n", yytext); */
            }

%%
