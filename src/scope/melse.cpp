#include <minilang/melse.h>

#include <minilang/mutils.h>
#include <sstream>

std::string mini::MElse::prettify(int indent) {
    std::stringstream ss;
    ss << " else {";
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

std::string mini::MElse::toC(int indent) {
    std::stringstream ss;
    ss << " else {";
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

void mini::MElse::typeCheck() {
    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            statement->typeCheck();
        }
    }
}
