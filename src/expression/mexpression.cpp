#include <minilang/mexpression.h>
#include <minilang/mreport.h>

bool mini::MExpression::isUnary() const {
    if(m_type == mini::MExpression::TYPE::UNDEFINED) {
        throw std::runtime_error("Expression without type cannot be check if it is unary");
    }
    return m_type == U_MINUS || m_type == U_NOT;
}

bool mini::MExpression::isAtomic() const {
    switch (m_type) {
        U_INTEGER:
        U_FLOAT:
        U_IDENTIFIER:
        U_STRING:
            return true;
    }
    return false;
}

mini::TYPE mini::MExpression::getType() {
    if(m_kind == mini::MExpression::KIND::UNDEFINED) {
        throw std::runtime_error("Cannot get the type of an undefined epxression");
    }

    switch (m_kind) {

        /********************
         * UNARY OPERATIONS
         ********************/
        case mini::MExpression::U_STRING:
            return mini::TYPE::STRING;

        case mini::MExpression::U_INTEGER:
            return mini::TYPE::INTEGER;

        case mini::MExpression::U_FLOAT:
            return mini::TYPE::FLOAT;

        case mini::MExpression::U_BOOLEAN:
            return mini::TYPE::BOOLEAN;

        case mini::MExpression::U_MINUS:
            mini::TYPE leftType = m_left->evalType();
            if(leftType != mini::TYPE::INTEGER || leftType != mini::TYPE::FLOAT) {
                mini::error_exit("unary operator - expects the operand to be an integer or float");
            }
            return leftType;

        case mini::MExpression::U_NOT:
            if(m_left->evalType() != mini::TYPE::BOOLEAN) {
                mini::error_exit("unary operator ! expects the operand to be a boolean");
            }
            return mini::TYPE::BOOLEAN;

        case mini::MExpression::U_IDENTIFIER:
            // TODO get type of the identifier
            return 0;

        /********************
         * BINARY OPERATIONS
         ********************/

        case mini::MExpression::B_AND:
        case mini::MExpression::B_OR:
            if(m_left->evalType() != TYPE::BOOLEAN || m_left->evalType() != TYPE::BOOLEAN) {
                mini::error_exit(m_operator + " operator expects operators to be boolean");
            }
            return mini::TYPE::BOOLEAN;

        case mini::MExpression::B_DIVIDE:
        case mini::MExpression::B_MINUS:
            mini::TYPE leftType = m_left->evalType();
            mini::TYPE rightType = m_right->evalType();
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else {
                mini::error_exit(m_operator + " expects operands to be integers or floats");
            }

        case mini::MExpression::B_TIMES:
            mini::TYPE leftType = m_left->evalType();
            mini::TYPE rightType = m_right->evalType();
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

        case mini::MExpression::B_PLUS:
            mini::TYPE leftType = m_left->evalType();
            mini::TYPE rightType = m_right->evalType();
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else if(leftType == mini::TYPE::STRING && leftType == mini::TYPE::STRING) {
                return mini::TYPE::STRING;
            } else {
                mini::error_exit(m_operator + " expects operands to be integers or floats");
            }

        case mini::MExpression::B_IS_EQUAL:
        case mini::MExpression::B_IS_NOT_EQUAL:
            mini::TYPE leftType = m_left->evalType();
            mini::TYPE rightType = m_right->evalType();
            if(leftType != rightType) {
                mini::error_exit(m_operator + " expects both operand to be of the same type");
            }

        default:
            throw std::runtime_error("Unrecognized type while evaluating the type of the expression");
    }
    return mini::TYPE::UNDEFINED;
}
