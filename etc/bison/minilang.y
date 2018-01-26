%{
// ML Include
#include <minilang/minilang.h>
#include <iostream>

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

%token _EOF_ 0

// Set grammar start non-terminal
%start S
%left T_OR
%left T_AND
%left T_IS_EQUAL T_IS_NOT_EQUAL
%left T_PLUS T_MINUS
%left T_MULT T_DIV
%left P_NEG

%%
S
    : S VAR_DEC
    | S STATEMENT
    | %empty
    | S S_ERRORS
    ;

S_ERRORS
    : S error TOKEN_START { syError("Invalid syntax at line "); }
    | S error TOKEN_END { syError("Invalid syntax at line "); }
    | S error _EOF_ { syErrorEOF(); }
    ;

VAR_DEC
    : T_VAR T_IDENTIFIER T_COLON TYPE T_EQUAL EXPR T_SEMICOLON
    | VAR_DEC_ERRORS
    ;

VAR_DEC_ERRORS
    : T_VAR error TOKEN_START { syError("Missing semicolon for variable declaration at line "); }
    | T_VAR error TOKEN_END {syError("Invalid variable declaration at line ");}
    | T_VAR error _EOF_ { syErrorEOF(); }
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
    | T_PRINT T_IDENTIFIER T_SEMICOLON
    | STATEMENT_ERRORS
    ;

STATEMENT_ERRORS
    : T_WHILE error TOKEN_START { syError("Missing closing curly bracket for while statement at line "); }
    | T_WHILE error TOKEN_END { syError("Invalid while statement declaration at line "); }
    | T_WHILE error _EOF_ { syErrorEOF(); }
    | T_IF error TOKEN_START { syError("Missing closing curly bracket for if statement at line "); }
    | T_IF error TOKEN_END { syError("Invalid if statement declaration at line "); }
    | T_IF error _EOF_ { syErrorEOF(); }
    | T_IDENTIFIER error TOKEN_START { syError("Missing semicolon for variable assignment at line "); }
    | T_IDENTIFIER error TOKEN_END { syError("Invalid variable assignment at line "); }
    | T_IDENTIFIER error _EOF_ { syErrorEOF(); }
    | T_READ error TOKEN_START { syError("Missing semicolon for read statement at line "); }
    | T_READ error TOKEN_END { syError("Invalid read statement at line "); }
    | T_READ error _EOF_ { syErrorEOF(); }
    | T_PRINT error TOKEN_START { syError("Missing semicolon for print statement at line "); }
    | T_PRINT error TOKEN_END { syError("Invalid print statement at line "); }
    | T_PRINT error _EOF_ { syErrorEOF(); }
    | error TOKEN_START { syError("Undetermined statement at line "); }
    | error TOKEN_END { syError("Undetermined statement at line "); }
    | error _EOF_ { syErrorEOF(); }
    ;

ELSE_OPT
    : T_ELSE T_LCURL STATEMENTS T_RCURL
    | %empty
    | ELSE_OPT_ERRORS
    ;

ELSE_OPT_ERRORS
    : T_ELSE error TOKEN_START { syError("Missing closing curly bracket for else statement at line "); }
    | T_ELSE error TOKEN_END { syError("Invalid else statement declaration at line "); }
    | T_ELSE error _EOF_ { syErrorEOF(); }
    ;

EXPR
    : EXPR T_PLUS EXPR
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

TYPE
    : T_TYPE_INT
    | T_TYPE_FLOAT
    | T_TYPE_STRING
    ;

TOKEN_START
    : T_WHILE
    | T_VAR
    | T_IF
    | T_READ
    | T_PRINT
    ;

TOKEN_END
    : T_SEMICOLON
    | T_RCURL
    ;
%%
