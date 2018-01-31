#include <minilang/mexpression_factory.h>

mini::MBinary* mini::MExpressionFactory::createPlus(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_PLUS);
    return expression;
}

mini::MBinary* mini::MExpressionFactory::createMinus(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_MINUS);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createTimes(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_TIMES);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createDivide(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_DIVIDE);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createIsEqual(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_IS_EQUAL);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createIsNotEqual(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_IS_NOT_EQUAL);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createAND(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_AND);
    return expression;
}
mini::MBinary* mini::MExpressionFactory::createOR(mini::MExpression *left, mini::MExpression *right) {
    mini::MBinary* expression = new mini::MBinary();
    expression->setLeft(left);
    expression->setRight(right);
    expression->setKind(mini::MExpression::KIND::B_OR);
    return expression;
}
