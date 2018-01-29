#include <minilang/mexpression.h>
#include <minilang/mreport.h>

bool mini::MExpression::isUnary() const {
    if(m_kind == mini::MExpression::KIND::UNDEFINED) {
        throw std::runtime_error("Expression without type cannot be check if it is unary");
    }
    return m_kind == U_MINUS || m_kind == U_NOT;
}

bool mini::MExpression::isAtomic() const {
    switch (m_kind) {
        case U_INTEGER:
        case U_FLOAT:
        case U_IDENTIFIER:
        case U_STRING:
            return true;
    }
    return false;
}

mini::TYPE mini::MExpression::evalType() {
    if(m_kind == mini::MExpression::KIND::UNDEFINED) {
        throw std::runtime_error("Cannot get the type of an undefined epxression");
    }

    mini::TYPE leftType = mini::TYPE::UNDEFINED;
    mini::TYPE rightType = mini::TYPE::UNDEFINED;
    switch (m_kind) {

        /********************
         * UNARY OPERATIONS
         ********************/
        case U_STRING:
            return mini::TYPE::STRING;

        case U_INTEGER:
            return mini::TYPE::INTEGER;

        case U_FLOAT:
            return mini::TYPE::FLOAT;

        case U_BOOLEAN:
            return mini::TYPE::BOOLEAN;

        case U_MINUS:
            leftType = m_left->evalType();
            if(leftType != mini::TYPE::INTEGER && leftType != mini::TYPE::FLOAT) {
                mini::error_exit("unary operator - expects the operand to be an integer or float");
            }
            return leftType;

        case U_NOT:
            if(m_left->evalType() != mini::TYPE::BOOLEAN) {
                mini::error_exit("unary operator ! expects the operand to be a boolean");
            }
            return mini::TYPE::BOOLEAN;

        case U_IDENTIFIER:
            // FIXME get type of the identifier
            return mini::TYPE::INTEGER;

        /********************
         * BINARY OPERATIONS
         ********************/

        case B_AND:
        case B_OR:
            if(m_left->evalType() != TYPE::BOOLEAN || m_left->evalType() != TYPE::BOOLEAN) {
                mini::error_exit(m_operator + " operator expects operators to be boolean");
            }
            return mini::TYPE::BOOLEAN;

        case B_DIVIDE:
        case B_MINUS:
            leftType = m_left->evalType();
            rightType = m_right->evalType();
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else {
                mini::error_exit(m_operator + " expects operands to be integers or floats");
            }

        case B_TIMES:
            leftType = m_left->evalType();
            rightType = m_right->evalType();
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::STRING
                      || leftType == mini::TYPE::STRING && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::FLOAT;
            } else {
                mini::error_exit(m_operator + " expects operands to be integers, floats, or an integer and a string");
            }

        case B_PLUS:
            leftType = m_left->evalType();
            rightType = m_right->evalType();
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else if(leftType == mini::TYPE::STRING && rightType == mini::TYPE::STRING) {
                return mini::TYPE::STRING;
            } else {
                mini::error_exit(m_operator + " expects operands to be integers or floats");
            }

        case B_IS_EQUAL:
        case B_IS_NOT_EQUAL:
            leftType = m_left->evalType();
            rightType = m_right->evalType();
            if(leftType != rightType) {
                mini::error_exit(m_operator + " expects both operand to be of the same type");
            }
            return mini::TYPE::BOOLEAN;

        default:
            throw std::runtime_error("Unrecognized type while evaluating the type of the expression");
    }
}
