#include <minilang/mvariable.h>
#include <sstream>

std::string mini::MVariable::prettify() {
    std::stringstream ss;
    switch (m_type) {
        case mini::TYPE::STRING:
            ss << "char*";
            break;
        case mini::TYPE::INTEGER:
            ss << "int";
            break;
        case mini::TYPE::FLOAT:
            ss << "float";
            break;
        case mini::TYPE::BOOLEAN:
            ss << "bool";
            break;
        default:
            throw std::runtime_error("Cannot generate code for a variable with an undefined type");
    }
    ss << " " << m_identifier->getName() << " = " << m_identifier->getExpression()->prettify() << ";" << std::endl;
    return ss.str();
}