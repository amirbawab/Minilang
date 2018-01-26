#include <minilang/minilang.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>

// Information for Flex
extern "C" FILE *yyin;
extern "C" int yyparse();
extern "C" int yylex();

// ML variables
std::vector<std::string> m_inputFiles;
std::string m_outputFile;

// Program flags
bool m_tokenFlag = false;
bool m_scanFlag = false;
bool m_parseFlag = false;

// Keep track of errors
bool syntaxErrorFlag = false;

/**
 * Syntax error function
 */
void yyerror(const char *s) {
    std::cout << "Error: Syntax error" << std::endl;
    syntaxErrorFlag = true;
}

/**
 * Syntax error
 * @param s
 */
void syError(const char *s) {
    std::cerr << "Error: " << s << std::endl;
    syntaxErrorFlag = true;
}

/**
 * Syntax error
 */
void syErrorEOF() {
    syError("Unexpected end of file");
    exit(CODE_COMPILER_ERROR);
}

/**
 * Print compiler usage to STDOUT
 */
void printUsage() {
    std::cout
            << "MiniLang - A mini language compiler using Flex/Bison" << std::endl
            << "Usage: minilang [OPTION]... [FILE]..." << std::endl
            << "    -s, --scan            Scan input" << std::endl
            << "    -t, --token           Print tokens" << std::endl
            << "    -o, --output          Output file path. If not used print to STDOUT" << std::endl
            << "    -h, --help            Display this help message" << std::endl;
}

/**
 * Initialize parameters passed to the compiler
 */
void initParams(int argc, char *argv[]) {
    struct option longOptions[] = {
            {"token", no_argument, 0, 't'},
            {"scan", no_argument, 0, 's'},
            {"parse", no_argument, 0, 'p'},
            {"output", required_argument, 0, 'o'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    int optionIndex = 0;
    int c;
    while ((c = getopt_long(argc, argv, "hspto:", longOptions, &optionIndex)) != -1) {
        switch (c) {
            case 'o':
                m_outputFile = optarg;
                break;
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

    if(m_tokenFlag || m_scanFlag) {
        while (yylex()) {}
    } else if(m_parseFlag) {
        do { yyparse(); } while (!feof(yyin));
        return !syntaxErrorFlag ? CODE_SUCCESS : CODE_COMPILER_ERROR;
    }

    return CODE_SUCCESS;
}
