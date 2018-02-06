#include <minilang/mtable.h>
#include <minilang/mreport.h>
#include <sstream>

std::string mini::MTable::str() {
    std::stringstream ss;
    ss << "---- Global Scope ----" << std::endl;
    for(auto variableEntry : m_variableMap) {
        ss << variableEntry.first << " : " << variableEntry.second->getMiniType() << std::endl;
    }
    ss << "----------------------" << std::endl;
    return ss.str();
}

mini::MVariable* mini::MTable::getVariable(std::string name) {
    if(m_variableMap.find(name) != m_variableMap.end()) {
        return m_variableMap[name];
    }
    return nullptr;
}

void mini::MTable::registerVariable(mini::MVariable *variable) {
    if(getVariable(variable->getIdentifier()->getName())) {
        mini::error_exit("Multiple declaration of variable " + variable->getIdentifier()->getName());
    }
    m_variableMap[variable->getIdentifier()->getName()] = variable;
}