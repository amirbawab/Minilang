#include <minilang/mbinary.h>
#include <minilang/mreport.h>
#include <sstream>

mini::TYPE mini::MBinary::evalType() {
    if(m_kind == KIND::UNDEFINED) {
        throw std::runtime_error("Cannot get the type of an undefined binary expression");
    }

    mini::TYPE leftType = m_left->evalType();
    mini::TYPE rightType = m_right->evalType();
    switch (m_kind) {
        case B_AND:
        case B_OR:
            if(leftType != TYPE::BOOLEAN || rightType != TYPE::BOOLEAN) {
                mini::error_exit(m_operator + " operator expects operators to be boolean");
            }
            return mini::TYPE::BOOLEAN;

        case B_DIVIDE:
        case B_MINUS:
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else {
                mini::error_exit(m_operator + " expects operands to be integers or floats");
            }

        case B_TIMES:
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
            if(leftType != rightType) {
                mini::error_exit(m_operator + " expects both operand to be of the same type");
            }
            return mini::TYPE::BOOLEAN;

        default:
            throw std::runtime_error("Unrecognized type while evaluating the type of the expression");
    }
}

std::string mini::MBinary::prettify() {
    std::stringstream ss;
    std::string opt;
    switch (m_kind) {
        case B_MINUS:
            opt = " - ";
            break;
        case B_PLUS:
            opt = " + ";
            break;
        case B_TIMES:
            opt = " * ";
            break;
        case B_DIVIDE:
            opt = " / ";
            break;
        case B_IS_EQUAL:
            opt = " == ";
            break;
        case B_IS_NOT_EQUAL:
            opt = " != ";
            break;
        case B_AND:
            opt =" && ";
            break;
        case B_OR:
            opt = " || ";
            break;
        default:
            throw std::runtime_error("Cannot prettify binary expression because kind is unknown");
    }
    ss << "( " << m_left->prettify() << opt << m_right->prettify() << " )";
    return ss.str();
}