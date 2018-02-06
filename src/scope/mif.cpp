#include <minilang/mif.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MIf::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "if " << m_condition->prettify() << " {" << std::endl;
    for(mini::MStatement* statement : *m_statements) {
        ss << mini::utils::indent(indent+1) << statement->prettify(indent+1) << std::endl;
    }
    ss << mini::utils::indent(indent) << "}";

    // Else statement (if exists)
    if(m_else) {
        ss << m_else->prettify(indent);
    } else {
        ss << std::endl;
    }
    return ss.str();
}