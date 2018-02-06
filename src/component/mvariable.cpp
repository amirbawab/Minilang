#include <minilang/mvariable.h>
#include <minilang/mutils.h>
#include <minilang/mglobal.h>
#include <minilang/mreport.h>
#include <sstream>
#include <iostream>

std::string mini::MVariable::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "var " << m_identifier->getName() << " : ";
    switch (m_type) {
        case mini::TYPE::STRING:
            ss << "string";
            break;
        case mini::TYPE::INTEGER:
            ss << "int";
            break;
        case mini::TYPE::FLOAT:
            ss << "float";
            break;
        case mini::TYPE::BOOLEAN:
            ss << "boolean";
            break;
        default:
            throw std::runtime_error("Cannot generate code for a variable with an undefined type");
    }
    ss << " = " << m_identifier->getExpression()->prettify() << ";";
    return ss.str();
}

void mini::MVariable::checkExist() {
    std::vector<mini::MVariable*> variables = mini::MGlobal::getInstance()->findVariables(m_identifier->getName());
    if(variables.size() > 1) {
        mini::error_exit("Variable " + m_identifier->getName() +" already declared");
    }
}

void mini::MVariable::typeCheck() {
    if(m_identifier->getExpression()->evalType() != getType()) {
        mini::error_exit("Variable " + m_identifier->getName() + " is assigned an unexpected expression type");
    }
}