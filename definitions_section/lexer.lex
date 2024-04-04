
%top {
	/* This code goes to the top of lex.yy.c*/
	#include <stdio.h>
}

%{
int digit_count = 0;
int char_count = 0;
%}

%%
fuck	printf("f**k"); char_count+=4;
[0-9]	digit_count++; char_count++;
.	char_count++;
%%

int yywrap () {}
int main () {
	yylex();
	printf("digit_count: %d\n", digit_count);
	printf("char_count: %d\n", char_count);
	return 0;
}

