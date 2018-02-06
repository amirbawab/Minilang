#include <minilang/midentifier.h>
#include <minilang/mreport.h>
#include <minilang/mutils.h>
#include <minilang/mvariable.h>
#include <sstream>

mini::TYPE mini::MIdentifier::evalType() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get type of an identifier with an undetermined reference variable");
    }
    return m_variable->getType();
}

std::string mini::MIdentifier::prettify() {
    return getName();
}

std::string mini::MIdentifier::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << getName() << std::endl;
    return ss.str();
}
