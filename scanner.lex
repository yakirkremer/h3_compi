%{

/* Declarations section */
    #include "output.hpp"
    using namespace output;
    #include "parser.tab.hpp"
%}

%option noyywrap
%option yylineno

whitespace [ \t\n\r]
printable [ -~]
escape [\n]

%%
int                     return INT;
byte                    return BYTE;
b                       return B;
bool                    return BOOL;
and                     return AND;
or                      return OR;
not                     return NOT;
true                    return TRUE;
false                   return FALSE;
return                  return RETURN;
if                      return IF;
else                    return ELSE;
while                   return WHILE;
break                   return BREAK;
continue                return CONTINUE;
;                       return SC;
\(                      return LPAREN;
\)                      return RPAREN;
\{                      return LBRACE;
\}                      return RBRACE;
=                       return ASSIGN;
"<="|">="|<|>           return RELOP;
==|!=                   return EQUALITY;
[-+]                    return ADDITIVE;
[*/]                    return MULTIPLICATIVE;
[a-zA-Z][a-zA-Z0-9]*    return ID;
[1-9][0-9]*|0           return NUM;
\/\/[^\r\n]*            ;
\"([ !#-\[\]-~]|\\[\\\"nrt0]|\\x[0-7][0-9A-Fa-f])+\"    return STRING;
{whitespace}            ;
.                       {errorLex(yylineno); exit(1);}
%%