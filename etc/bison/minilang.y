%{
// ML Includes
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

// ML variables
std::vector<std::string> m_inputFiles;
std::string m_outputFile;

// ML Exit code
const int CODE_PARAM_ERROR = 2;
const int CODE_COMPILER_ERROR = 1;
const int CODE_SUCCESS = 0;

// Function protoytpes
void yyerror(const char *s);
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

/**
 * Syntax error function
 */
void yyerror(const char *s) {
	std::cerr << "Error: " << s << std::endl;
	exit(CODE_COMPILER_ERROR);
}

/**
 * Print compiler usage to STDOUT
 */
void printUsage() {
        std::cout
        << "MiniLang - A mini language compiler using Flex/Bison" << std::endl
        << "Usage: minilang [OPTION]... [FILE]..." << std::endl
        << "    -o, --output          Output file path. If not used print to STDOUT" << std::endl
        << "    -h, --help            Display this help message" << std::endl;
}

/**
 * Initialize parameters passed to the compiler
 */
void initParams(int argc, char *argv[]) {
    struct option longOptions[] = {
            {"output", required_argument, 0, 'o'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    int optionIndex = 0;
    int c;
    while ((c = getopt_long(argc, argv, "ho:", longOptions, &optionIndex)) != -1) {
        switch (c) {
            case 'o':
                m_outputFile = optarg;
                break;
            case 'h':
            default:
                // Print by default
                break;
        }
    }
}

/**
 * Check if the compiler has all required parameters
 * @return true if all required arguments are set
 */
bool validArguments() {
    return !m_inputFiles.empty();
}

/**
 * Fetch input files from the list of arguments passed
 */
void fetchInputFiles(const int argc, char *argv[]) {
    for(int i = optind; i < argc; ++i) {
        m_inputFiles.push_back(argv[i]);
    }
}

/**
 * Compiler starts here
 */
int main(int argc, char** argv) {

    // Initialize params
    initParams(argc, argv);

    // Fetch input filesa
    fetchInputFiles(argc, argv);

    // Check if arguments are valid
    if(!validArguments()) {
        printUsage();
        return CODE_PARAM_ERROR;
    }

    // Read file
    std::string inputFileName = m_inputFiles[0];
	FILE *inputFile = fopen(inputFileName.c_str(), "r");
	if (!inputFile) {
		std::cerr << "Cannot open input file: " << inputFileName << std::endl;
		return CODE_PARAM_ERROR;
	}
	yyin = inputFile;

	// Create lexical tokens and validate them against the grammar
    do {
        // Run "lexical" and "syntax" analyzers
        yyparse();
    } while (!feof(yyin));

	return CODE_SUCCESS;
}
