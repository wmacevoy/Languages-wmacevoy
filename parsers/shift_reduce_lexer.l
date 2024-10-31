%{
#include "shift_reduce_parser.h"
#include <cstdlib>

// Forward declaration of yyerror
void yyerror(const char *s);
%}

%option noyywrap
%option outfile="shift_reduce_lexer.cpp"
%option header-file="shift_reduce_lexer.h"

DIGIT      [0-9]
NUMBER     {DIGIT}+(\.{DIGIT}+)?

%%

[ \t\n]+              ; // Skip whitespace

"+"                   { return PLUS; }
"-"                   { return MINUS; }
"*"                   { return MULTIPLY; }
"/"                   { return DIVIDE; }
"("                   { return LPAREN; }
")"                   { return RPAREN; }

{NUMBER}              {
                        yylval.dval = atof(yytext);
                        return NUMBER;
                     }

.                     { yyerror("Unknown character"); }

%%
