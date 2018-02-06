#include <minilang/mglobal.h>
#include <sstream>
#include <iostream>

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

std::vector<mini::MVariable*> mini::MGlobal::findVariables(std::string name) {
    std::vector<mini::MVariable*> variables;
    if(m_variables) {
        for(mini::MVariable* variable : *m_variables) {
            if(name == variable->getIdentifier()->getName()) {
                variables.push_back(variable);
            }
        }
    }
    return variables;
}

void mini::MGlobal::typeCheck() {
    if(m_variables) {
        for(mini::MVariable* variable : *m_variables) {
            variable->checkExist();
            variable->typeCheck();
        }
    }
    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            statement->typeCheck();
        }
    }
}