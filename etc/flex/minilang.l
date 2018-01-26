%{
// MiniLang Compiler
// Author: Amir El Bawab
// ML = MiniLang

// ML Include
#include <minilang/minilang.h>
#include <bison/minilang_bison.h>
#include <iostream>

// ML defines
#define YY_DECL extern "C" int yylex()
extern "C" bool m_tokenFlag;
%}

%%
var     {if(m_tokenFlag) std::cout << "T_VAR" << std::endl; return T_VAR;}
float   {if(m_tokenFlag) std::cout << "T_TYPE_FLOAT" << std::endl; return T_TYPE_FLOAT;}
int     {if(m_tokenFlag) std::cout << "T_TYPE_INT" << std::endl; return T_TYPE_INT;}
string  {if(m_tokenFlag) std::cout << "T_TYPE_STRING" << std::endl; return T_TYPE_STRING;}
while   {if(m_tokenFlag) std::cout << "T_WHILE" << std::endl; return T_WHILE;}
if      {if(m_tokenFlag) std::cout << "T_IF" << std::endl; return T_IF;}
else    {if(m_tokenFlag) std::cout << "T_ELSE" << std::endl; return T_ELSE;}
print   {if(m_tokenFlag) std::cout << "T_PRINT" << std::endl; return T_PRINT;}
read    {if(m_tokenFlag) std::cout << "T_READ" << std::endl; return T_READ;}
boolean {if(m_tokenFlag) std::cout << "T_BOOLEAN" << std::endl; return T_BOOLEAN;}
TRUE    {if(m_tokenFlag) std::cout << "T_TRUE" << std::endl; return T_TRUE;}
FALSE   {if(m_tokenFlag) std::cout << "T_FALSE" << std::endl; return T_FALSE;}
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

[ \t\r\n] {
    // White-space
}

[a-zA-Z_][a-zA-Z0-9_]* {
    if(m_tokenFlag) std::cout << "T_IDENTIFIER" << std::endl;
    return T_IDENTIFIER;
}

(0|[1-9][0-9]+)\.[0-9]+  {
    if(m_tokenFlag) std::cout << "T_FLOAT" << std::endl;
    return T_FLOAT;
}

0|([1-9][0-9]*) {
    if(m_tokenFlag) std::cout << "T_INTEGER" << std::endl;
    return T_INTEGER;
}

\"((\\[abfnrtv\"\\])|[ \ta-zA-Z0-9\~\@\#\$\%\^\&\*\-\+\/\`\<\>\=\_\|\'\.\,\;\:\!\?\{\}\[\]\(\)])*\"  {
    if(m_tokenFlag) std::cout << "T_STRING" << std::endl;
    return T_STRING;
}

"//".* {
    // Inline comment
}

. {
    // EVERYTHING ELSE
    std::cerr << "Invalid token: " << yytext << std::endl;
    exit(CODE_COMPILER_ERROR);
}
%%

