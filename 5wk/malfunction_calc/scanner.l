/* scanner.l */
%option noyywrap

%{
#include "parser.tab.h"   /* bison이 생성하는 헤더 */
%}

DIGIT   [0-9]+
WS      [ \t\r\n]+

%%

{DIGIT}     { yylval.ival = atoi(yytext); return T_NUMBER; }
"+"         { return '+'; }
"*"         { return '*'; }
"("         { return '('; }
")"         { return ')'; }
{WS}        { /* skip */ }

.           { /* 알 수 없는 문자 무시(혹은 에러 출력 가능) */ }

%%