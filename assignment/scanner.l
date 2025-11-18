%option noyywrap

%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>

/* 현재 수식 문자열 누적용 */
char current_expr[256] = "";
%}

ID      [A-Za-z_][A-Za-z0-9_]*
NUM     [0-9]+(\.[0-9]+)? 
WS      [ \t\r]+

%%

"show"      { strcpy(current_expr, ""); return T_SHOW; } 
{ID}        { strcat(current_expr, yytext); yylval.sval = strdup(yytext); return T_ID; }

{NUM}       { strcat(current_expr, yytext); yylval.dval = atof(yytext); return T_NUMBER; }

";"         { return T_END; } 
\n        { return T_END; } 

"+"         { strcat(current_expr, "+"); return '+'; }
"-"         { strcat(current_expr, "-"); return '-'; }
"*"         { strcat(current_expr, "*"); return '*'; }
"/"         { strcat(current_expr, "/"); return '/'; } 
"%"         { strcat(current_expr, "%"); return '%'; }
"="         { strcat(current_expr, "="); return '='; }
"("         { strcat(current_expr, "("); return '('; }
")"         { strcat(current_expr, ")"); return ')'; }

"//"[^\n]*  { /* skip */ }

{WS}        { /* skip */ }

.           { /* fprintf(stderr, "unknown char: %s\n", yytext); */ }

%%