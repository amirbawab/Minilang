#include <minilang/mif.h>
#include <minilang/mutils.h>
#include <minilang/mreport.h>
#include <sstream>

std::string mini::MIf::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "if " << m_condition->prettify() << " {";
    if(m_statements) {
        ss << std::endl;
        for(mini::MStatement* statement : *m_statements) {
            ss << statement->prettify(indent+1) << std::endl;
        }
        ss << mini::utils::indent(indent);
    }
    ss << "}";

    // Else statement (if exists)
    if(m_else) {
        ss << m_else->prettify(indent);
    }
    return ss.str();
}

void mini::MIf::typeCheck() {
    if(m_condition->evalType() != mini::TYPE::BOOLEAN) {
        mini::error_exit("While condition must evaluate to boolean");
    }

    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            statement->typeCheck();
        }
    }
}
