%option noyywrap
%option yylineno
%option nounput
%option noinput

%{
  #include "parser.h"   /* bison이 만든 토큰/yyparse 선언 (토큰 enum, yylval 등) */
  #include "ast.h"
  #include <stdio.h>

  /* yylineno는 %option yylineno로 flex가 관리 */
%}

/* 블록 주석 처리용 시작 조건 */
%s COMMENT

%%
[ \t\r\n]+                        { /* skip whitespace */ }

"/*"                              { BEGIN(COMMENT); }
<COMMENT>[^*]+                    { /* skip */ }
<COMMENT>"*"+[^*/]                { /* skip */ }
<COMMENT>"*"+"/"                  { BEGIN(INITIAL); }
<COMMENT><<EOF>>                  { BEGIN(INITIAL); /* unterminated comment -> 무시 또는 에러 */ }

"//".*                            { /* skip */ }

"int"                             { return INT; }
"float"                           { return FLOAT; }
"char"                            { return CHAR; }
"void"                            { return VOID; }
"if"                              { return IF; }
"else"                            { return ELSE; }
"while"                           { return WHILE; }
"for"                             { return FOR; }
"return"                          { return RETURN; }

"=="                              { return EQ; }
"!="                              { return NE; }
"<="                              { return LE; }
">="                              { return GE; }
"&&"                              { return AND; }
"||"                              { return OR; }
"="                               { return '='; }
"<"                               { return '<'; }
">"                               { return '>'; }
"+"                               { return '+'; }
"-"                               { return '-'; }
"*"                               { return '*'; }
"/"                               { return '/'; }
"%"                               { return '%'; }
"!"                               { return '!'; }
"~"                               { return '~'; }
";"                               { return ';'; }
","                               { return ','; }
"("                               { return '('; }
")"                               { return ')'; }
"{"                               { return '{'; }
"}"                               { return '}'; }

[A-Za-z_][A-Za-z0-9_]*            { yylval = node(NK_VAR,    yylineno, yytext, 0); return IDENT; }

[0-9]+                            { yylval = node(NK_INT,    yylineno, yytext, 0); return INT_CONST; }

([0-9]+"."[0-9]*|"."[0-9]+|[0-9]+"."[0-9]*)([eE][+-]?[0-9]+)? {
                                    yylval = node(NK_FLOAT,  yylineno, yytext, 0); return FLOAT_CONST;
                                  }

\'([^\\\n]|\\.)\'                 { yylval = node(NK_CHAR,   yylineno, yytext, 0); return CHAR_CONST; }

\"([^\\\n]|\\.)*\"                { yylval = node(NK_STRING, yylineno, yytext, 0); return STRING_LITERAL; }

.                                 { /* unknown char: ignore or report */ }

%%

/* 필요 시 사용자 정의 헬퍼 추가 가능 */
