%{
// ML Include
#include <minilang/minilang.h>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
%}

%union {
	int     intVal;
	float   floatVal;
	char    *stringVal;
	char    *identVal;
}

// Define tokens
%token
    T_TYPE_FLOAT
    T_TYPE_INT
    T_TYPE_STRING
    T_VAR
    T_WHILE
    T_IF
    T_ELSE
    T_PRINT
    T_READ
    T_BOOLEAN
    T_TRUE
    T_FALSE
    T_EQUAL
    T_COLON
    T_SEMICOLON
    T_LCURL
    T_RCURL
    T_LPAR
    T_RPAR
    T_PLUS
    T_MINUS
    T_MULT
    T_DIV
    T_IS_EQUAL
    T_IS_NOT_EQUAL
    T_AND
    T_OR
    <intVal>     T_INTEGER
    <floatVal>   T_FLOAT
    <stringVal>  T_STRING
    <identVal>   T_IDENTIFIER
    ;

// Set grammar start non-terminal
%start S
%left T_OR
%left T_AND
%left T_IS_EQUAL T_IS_NOT_EQUAL
%left T_PLUS T_MINUS
%left T_MULT T_DIV
%left P_NEG

%%
S :
    S VAR_DEC
    | S STATEMENTS
    | %empty
    ;

VAR_DEC :
    T_VAR T_IDENTIFIER T_COLON TYPE T_EQUAL EXPR T_SEMICOLON;

STATEMENTS :
    STATEMENTS STATEMENT
    | %empty

STATEMENT :
    T_WHILE EXPR T_LCURL STATEMENTS T_RCURL
    | T_IF EXPR T_LCURL STATEMENTS T_RCURL ELSE_OPT
    | T_IDENTIFIER T_EQUAL EXPR T_SEMICOLON
    | T_READ T_IDENTIFIER T_SEMICOLON
    | T_PRINT T_IDENTIFIER T_SEMICOLON
    ;

ELSE_OPT:
    T_ELSE T_LCURL STATEMENTS T_RCURL
    | %empty
    ;

EXPR:
    EXPR T_PLUS EXPR
    | EXPR T_MINUS EXPR
    | EXPR T_MULT EXPR
    | EXPR T_DIV EXPR
    | EXPR T_IS_EQUAL EXPR
    | EXPR T_IS_NOT_EQUAL EXPR
    | EXPR T_AND EXPR
    | EXPR T_OR EXPR
    | T_MINUS EXPR %prec P_NEG
    | T_INTEGER
    | T_FLOAT
    | T_STRING
    | T_IDENTIFIER
    | T_TRUE
    | T_FALSE
    ;

TYPE:
    T_TYPE_INT
    | T_TYPE_FLOAT
    | T_TYPE_STRING
    ;
%%
