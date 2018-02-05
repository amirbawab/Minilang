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
#include <minilang/mvalue.h>
#include <minilang/mexpression_factory.h>
#include <minilang/mstatement.h>
}

%union {
	mini::MStatement*       m_statement;
	mini::MExpression*      m_expression;
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
    <m_expression>  T_INTEGER      "integer number"
    <m_expression>  T_FLOAT        "float number"
    <m_expression>  T_STRING       "string"
    <m_expression>  T_IDENTIFIER   "identifier"
    <m_expression>  T_TRUE         "TRUE"
    <m_expression>  T_FALSE        "FALSE"
    ;

// Non-terminal type
%type <m_expression> EXPR
%type <m_statement> STATEMENT
%type <m_statement> ELSE_OPT

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
S[root]
    : VAR_DECS STATEMENTS 
    ;

VAR_DECS
    : VAR_DECS VAR_DEC
    | %empty
    ;

VAR_DEC
    : T_VAR T_IDENTIFIER[id] T_COLON TYPE T_EQUAL EXPR[expr] T_SEMICOLON {
        mini::MValue<mini::MIdentifier*>* value = static_cast<mini::MValue<mini::MIdentifier*>*>($id);
        //value->setExpression($expr);
    }
    ;

STATEMENTS
    : STATEMENTS STATEMENT
    | %empty
    ;

STATEMENT[root]
    : T_WHILE EXPR T_LCURL STATEMENTS T_RCURL {
        std::cout << "while statement" << std::endl;
    }
    | T_IF EXPR T_LCURL STATEMENTS T_RCURL ELSE_OPT {
        std::cout << "if statement" << std::endl;
    }
    | T_IDENTIFIER T_EQUAL EXPR T_SEMICOLON {
        std::cout << "assign statement" << std::endl;
    }
    | T_READ T_IDENTIFIER T_SEMICOLON {
        std::cout << "read statement" << std::endl;
    }
    | T_PRINT EXPR T_SEMICOLON {
        std::cout << "print statement" << std::endl;
    }
    ;

ELSE_OPT[root]
    : T_ELSE T_LCURL STATEMENTS T_RCURL {
        std::cout << "else statement" << std::endl;
    }
    | %empty {
        $root = nullptr;
    }
    ;

EXPR[root]
    : EXPR[left] T_PLUS EXPR[right] {
        $root = mini::MExpressionFactory::createBPlus($left, $right);
    }
    | EXPR[left] T_MINUS EXPR[right] {
        $root = mini::MExpressionFactory::createBMinus($left, $right);
    }
    | EXPR[left] T_MULT EXPR[right] {
        $root = mini::MExpressionFactory::createBTimes($left, $right);
    }
    | EXPR[left] T_DIV EXPR[right] {
        $root = mini::MExpressionFactory::createBDivide($left, $right);
    }
    | EXPR[left] T_IS_EQUAL EXPR[right] {
        $root = mini::MExpressionFactory::createBIsEqual($left, $right);
    }
    | EXPR[left] T_IS_NOT_EQUAL EXPR[right] {
        $root = mini::MExpressionFactory::createBIsNotEqual($left, $right);
    }
    | EXPR[left] T_AND EXPR[right] {
        $root = mini::MExpressionFactory::createBAND($left, $right);
    }
    | EXPR[left] T_OR EXPR[right] {
        $root = mini::MExpressionFactory::createBOR($left, $right);
    }
    | T_MINUS EXPR[operand] %prec P_NEG {
        $root = mini::MExpressionFactory::createUMinus($operand);
    }
    | T_NOT EXPR[operand] %prec P_NOT {
        $root = mini::MExpressionFactory::createUNot($operand);
    }
    | T_LPAR EXPR[operand] T_RPAR {
        $root = $operand;
    }
    | T_INTEGER
    | T_FLOAT
    | T_STRING {
        mini::MValue<char*>* val = static_cast<mini::MValue<char*>*>($1);
    }
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
