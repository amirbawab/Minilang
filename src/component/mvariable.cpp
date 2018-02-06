#include <minilang/mvariable.h>
#include <minilang/mutils.h>
#include <minilang/mglobal.h>
#include <minilang/mreport.h>
#include <sstream>
#include <iostream>

std::string mini::MVariable::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "var " << m_identifier->getName() << " : "
       << getMiniType() << " = " << m_identifier->getExpression()->prettify() << ";";
    return ss.str();
}

std::string mini::MVariable::toC(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << getCType() << " " << m_identifier->getName()
       << " = " << m_identifier->getExpression()->prettify() << ";";
    return ss.str();
}

void mini::MVariable::checkExist() {
    std::vector<mini::MVariable*> variables = mini::MGlobal::getInstance()->findVariables(m_identifier->getName());
    if(variables.size() > 1) {
        mini::error_exit("Variable " + m_identifier->getName() +" already declared");
    }
}

void mini::MVariable::typeCheck() {
    compatibleExpr(m_identifier->getExpression());
}

void mini::MVariable::compatibleExpr(mini::MExpression *expression) {
    mini::TYPE expressionType = expression->evalType();
    if(expressionType != getType()
       && !(getType() == mini::TYPE::FLOAT && expressionType == mini::TYPE::INTEGER)) {
        mini::error_exit("Variable " + m_identifier->getName() + " is assigned an unexpected expression type");
    }
}

std::string mini::MVariable::getMiniType() {
    switch (m_type) {
        case mini::TYPE::STRING:
            return "string";
        case mini::TYPE::INTEGER:
            return "int";
        case mini::TYPE::FLOAT:
            return "float";
        case mini::TYPE::BOOLEAN:
            return "boolean";
        default:
            throw std::runtime_error("Cannot generate code for a variable with an undefined type");
    }
}

std::string mini::MVariable::getCType() {
    switch (m_type) {
        case mini::TYPE::STRING:
            return "char*";
        case mini::TYPE::INTEGER:
            return "int";
        case mini::TYPE::FLOAT:
            return "float";
        case mini::TYPE::BOOLEAN:
            return "bool";
        default:
            throw std::runtime_error("Cannot generate code for a variable with an undefined type");
    }
}
