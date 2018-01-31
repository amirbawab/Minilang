%{
// MiniLang Compiler
// Author: Amir El Bawab
// ML = MiniLang

// ML Include
#include <minilang/minilang.h>
#include <minilang/mvalue.h>
#include <bison/minilang_bison.h>
#include <iostream>

// ML defines
#define YY_DECL extern "C" int yylex()
extern "C" bool m_tokenFlag;
%}

%option yylineno

%%
var     {if(m_tokenFlag) std::cout << "T_VAR" << std::endl; return T_VAR;}
float   {if(m_tokenFlag) std::cout << "T_TYPE_FLOAT" << std::endl; return T_TYPE_FLOAT;}
int     {if(m_tokenFlag) std::cout << "T_TYPE_INT" << std::endl; return T_TYPE_INT;}
string  {if(m_tokenFlag) std::cout << "T_TYPE_STRING" << std::endl; return T_TYPE_STRING;}
boolean {if(m_tokenFlag) std::cout << "T_BOOLEAN" << std::endl; return T_TYPE_BOOLEAN;}
while   {if(m_tokenFlag) std::cout << "T_WHILE" << std::endl; return T_WHILE;}
if      {if(m_tokenFlag) std::cout << "T_IF" << std::endl; return T_IF;}
else    {if(m_tokenFlag) std::cout << "T_ELSE" << std::endl; return T_ELSE;}
print   {if(m_tokenFlag) std::cout << "T_PRINT" << std::endl; return T_PRINT;}
read    {if(m_tokenFlag) std::cout << "T_READ" << std::endl; return T_READ;}
":"     {if(m_tokenFlag) std::cout << "T_COLON" << std::endl; return T_COLON;}
";"     {if(m_tokenFlag) std::cout << "T_SEMICOLON" << std::endl; return T_SEMICOLON;}
"="     {if(m_tokenFlag) std::cout << "T_EQUAL" << std::endl; return T_EQUAL;}
"=="    {if(m_tokenFlag) std::cout << "T_IS_EQUAL" << std::endl; return T_IS_EQUAL;}
"!="    {if(m_tokenFlag) std::cout << "T_IS_NOT_EQUAL" << std::endl; return T_IS_NOT_EQUAL;}
"&&"    {if(m_tokenFlag) std::cout << "T_AND" << std::endl; return T_AND;}
"||"    {if(m_tokenFlag) std::cout << "T_OR" << std::endl; return T_OR;}
"{"     {if(m_tokenFlag) std::cout << "T_LCURL" << std::endl; return T_LCURL;}
"}"     {if(m_tokenFlag) std::cout << "T_RCURL" << std::endl; return T_RCURL;}
"+"     {if(m_tokenFlag) std::cout << "T_PLUS" << std::endl; return T_PLUS;}
"-"     {if(m_tokenFlag) std::cout << "T_MINUS" << std::endl; return T_MINUS;}
"*"     {if(m_tokenFlag) std::cout << "T_MULT" << std::endl; return T_MULT;}
"/"     {if(m_tokenFlag) std::cout << "T_DIV" << std::endl; return T_DIV;}
"("     {if(m_tokenFlag) std::cout << "T_LPAR" << std::endl; return T_LPAR;}
")"     {if(m_tokenFlag) std::cout << "T_RPAR" << std::endl; return T_RPAR;}
"!"     {if(m_tokenFlag) std::cout << "T_NOT" << std::endl; return T_NOT;}

TRUE {
    if(m_tokenFlag) std::cout << "T_TRUE" << std::endl;
    yylval.m_boolVal = new mini::MValue<bool>(true);
    return T_TRUE;
}

FALSE {
    if(m_tokenFlag) std::cout << "T_FALSE" << std::endl;
    yylval.m_boolVal = new mini::MValue<bool>(false);
    return T_FALSE;
}

[ \t\r\n] {
    // White-space
}

[a-zA-Z_][a-zA-Z0-9_]* {
    if(m_tokenFlag) std::cout << "T_IDENTIFIER(" << yytext << ")" << std::endl;
    return T_IDENTIFIER;
}

(0|[1-9][0-9]*)\.[0-9]+ {
    if(m_tokenFlag) std::cout << "T_FLOAT(" << yytext << ")" << std::endl;
    yylval.m_floatVal = new mini::MValue<float>(atof(yytext));
    return T_FLOAT;
}

0|([1-9][0-9]*) {
    if(m_tokenFlag) std::cout << "T_INTEGER(" << yytext << ")" << std::endl;
    yylval.m_intVal = new mini::MValue<int>(atoi(yytext));
    return T_INTEGER;
}

\"((\\[abfnrtv\"\\])|[ a-zA-Z0-9\~\@\#\$\%\^\&\*\-\+\/\`\<\>\=\_\|\'\.\,\;\:\!\?\{\}\[\]\(\)])*\"  {
    if(m_tokenFlag) std::cout << "T_STRING(" << yytext << ")" << std::endl;
    yylval.m_stringVal = new mini::MValue<char*>(yytext);
    return T_STRING;
}

"//".* {
    // Inline comment
}

. {
    // EVERYTHING ELSE
    std::cerr << "Error: Invalid token " << yytext << " at line " << yylineno << std::endl;
    exit(CODE_COMPILER_ERROR);
}
%%

