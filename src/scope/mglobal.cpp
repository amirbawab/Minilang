#include <minilang/mglobal.h>
#include <sstream>

std::string mini::MGlobal::prettify(int indent) {
    std::stringstream ss;
    for(mini::MVariable* variable : *m_variables) {
        ss << variable->prettify() << std::endl;
    }
    for(mini::MStatement* statement : *m_statements) {
        ss << statement->prettify(0) << std::endl;
    }
    return ss.str();
}