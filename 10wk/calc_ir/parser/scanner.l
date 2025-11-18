%{
#include "ast.h"        /* AST 타입을 먼저 알려주고 */
#include "parser.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval.ival = atoi(yytext); return NUMBER; }
[ \t\r]+    { /* skip whitespace */ }
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap(void) { return 1; }
