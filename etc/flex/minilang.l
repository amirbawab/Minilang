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
var     return T_VAR;
float   return T_TYPE_FLOAT;
int     return T_TYPE_INT;
string  return T_TYPE_STRING;
while   return T_WHILE;
if      return T_IF;
else    return T_ELSE;
print   return T_PRINT;
read    return T_READ;
boolean return T_BOOLEAN;
TRUE    return T_TRUE;
FALSE   return T_FALSE;
":"     return T_COLON;
";"     return T_SEMICOLON;
"="     return T_EQUAL;
"=="    return T_IS_EQUAL;
"!="    return T_IS_NOT_EQUAL;
"&&"    return T_AND;
"||"    return T_OR;
"{"     return T_LCURL;
"}"     return T_RCURL;
"+"     return T_PLUS;
"-"     return T_MINUS;
"*"     return T_MULT;
"/"     return T_DIV;
"("     return T_LPAR;
")"     return T_RPAR;

[ \t\r\n] {
    // White-space
}

[a-zA-Z_][a-zA-Z0-9_]* {
    return T_IDENTIFIER;
}

(0|[1-9][0-9]+)\.[0-9]+  {
    return T_FLOAT;
}

0|([1-9][0-9]*) {
    return T_INTEGER;
}

\"((\\[abfnrtv\"\\])|[ \ta-zA-Z0-9\~\@\#\$\%\^\&\*\-\+\/\`\<\>\=\_\|\'\.\,\;\:\!\?\{\}\[\]\(\)])*\"  {
    return T_STRING;
}

"//".* {
    // Inline comment
}

. {
    // EVERYTHING ELSE
    std::cerr << "Invalid token: " << yytext << std::endl;
    exit(CODE_LEXICAL_ERROR);
}
%%

