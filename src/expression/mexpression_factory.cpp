#include <minilang/mexpression_factory.h>

mini::MBinary* mini::MExpressionFactory::createBPlus(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_PLUS);
    return expression;
}

mini::MBinary* mini::MExpressionFactory::createBMinus(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_MINUS);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createBTimes(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_TIMES);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createBDivide(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_DIVIDE);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createBIsEqual(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_IS_EQUAL);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createBIsNotEqual(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_IS_NOT_EQUAL);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createBAND(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_AND);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createBOR(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_OR);
    return expression;
}
mini::MUnary* mini::MExpressionFactory::createUMinus(mini::MExpression *operand) {
    mini::MUnary* expression = new mini::MUnary();
    expression->setOperand(operand);
    expression->setKind(mini::MExpression::KIND::U_MINUS);
    return expression;
}
mini::MUnary* mini::MExpressionFactory::createUNot(mini::MExpression *operand) {
    mini::MUnary* expression = new mini::MUnary();
    expression->setOperand(operand);
    expression->setKind(mini::MExpression::KIND::U_NOT);
    return expression;
}
