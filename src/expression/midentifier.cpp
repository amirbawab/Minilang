#include <minilang/midentifier.h>

mini::TYPE mini::MIdentifer::evalType() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get type of an identifier with an undetermined reference variable");
    }
    return m_variable->getType();
}

std::string mini::MIdentifer::prettify() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get name of an identifier with an undetermined reference variable");
    }
    return m_variable->getName();
}