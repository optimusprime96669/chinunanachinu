%{
#include <stdio.h>
%}

%%
[0-9]+      { printf("INTEGER: %s\n", yytext); }
[-+]        { printf("OPERATOR: %s\n", yytext); }
[*\/]       { printf("OPERATOR: %s\n", yytext); }
[ \t\n]     ; /* Ignore whitespace and newlines */
.           { printf("INVALID: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}
