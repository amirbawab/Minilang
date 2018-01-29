#include <minilang/mexpression.h>

bool mini::MExpression::isUnary() const {
    if(m_type == mini::MExpression::TYPE::UNDEFINED) {
        throw std::runtime_error("Expression without type cannot be check if it is unary");
    }
    return m_type == U_MINUS || m_type == U_NOT;
}

bool mini::MExpression::isUndefined() const {
    return m_type == mini::MExpression::UNDEFINED;
}