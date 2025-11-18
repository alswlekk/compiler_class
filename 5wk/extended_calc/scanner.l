%option noyywrap

%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

ID      [A-Za-z_][A-Za-z0-9_]*
NUM     [0-9]+
WS      [ \t\r]+

%%

"print"     { return T_PRINT; }
{ID}        { yylval.sval = strdup(yytext); return T_ID; }

{NUM}       { yylval.ival = atoi(yytext);   return T_NUMBER; }

"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"%"         { return '%'; }
"="         { return '='; }
"("         { return '('; }
")"         { return ')'; }

"//"[^\n]*  { /* skip */ }

{WS}        { /* skip */ }
\n          { return '\n'; }

.           { /* fprintf(stderr, "unknown char: %s\n", yytext); */ }

%%
