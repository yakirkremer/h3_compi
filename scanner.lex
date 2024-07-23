%{

/* Declarations section */
    #include "types.h"
    #include "hw3_output.hpp"
    using namespace output;
    #include "parser.tab.hpp"

%}

%option noyywrap
%option yylineno

whitespace [ \t\n\r]
printable [ -~]
escape [\n]

%%
int                     yylval=new Node("INT",yylineno);    return INT;
byte                    yylval=new Node("BYTE",yylineno);    return BYTE;
b                       yylval=new Node(yytext,yylineno);    return B;
bool                    yylval=new Node("BOOL",yylineno);    return BOOL;
and                     yylval=new Node(yytext,yylineno);  return AND;
or                      yylval=new Node(yytext,yylineno);  return OR;
not                     yylval=new Node(yytext,yylineno);  return NOT;
true                    yylval=new Node(yytext,yylineno);  return TRUE;
false                  yylval=new Node(yytext,yylineno);   return FALSE;
return                  yylval=new Node(yytext,yylineno);  return RETURN;
if                      yylval=new Node(yytext,yylineno);  return IF;
else                    yylval=new Node(yytext,yylineno);  return ELSE;
while                  yylval=new Node(yytext,yylineno);   return WHILE;
break                  yylval=new Node(yytext,yylineno);   return BREAK;
continue               yylval=new Node(yytext,yylineno);   return CONTINUE;
;                       yylval=new Node(yytext,yylineno);  return SC;
\(                      yylval=new Node(yytext,yylineno);  return LPAREN;
\)                     yylval=new Node(yytext,yylineno);   return RPAREN;
\{                      yylval=new Node(yytext,yylineno);  return LBRACE;
\}                     yylval=new Node(yytext,yylineno);   return RBRACE;
=                      yylval=new Node(yytext,yylineno);   return ASSIGN;
"<="|">="|<|>          yylval=new Node(yytext,yylineno);  return RELOP;
==|!=                  yylval=new Node(yytext,yylineno);   return EQUALITY;
[-+]                   yylval=new Node(yytext,yylineno);   return ADDITIVE;
[*/]                   yylval=new Node(yytext,yylineno);   return MULTIPLICATIVE;
[a-zA-Z][a-zA-Z0-9]*     yylval=new Node(yytext,yylineno); return ID;
[1-9][0-9]*|0          yylval=new Node(yytext,yylineno);   return NUM;
\/\/[^\r\n]*            ;
\"([ !#-\[\]-~]|\\[\\\"nrt0]|\\x[0-7][0-9A-Fa-f])+\"  yylval=new Node(yytext,yylineno);    return STRING;
{whitespace}            ;
.                       {errorLex(yylineno); exit(1);}
%%