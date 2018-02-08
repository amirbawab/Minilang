#include <minilang/munary.h>
#include <minilang/mreport.h>
#include <sstream>

mini::TYPE mini::MUnary::evalType() {
    if(m_kind == KIND::UNDEFINED) {
        throw std::runtime_error("Cannot get the type of an undefined binary expression");
    }

    TYPE operandType = m_operand->evalType();
    switch (m_kind) {
        case U_MINUS:
            if(operandType != mini::TYPE::INTEGER && operandType != mini::TYPE::FLOAT) {
                mini::report::error_exit("unary operator - expects the operand to be an integer or float", getLine());
            }
            return operandType;

        case U_NOT:
            if(operandType != mini::TYPE::BOOLEAN) {
                mini::report::error_exit("unary operator ! expects the operand to be a boolean", getLine());
            }
            return mini::TYPE::BOOLEAN;
        default:
            throw std::runtime_error("Unrecognized type while evaluating the type of the expression");
    }
}

std::string mini::MUnary::prettify() {
    std::stringstream ss;
    std::string opt;
    switch (m_kind) {
        case U_MINUS:
            opt = " - ";
            break;
        case U_NOT:
            opt = " ! ";
            break;
        default:
            throw std::runtime_error("Cannot prettify unary expression because kind is unknown");
    }
    ss << "( " << opt << m_operand->prettify() << " )";
    return ss.str();
}

std::string mini::MUnary::toC() {
    std::stringstream ss;
    std::string opt;
    switch (m_kind) {
        case U_MINUS:
            opt = " - ";
            break;
        case U_NOT:
            opt = " ! ";
            break;
        default:
            throw std::runtime_error("Cannot generate C code for unary expression because kind is unknown");
    }
    ss << "( " << opt << m_operand->toC() << " )";
    return ss.str();
}

int mini::MUnary::getLine() {
    return m_operand->getLine();
}

mini::MUnary::~MUnary() {
    if(m_operand) {
        delete m_operand;
    }
}