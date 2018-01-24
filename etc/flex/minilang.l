%{
// MiniLang Compiler
// Author: Amir El Bawab
// ML = MiniLang

// ML Include
#include <bison/minilang_bison.h>
#include <iostream>

// ML defines
#define YY_DECL extern "C" int yylex()

// Exit codes
const int CODE_LEXICAL_ERROR = 1;

// Lexical error function
void lexicalError(char* message);
%}

%%
[ \t\r\n] {}

(0|[1-9][0-9]+)\.[0-9]+  {
    // FLOAT
    std::cout << "Found a floating-point number:" << yytext << std::endl;
}

0|([1-9][0-9]*) {
    // INTEGER
    std::cout << "Found an integer:" << yytext << std::endl;
}

\"((\\[abfnrtv\"\\])|[ \ta-zA-Z0-9\~\@\#\$\%\^\&\*\-\+\/\`\<\>\=\_\|\'\.\,\;\:\!\?\{\}\[\]\(\)])*\"  {
    // STRING
    std::cout << "Found a string: " << yytext << std::endl;
}

"//".* {
    // INLINE COMMENT
    std::cout << "Found a comment: " << yytext << std::endl;
}

. {
    // EVERYTHING ELSE
    std::cerr << "Invalid token: " << yytext << std::endl;
    exit(CODE_LEXICAL_ERROR);
}
%%

