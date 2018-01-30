#include <minilang/munary.h>
#include <minilang/mreport.h>

mini::TYPE mini::MUnary::evalType() {
    if(m_kind == KIND::UNDEFINED) {
        throw std::runtime_error("Cannot get the type of an undefined binary expression");
    }

    TYPE operandType = m_operand->evalType();
    switch (m_kind) {
        case U_MINUS:
            if(operandType != mini::TYPE::INTEGER && operandType != mini::TYPE::FLOAT) {
                mini::error_exit("unary operator - expects the operand to be an integer or float");
            }
            return operandType;

        case U_NOT:
            if(operandType != mini::TYPE::BOOLEAN) {
                mini::error_exit("unary operator ! expects the operand to be a boolean");
            }
            return mini::TYPE::BOOLEAN;
    }
}