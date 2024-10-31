%{
#include <iostream>
#include <cstdlib>
#include "shift_reduce_ast.h"    // Include the correct AST header

void yyerror(const char *s);
extern int yylex();

// Root of the AST
ASTNode* root;
%}

%code requires {
    // Include the AST header before the union declaration
    #include "shift_reduce_ast.h"
}

%code provides {
    extern ASTNode* root;
}

%union {
    double dval;
    ASTNode* node;
}

%token <dval> NUMBER
%token PLUS MINUS MULTIPLY DIVIDE LPAREN RPAREN

%type <node> expr

%left PLUS MINUS
%left MULTIPLY DIVIDE
%right UMINUS

%%

input:
    expr {
        root = $1;
    }
    ;

expr:
    expr PLUS expr        { $$ = new BinaryOpNode($1, TOKEN_PLUS, $3); }
    | expr MINUS expr     { $$ = new BinaryOpNode($1, TOKEN_MINUS, $3); }
    | expr MULTIPLY expr  { $$ = new BinaryOpNode($1, TOKEN_MULTIPLY, $3); }
    | expr DIVIDE expr    { $$ = new BinaryOpNode($1, TOKEN_DIVIDE, $3); }
    | MINUS expr %prec UMINUS { $$ = new UnaryOpNode(TOKEN_MINUS, $2); }
    | LPAREN expr RPAREN  { $$ = $2; }
    | NUMBER              { $$ = new NumberNode($1); }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Syntax error: " << s << std::endl;
}
