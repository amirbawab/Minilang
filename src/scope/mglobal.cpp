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
    ss  << "/***********************************" << std::endl
        << " * THIS PROGRAM IS AUTO GENERATED" << std::endl
        << " ***********************************/" << std::endl
        << "#include <stdio.h>" << std::endl
        << "#include <stdlib.h>" << std::endl
        << "#include <stdbool.h>" << std::endl
        << "#include <string.h>" << std::endl
        << std::endl;

    ss << "int main() {" << std::endl;
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
                ss << mini::utils::indent(indent+1) << "free( " << variable->getIdentifier()->getName()
                   << " );" << std::endl;
            }
        }
    }
    ss << mini::utils::indent(indent+1) << "return (0);" << std::endl;
    ss << "}" << std::endl;
    return ss.str();
}

std::string mini::MGlobal::toSymbolTable() {
    return m_table.str();
}