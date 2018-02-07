#include <minilang/mglobal.h>
#include <sstream>
#include <iostream>
#include <minilang/mutils.h>

std::string mini::MGlobal::prettify(int indent) {
    std::stringstream ss;
    if(m_variables) {
        for(mini::MVariable* variable : *m_variables) {
            ss << variable->prettify(indent) << std::endl;
        }
    }

    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            ss << statement->prettify(indent) << std::endl;
        }
    }
    return ss.str();
}

mini::MVariable* mini::MGlobal::findVariable(std::string name) {
    return m_table.getVariable(name);
}

void mini::MGlobal::typeCheck() {
    if(m_variables) {
        for(mini::MVariable* variable : *m_variables) {
            variable->checkExist();
            variable->typeCheck();
            m_table.registerVariable(variable);
        }
    }
    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            statement->typeCheck();
        }
    }
}

std::string mini::MGlobal::toC(int indent) {
    std::stringstream ss;
    ss << "/***********************************" << std::endl
       << " * THIS PROGRAM IS AUTO GENERATED" << std::endl
       << " ***********************************/" << std::endl
       << "#include <stdio.h>" << std::endl
       << "#include <stdlib.h>" << std::endl
       << "#include <stdbool.h>" << std::endl
       << "#include <string.h>" << std::endl
       << std::endl;

    // Repeat String function
    ss << mini::utils::indent(indent)   << "char* repeatStr(char* str, int times) {" << std::endl
       << mini::utils::indent(indent+1)     << "if (times < 0) {" << std::endl
       << mini::utils::indent(indent+2)         << "fprintf(stderr, \"Repeat value cannot be negative\\n\");" << std::endl
       << mini::utils::indent(indent+2)         << "exit(1);" << std::endl
       << mini::utils::indent(indent+1)     << "}" << std::endl
       << mini::utils::indent(indent+1)     << "size_t slen = strlen(str);" << std::endl
       << mini::utils::indent(indent+1)     << "char* dest = malloc(times * slen + 1);" << std::endl
       << mini::utils::indent(indent+1)     << "int i; char* p;" << std::endl
       << mini::utils::indent(indent+1)     << "for(i=0, p=dest; i < times; ++i, p += slen) {" << std::endl
       << mini::utils::indent(indent+2)         << "memcpy(p, str, slen);" << std::endl
       << mini::utils::indent(indent+1)     << "}" << std::endl
       << mini::utils::indent(indent+1)     << "*p = '\\0';" << std::endl
       << mini::utils::indent(indent+1)     << "return dest;" << std::endl
       << mini::utils::indent(indent)   << "}" << std::endl
       << std::endl;

    // String concatenation
    ss << mini::utils::indent(indent) << "char* cat(char *str1, char *str2) {" << std::endl
       << mini::utils::indent(indent+1)     <<"char* str1Cp = malloc(sizeof(char) * 1024);" << std::endl
       << mini::utils::indent(indent+1)     << "char* ptr = str1Cp;" << std::endl
       << mini::utils::indent(indent+1)     << "strcpy(ptr, str1);" << std::endl
       << mini::utils::indent(indent+1)     << "while(*ptr) {" << std::endl
       << mini::utils::indent(indent+2)         << "ptr++;" << std::endl
       << mini::utils::indent(indent+1)     << "}" << std::endl
       << mini::utils::indent(indent+1)     << "while(*str2) {" << std::endl
       << mini::utils::indent(indent+2)         << "*ptr = *str2;" << std::endl
       << mini::utils::indent(indent+2)         << "str2++;" << std::endl
       << mini::utils::indent(indent+2)         << "ptr++;" << std::endl
       << mini::utils::indent(indent+1)     << "}" << std::endl
       << mini::utils::indent(indent+1)     << "*ptr = '\\0';" << std::endl
       << mini::utils::indent(indent+1)     << "return str1Cp;" << std::endl
       << mini::utils::indent(indent) << "}" << std::endl
       << std::endl;

    ss << mini::utils::indent(indent) << "void scanb(bool *id) {" << std::endl
       << mini::utils::indent(indent+1) <<    "char* boolStr = malloc(sizeof(char) * 1024);" << std::endl
       << mini::utils::indent(indent+1) <<    "scanf(\"%s\", boolStr);" << std::endl
       << mini::utils::indent(indent+1) <<    "if(strcmp(boolStr, \"TRUE\") == 0) {" << std::endl
       << mini::utils::indent(indent+2) <<        "*id = true;" << std::endl
       << mini::utils::indent(indent+1) <<    "} else if(strcmp(boolStr, \"FALSE\") == 0) {" << std::endl
       << mini::utils::indent(indent+2) <<        "*id = false;" << std::endl
       << mini::utils::indent(indent+1) <<    "} else {" << std::endl
       << mini::utils::indent(indent+2) <<        "fprintf(stderr, \"Value '%s' is not a "
            "valid boolean value. Expecting TRUE or FALSE\\n\", boolStr);" << std::endl
       << mini::utils::indent(indent+2) <<        "exit(1);" << std::endl
       << mini::utils::indent(indent+1) <<    "}" << std::endl
       << mini::utils::indent(indent) << "}" << std::endl
       << std::endl;

    // Boolean to ascii
    ss << mini::utils::indent(indent) << "char* btoa(bool val) {" << std::endl
       << mini::utils::indent(indent)   << "if(val) {" << std::endl
       << mini::utils::indent(indent)       << "return \"TRUE\";" << std::endl
       << mini::utils::indent(indent)   << "} else {" << std::endl
       << mini::utils::indent(indent)       << "return \"FALSE\";" << std::endl
       << mini::utils::indent(indent)   << "}" << std::endl
       << mini::utils::indent(indent) << "}" << std::endl
       << std::endl;

    // Main function
    ss << mini::utils::indent(indent) << "int main() {" << std::endl;
    // Declare and initialize variables
    if(m_variables) {
        ss << mini::utils::indent(indent+1) << "// Declare and initialize variables" << std::endl;
        for(mini::MVariable* variable : *m_variables) {
            ss << variable->toC(indent+1) << std::endl;
        }
        ss << std::endl;
    }

    // Create statements
    if(m_statements) {
        ss << mini::utils::indent(indent+1) << "// Statements" << std::endl;
        for(mini::MStatement* statement : *m_statements) {
            ss << statement->toC(indent+1) << std::endl;
        }
        ss << std::endl;
    }

    // Free memory
    if(m_variables) {
        for(mini::MVariable* variable : *m_variables) {
            if(variable->getType() == mini::TYPE::STRING) {
                ss << mini::utils::indent(indent+1) << "free( " << variable->getIdentifier()->getCName()
                   << " );" << std::endl;
            }
        }
    }
    ss << mini::utils::indent(indent+1) << "return (0);" << std::endl;
    ss << mini::utils::indent(indent) << "}" << std::endl;
    return ss.str();
}

std::string mini::MGlobal::toSymbolTable() {
    return m_table.str();
}