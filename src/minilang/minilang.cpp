#include <minilang/minilang.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <getopt.h>
#include <cstdlib>

// Information for Flex
extern "C" FILE *yyin;
extern "C" int yyparse();
extern "C" int yylex();
extern "C" int yylineno;

// ML variables
std::vector<std::string> m_inputFiles;

// Program flags
bool m_tokenFlag = false;
bool m_scanFlag = false;
bool m_parseFlag = false;

/**
 * Syntax error function
 */
void yyerror(const char *s) {
    std::cout << "Error: " << s << " at line " << yylineno << std::endl;
    exit(CODE_COMPILER_ERROR);
}

/**
 * Print compiler usage to STDOUT
 */
void printUsage() {
    std::cout
            << "MiniLang - A mini language compiler using Flex/Bison" << std::endl
            << "Usage: minilang [OPTION]... [FILE]..." << std::endl
            << "    -s, --scan            Scan input. Exit (1) on error" << std::endl
            << "    -t, --tokens          Print tokens" << std::endl
            << "    -p, --parse           Parse tokens" << std::endl
            << "    -h, --help            Display this help message" << std::endl;
}

/**
 * Initialize parameters passed to the compiler
 */
void initParams(int argc, char *argv[]) {
    struct option longOptions[] = {
            {"tokens", no_argument, 0, 't'},
            {"scan", no_argument, 0, 's'},
            {"parse", no_argument, 0, 'p'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    int optionIndex = 0;
    int c;
    while ((c = getopt_long(argc, argv, "hspt", longOptions, &optionIndex)) != -1) {
        switch (c) {
            case 't':
                m_tokenFlag = true;
                break;
            case 's':
                m_scanFlag = true;
                break;
            case 'p':
                m_parseFlag = true;
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
    return !m_inputFiles.empty() && (m_scanFlag || m_parseFlag || m_tokenFlag);
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

    if(m_tokenFlag || m_scanFlag) {
        while (yylex()) {}
    } else if(m_parseFlag) {
        do { yyparse(); } while (!feof(yyin));
    }

    return CODE_SUCCESS;
}
