#include <minilang/mwhile.h>
#include <minilang/mutils.h>
#include <minilang/mreport.h>
#include <sstream>

std::string mini::MWhile::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "while " << m_condition->prettify() << " {";
    if(m_statements) {
        ss << std::endl;
        for(mini::MStatement* statement : *m_statements) {
            ss << statement->prettify(indent+1) << std::endl;
        }
        ss << mini::utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}

void mini::MWhile::typeCheck() {
    mini::TYPE conditionType = m_condition->evalType();
    if(conditionType != mini::TYPE::BOOLEAN && conditionType != mini::TYPE::INTEGER) {
        mini::error_exit("While condition must evaluate to boolean or integer");
    }

    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            statement->typeCheck();
        }
    }
}

std::string mini::MWhile::toC(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "while ( " << m_condition->toC() << " ) {";
    if(m_statements) {
        ss << std::endl;
        for(mini::MStatement* statement : *m_statements) {
            ss << statement->toC(indent+1) << std::endl;
        }
        ss << mini::utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}
