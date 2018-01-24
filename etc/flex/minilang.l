%{
// MiniLang Compiler
// Author: Amir El Bawab
// ML = MiniLang

// ML Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>

// ML defines
#define YY_DECL extern "C" int yylex()

// ML variables
std::vector<std::string> m_inputFiles;
std::string m_outputFile;

// ML Exit code
const int CODE_PARAM_ERROR = 2;
const int CODE_COMPILER_ERROR = 1;
const int CODE_SUCCESS = 0;
%}

%%
[ \t\n]         ;
[0-9]+\.[0-9]+  { std::cout << "Found a floating-point number:" << yytext << std::endl; }
[0-9]+          { std::cout << "Found an integer:" << yytext << std::endl; }
[a-zA-Z0-9]+    { std::cout << "Found a string: " << yytext << std::endl; }
%%

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

    // Run lexical analyzer
	yylex();

	return CODE_SUCCESS;
}
