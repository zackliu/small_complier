%{
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "small.tab.h"

int line = 1;
void yyerror(char *);
int yywrap(void);
%}

%%
"//".*
[ \t]
[\n] {line++;}

"+" |
"-" |
"*" |
"/" |
"%" |
";" |
"," |
"(" |
")" {return yytext[0];}

":=" {return BC;}
">=" {return GE;}
"<=" {return LE;}
">" {return GT;}
"<" {return LT;}
"==" {return EQ;}
"!=" {return NE;}

"begin" {return BEG;}
"end" {return END;}
"if" {return IF;}
"else" {return ELSE;}
"then" {return THEN;}
"while" {return WHILE;}
"do" {return DO;}
"repeat" {return REPEAT;}
"until" {return UNTIL;}
"read" {return READ;}
"write" {return WRITE;}
"function" {return FUNCTION;}
"odd" {return ODD;}
"xor" {return XOR;}
"var" {return VAR;}
"const" {return CONST;}
"call" {return CALL;}
"return" {return RETURN;}

[A-Za-z]([A-Za-z]|[0-9])* {strcpy(yylval.ident,yytext); return IDENT;}
[0-9]+ {yylval.number=atoi(yytext); return NUMBER;}

. {printf("%s  ",yytext); yyerror("Unknown character!");}
%%
void redirectInput(FILE *input)
{
	yyin=input;
}

int yywrap(void)
{
	return 1;
}

