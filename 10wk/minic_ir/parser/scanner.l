%{
#include "ast.h"
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
"int"                        { return INT_KW; }
"print"                      { return PRINT_KW; }
[0-9]+                       { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*       { yylval.sval = strdup(yytext); return IDENT; }
[ \t\r\n]+                   { /* skip whitespace */ }
.                            { return yytext[0]; }
%%

int yywrap(void) { return 1; }
