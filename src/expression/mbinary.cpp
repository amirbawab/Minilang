#include <minilang/mbinary.h>
#include <minilang/mreport.h>
#include <sstream>
#include <iostream>

mini::TYPE mini::MBinary::evalType() {
    if(m_kind == KIND::UNDEFINED) {
        throw std::runtime_error("Cannot get the type of an undefined binary expression");
    }

    mini::TYPE leftType = m_left->evalType();
    mini::TYPE rightType = m_right->evalType();
    switch (m_kind) {
        case B_AND:
        case B_OR:
            if((leftType != TYPE::BOOLEAN && leftType != TYPE::INTEGER)
               || (rightType != TYPE::BOOLEAN && rightType != TYPE::INTEGER)) {
                mini::report::error_exit(
                        getOperator() + " operator expects operands to be boolean or integers", getLine());
            }
            return mini::TYPE::BOOLEAN;

        case B_DIVIDE:
        case B_MINUS:
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT
                      || leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else {
                mini::report::error_exit(getOperator() + " expects operands to be integers or floats", getLine());
            }

        case B_TIMES:
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT
                      || leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::STRING
                      || leftType == mini::TYPE::STRING && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::STRING;
            } else {
                mini::report::error_exit(
                        getOperator() + " expects operands to be integers, floats, or an integer and a string", getLine());
            }

        case B_PLUS:
            if(leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::INTEGER) {
                return mini::TYPE::INTEGER;
            } else if(leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::INTEGER
                      || leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::FLOAT
                      || leftType == mini::TYPE::FLOAT && rightType == mini::TYPE::FLOAT) {
                return mini::TYPE::FLOAT;
            } else if(leftType == mini::TYPE::STRING && rightType == mini::TYPE::STRING) {
                return mini::TYPE::STRING;
            } else {
                mini::report::error_exit(getOperator() + " expects operands to be integers or floats", getLine());
            }

        case B_IS_EQUAL:
        case B_IS_NOT_EQUAL:
            if(leftType != rightType) {
                mini::report::error_exit(getOperator() + " expects both operand to be of the same type", getLine());
            }
            return mini::TYPE::BOOLEAN;

        default:
            throw std::runtime_error("Unrecognized type while evaluating the type of the expression");
    }
}

std::string mini::MBinary::prettify() {
    std::stringstream ss;
    std::string opt = getOperator();
    ss << "( " << m_left->prettify() << " " << opt << " " << m_right->prettify() << " )";
    return ss.str();
}

std::string mini::MBinary::toC() {
    std::stringstream ss;
    std::string opt = getOperator();
    mini::TYPE leftType = m_left->evalType();
    mini::TYPE rightType = m_right->evalType();

    // Handle special cases
    if(m_kind == mini::MExpression::KIND::B_TIMES) {
        if (leftType == mini::TYPE::STRING && rightType == mini::TYPE::INTEGER) {
            ss << "repeatStr(" << m_left->toC() << ", " << m_right->toC() << ")";
        } else if (leftType == mini::TYPE::INTEGER && rightType == mini::TYPE::STRING) {
            ss << "repeatStr(" << m_right->toC() << ", " << m_left->toC() << ")";
        } else {
            ss << "( " << m_left->toC() << " " << opt << " " << m_right->toC() << " )";
        }
    } else if(m_kind == mini::MExpression::KIND::B_PLUS
              && leftType == mini::TYPE::STRING && rightType == mini::TYPE::STRING) {
        ss << "cat(" << m_left->toC() << ", " << m_right->toC() << ")";
    } else {

        // Default case
        ss << "( " << m_left->toC() << " " << opt << " " << m_right->toC() << " )";
    }
    return ss.str();
}

std::string mini::MBinary::getOperator() {
    switch (m_kind) {
        case B_MINUS:
            return "-";
        case B_PLUS:
            return "+";
        case B_TIMES:
            return "*";
        case B_DIVIDE:
            return "/";
        case B_IS_EQUAL:
            return "==";
        case B_IS_NOT_EQUAL:
            return "!=";
        case B_AND:
            return "&&";
        case B_OR:
            return "||";
        default:
            throw std::runtime_error("Cannot prettify binary expression because kind is unknown");
    }
}

int mini::MBinary::getLine() {
    return m_left->getLine();
}

mini::MBinary::~MBinary() {
    if(m_left) {
        delete m_left;
    }
    if(m_right) {
        delete m_right;
    }
}