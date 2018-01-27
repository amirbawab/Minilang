#pragma once

#define CODE_PARAM_ERROR 2
#define CODE_COMPILER_ERROR 1
#define CODE_SUCCESS 0

/**
 * Bison required error function
 * @param s
 */
void yyerror(const char *s);
