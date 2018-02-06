#include <minilang/mvariable.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MVariable::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "var " << m_identifier->getName() << " : ";
    switch (m_type) {
        case mini::TYPE::STRING:
            ss << "string";
            break;
        case mini::TYPE::INTEGER:
            ss << "int";
            break;
        case mini::TYPE::FLOAT:
            ss << "float";
            break;
        case mini::TYPE::BOOLEAN:
            ss << "boolean";
            break;
        default:
            throw std::runtime_error("Cannot generate code for a variable with an undefined type");
    }
    ss << " = " << m_identifier->getExpression()->prettify() << ";";
    return ss.str();
}