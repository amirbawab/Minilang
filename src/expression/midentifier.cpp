#include <minilang/midentifier.h>
#include <iostream>

mini::TYPE mini::MIdentifier::evalType() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get type of an identifier with an undetermined reference variable");
    }
    return m_variable->getType();
}

std::string mini::MIdentifier::prettify() {
    if(!m_variable) {
        throw std::runtime_error("Cannot get name of an identifier with an undetermined reference variable");
    }
    return m_variable->getName();
}