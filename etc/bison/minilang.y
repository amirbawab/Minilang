%{
// ML Include
#include <minilang/minilang.h>
#include <iostream>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
%}

%code requires {
#include <memory>
#include <minilang/mexpression.h>
#include <minilang/mvalue.h>
}

%union {
	mini::MValue<int>*      intVal;
	mini::MValue<float>*    floatVal;
	mini::MValue<char*>*    stringVal;
}

// Define tokens
%token
    T_TYPE_FLOAT    "float type"
    T_TYPE_INT      "int type"
    T_TYPE_STRING   "string type"
    T_TYPE_BOOLEAN  "boolean type"
    T_VAR           "var"
    T_WHILE         "while"
    T_IF            "if"
    T_ELSE          "else"
    T_PRINT         "print"
    T_READ          "read"
    T_TRUE          "TRUE"
    T_FALSE         "FALSE"
    T_EQUAL         "="
    T_COLON         ":"
    T_SEMICOLON     ";"
    T_LCURL         "{"
    T_RCURL         "}"
    T_LPAR          "("
    T_RPAR          ")"
    T_PLUS          "+"
    T_MINUS         "-"
    T_MULT          "*"
    T_DIV           "/"
    T_IS_EQUAL      "=="
    T_IS_NOT_EQUAL  "!="
    T_AND           "&&"
    T_OR            "||"
    T_NOT           "!"
    <intVal>     T_INTEGER      "integer number"
    <floatVal>   T_FLOAT        "float number"
    <stringVal>  T_STRING       "string"
    <identVal>   T_IDENTIFIER   "identifier"
    ;

// Non-terminal type
%type <MExpression*> EXPR

// Configure bison
%locations
%error-verbose

// Configure grammar
%start S
%left T_OR
%left T_AND
%left T_IS_EQUAL T_IS_NOT_EQUAL
%left T_PLUS T_MINUS
%left T_MULT T_DIV
%left P_NEG P_NOT

%%
S
    : VAR_DECS STATEMENTS 
    ;

VAR_DECS
    : VAR_DECS VAR_DEC
    | %empty
    ;

VAR_DEC
    : T_VAR T_IDENTIFIER T_COLON TYPE T_EQUAL EXPR T_SEMICOLON
    ;

STATEMENTS
    : STATEMENTS STATEMENT
    | %empty
    ;

STATEMENT
    : T_WHILE EXPR T_LCURL STATEMENTS T_RCURL
    | T_IF EXPR T_LCURL STATEMENTS T_RCURL ELSE_OPT
    | T_IDENTIFIER T_EQUAL EXPR T_SEMICOLON
    | T_READ T_IDENTIFIER T_SEMICOLON
    | T_PRINT EXPR T_SEMICOLON
    ;

ELSE_OPT
    : T_ELSE T_LCURL STATEMENTS T_RCURL
    | %empty
    ;

EXPR[root]
    : EXPR[left] T_PLUS EXPR[right]
    | EXPR[left] T_MINUS EXPR[right]
    | EXPR[left] T_MULT EXPR[right]
    | EXPR[left] T_DIV EXPR[right]
    | EXPR[left] T_IS_EQUAL EXPR[right]
    | EXPR[left] T_IS_NOT_EQUAL EXPR[right]
    | EXPR[left] T_AND EXPR[right]
    | EXPR[left] T_OR EXPR[right]
    | T_LPAR EXPR[left] T_RPAR
    | T_MINUS EXPR[left] %prec P_NEG
    | T_NOT EXPR[left] %prec P_NOT
    | T_INTEGER
    | T_FLOAT
    | T_STRING
    | T_IDENTIFIER
    | T_TRUE
    | T_FALSE
    ;

TYPE
    : T_TYPE_INT
    | T_TYPE_FLOAT
    | T_TYPE_STRING
    | T_TYPE_BOOLEAN
    ;
%%
