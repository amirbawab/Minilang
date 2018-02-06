#include <minilang/midentifier.h>
#include <minilang/mreport.h>
#include <minilang/mutils.h>
#include <minilang/mvariable.h>
#include <minilang/mglobal.h>
#include <sstream>

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
    if(m_variable->getType() != m_expression->evalType()) {
        mini::error_exit("Identifier " + m_name + " was assigned an unexpected expression type");
    }
}

void mini::MIdentifier::linkVariable() {
    mini::MVariable* variable = mini::MGlobal::getInstance()->findVariable(m_name);
    if(!variable) {
        mini::error_exit("Identifier " + m_name + " was not declared");
    }
    m_variable = variable;
}