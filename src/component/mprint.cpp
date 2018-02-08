#include <minilang/mprint.h>
#include <minilang/mutils.h>

std::string mini::MPrint::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "print " << m_expression->prettify() << ";";
    return ss.str();
}

std::string mini::MPrint::toC(int indent) {
    std::stringstream ss;
    mini::TYPE exprType = m_expression->evalType();
    if(exprType == mini::TYPE::BOOLEAN) {
        ss << mini::utils::indent(indent) << "printf(\"" << mini::utils::toCStringFormat(exprType) << "\\n\", "
           << "btoa(" << m_expression->toC() << "));";
    } else {
        ss << mini::utils::indent(indent) << "printf(\"" << mini::utils::toCStringFormat(exprType) << "\\n\", "
           << m_expression->toC() << ");";
    }
    return ss.str();
}

void mini::MPrint::typeCheck() {
    m_expression->evalType();
}

mini::MPrint::~MPrint() {
    if(m_expression) {
        delete m_expression;
    }
}