#include <minilang/mwhile.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MWhile::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "while " << m_condition->prettify() << " {" << std::endl;
    for(mini::MStatement* statement : *m_statements) {
        ss << mini::utils::indent(indent+1) << statement->prettify(indent+1) << std::endl;
    }
    ss << mini::utils::indent(indent) << "}" << std::endl;
    return ss.str();
}