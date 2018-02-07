#include <minilang/mvariable.h>
#include <minilang/mutils.h>
#include <minilang/mglobal.h>
#include <minilang/mreport.h>
#include <sstream>
#include <iostream>

std::string mini::MVariable::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "var " << m_identifier->getName() << " : "
       << mini::utils::toMiniType(getType()) << " = " << m_identifier->getExpression()->prettify() << ";";
    return ss.str();
}

std::string mini::MVariable::toC(int indent) {
    std::stringstream ss;
    if (m_type == mini::TYPE::STRING) {
        ss << mini::utils::indent(indent) << mini::utils::toCType(getType()) << " " << m_identifier->getCName()
           << " = malloc(sizeof(char) * 1024);" << std::endl;
        if (m_identifier->getExpression()->evalType() == mini::TYPE::BOOLEAN) {
            ss << mini::utils::indent(indent) << "strcpy(" << m_identifier->getCName()
               << ", btoa(" << m_identifier->getExpression()->toC() << "));";
        } else {
            ss << mini::utils::indent(indent) << "strcpy(" << m_identifier->getCName()
               << ", " << m_identifier->getExpression()->toC() << ");";
        }
    } else if(m_type == mini::TYPE::BOOLEAN && m_identifier->getExpression()->evalType() == mini::TYPE::STRING) {
        ss << mini::utils::indent(indent) << mini::utils::toCType(getType()) << " " << m_identifier->getCName()
           << " = atob(" << m_identifier->getExpression()->toC() << ");";
    } else {
        ss << mini::utils::indent(indent) << mini::utils::toCType(getType()) << " " << m_identifier->getCName()
           << " = " << m_identifier->getExpression()->toC() << ";";
    }
    return ss.str();
}

void mini::MVariable::checkExist() {
    mini::MVariable* variable = mini::MGlobal::getInstance()->findVariable(m_identifier->getName());
    if(variable) {
        mini::error_exit("Variable " + m_identifier->getName() +" already declared");
    }
}

void mini::MVariable::typeCheck() {
    compatibleExpr(m_identifier->getExpression());
}

void mini::MVariable::compatibleExpr(mini::MExpression *expression) {
    mini::TYPE expressionType = expression->evalType();
    if(expressionType != getType()
       && !(getType() == mini::TYPE::FLOAT && expressionType == mini::TYPE::INTEGER)
       && !(getType() == mini::TYPE::BOOLEAN && expressionType == mini::TYPE::STRING)
       && !(getType() == mini::TYPE::STRING) && expressionType == mini::TYPE::BOOLEAN) {
        mini::error_exit("Variable " + m_identifier->getName() + " is assigned an unexpected expression type");
    }
}