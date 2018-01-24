%{
// MiniLang Compiler
// Author: Amir El Bawab
// ML = MiniLang

// ML Include
#include <bison/minilang_bison.h>
#include <iostream>

// ML defines
#define YY_DECL extern "C" int yylex()
%}

%%
[ \t\r\n]                ;
(0|[1-9][0-9]+)\.[0-9]+  { std::cout << "Found a floating-point number:" << yytext << std::endl; }
0|([1-9][0-9]*)          { std::cout << "Found an integer:" << yytext << std::endl; }
[a-zA-Z]+                { std::cout << "Found a string: " << yytext << std::endl; }
"//".*                   { std::cout << "Found a comment: " << yytext << std::endl; }
.                        { std::cout << "Invalid token: " << yytext << std::endl; }
%%
