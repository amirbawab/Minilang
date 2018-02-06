#include <minilang/midentifier.h>
#include <minilang/mreport.h>
#include <minilang/mutils.h>
#include <minilang/mvariable.h>
#include <minilang/mglobal.h>
#include <sstream>
#include <iostream>

mini::TYPE mini::MIdentifier::evalType() {
    linkVariable();
    return m_variable->getType();
}

std::string mini::MIdentifier::prettify() {
    return getName();
}

std::string mini::MIdentifier::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << getName() << " = " << m_expression->prettify() << ";";
    return ss.str();
}

void mini::MIdentifier::typeCheck() {
    linkVariable();
    m_variable->compatibleExpr(m_expression);
}

void mini::MIdentifier::linkVariable() {
    std::vector<mini::MVariable*> variables = mini::MGlobal::getInstance()->findVariables(m_name);

    // If not variable found
    if(variables.empty()) {
        mini::error_exit("Identifier " + m_name + " was not declared");
    }
    m_variable = variables.front();
}