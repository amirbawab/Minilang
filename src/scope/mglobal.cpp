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
    ss << "#include <stdio.h>" << std::endl;
    ss << "int main() {" << std::endl;
    if(m_variables) {
        for(mini::MVariable* variable : *m_variables) {
            ss << variable->toC(indent+1) << std::endl;
        }
    }

    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            ss << statement->toC(indent+1) << std::endl;
        }
    }
    ss << mini::utils::indent(indent+1) << "return (0);" << std::endl;
    ss << "}" << std::endl;
    return ss.str();
}

std::string mini::MGlobal::toSymbolTable() {
    return m_table.str();
}