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
#include <minilang/mstatement_factory.h>
#include <minilang/mscope.h>
#include <minilang/mglobal.h>
#include <minilang/mvariable.h>
#include <minilang/mtype.h>
#include <vector>
}

%union {
	mini::MStatement*                m_statement;
	mini::MExpression*               m_expression;
	std::vector<mini::MStatement*>*  m_statements;
	std::vector<mini::MVariable*>*   m_variables;
	mini::MVariable*                 m_variable;
	mini::TYPE                       m_type;
}

// Define tokens
%token
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
    <m_type>        T_TYPE_FLOAT   "float type"
    <m_type>        T_TYPE_INT     "int type"
    <m_type>        T_TYPE_STRING  "string type"
    <m_type>        T_TYPE_BOOLEAN "boolean type"
    ;

// Non-terminal type
%type <m_expression>    EXPR
%type <m_statements>    STATEMENTS
%type <m_statement>     STATEMENT
%type <m_statement>     ELSE_OPT
%type <m_variable>      VAR_DEC
%type <m_variables>     VAR_DECS
%type <m_type>          TYPE

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
    : VAR_DECS[variables] STATEMENTS[statements] {
        mini::MGlobal::getInstance()->setVariables($variables);
        mini::MGlobal::getInstance()->setStatements($statements);
    }
    ;

VAR_DECS[root]
    : VAR_DECS VAR_DEC[variable] {
        if(!$root) {
            $root = new std::vector<mini::MVariable*>();
        }
        $root->push_back($variable);
    }
    | %empty {
        $root = nullptr;
    }
    ;

VAR_DEC[root]
    : T_VAR T_IDENTIFIER[id] T_COLON TYPE[type] T_EQUAL EXPR[expr] T_SEMICOLON {
        mini::MIdentifier* value = static_cast<mini::MIdentifier*>($id);
        value->setExpression($expr);
        mini::MVariable* variable = new mini::MVariable(value);
        variable->setType($type);
        $root = variable;
    }
    ;

STATEMENTS[root]
    : STATEMENTS STATEMENT[statement] {
        if(!$root) {
            $root = new std::vector<mini::MStatement*>();
        }
        $root->push_back($statement);
    }
    | %empty {
        $root = nullptr;
    }
    ;

STATEMENT[root]
    : T_WHILE EXPR[expr] T_LCURL STATEMENTS[statements] T_RCURL {
        mini::MWhile* whileStmt = mini::MStatementFactory::createWhile($expr);
        whileStmt->setStatements($statements);
        $root = whileStmt;
    }
    | T_IF EXPR[expr] T_LCURL STATEMENTS[statements] T_RCURL ELSE_OPT[else] {
        mini::MIf* ifStmt = mini::MStatementFactory::createIf($expr);
        ifStmt->setElse($else);
        ifStmt->setStatements($statements);
        $root = ifStmt;
    }
    | T_IDENTIFIER[id] T_EQUAL EXPR[expr] T_SEMICOLON {
        mini::MIdentifier* value = static_cast<mini::MIdentifier*>($id);
        value->setExpression($expr);
        $root = value;
    }
    | T_READ T_IDENTIFIER[id] T_SEMICOLON {
        mini::MIdentifier* value = static_cast<mini::MIdentifier*>($id);
        $root = mini::MStatementFactory::createRead(value);
    }
    | T_PRINT EXPR[expr] T_SEMICOLON {
        $root = mini::MStatementFactory::createPrint($expr);
    }
    ;

ELSE_OPT[root]
    : T_ELSE T_LCURL STATEMENTS[statements] T_RCURL {
        mini::MElse* elseStmt = mini::MStatementFactory::createElse();
        elseStmt->setStatements($statements);
        $root = elseStmt;
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
