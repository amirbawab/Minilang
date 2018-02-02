#include <minilang/midentifier.h>
#include <minilang/mreport.h>
#include <iostream>

mini::TYPE mini::MIdentifier::evalType() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get type of an identifier with an undetermined reference variable");
    }
    return m_variable->getType();
}

std::string mini::MIdentifier::prettify() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get name of an identifier with an undetermined reference variable");
    }
    return m_variable->getName();
}

void mini::MIdentifier::setExpression(mini::MExpression *expression) {
    if(evalType() != expression->evalType()) {
        mini::error_exit("Cannot assign an expression to an identifier with a different type");
    }
    m_expression = expression;
}