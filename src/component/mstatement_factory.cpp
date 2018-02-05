#include <minilang/mstatement_factory.h>

mini::MWhile* mini::MStatement_factory::createWhile(mini::MExpression *condition) {
    return new mini::MWhile(condition);
}

mini::MIf* mini::MStatement_factory::createIf(mini::MExpression *condition) {
    return new mini::MIf(condition);
}

mini::MIdentifier* mini::MStatement_factory::createIdentifier(mini::MExpression *expression) {
    mini::MIdentifier* identifier = new mini::MIdentifier();
    identifier->setExpression(expression);
}

mini::MPrint* mini::MStatement_factory::createPrint(mini::MExpression *expression) {
    return new mini::MPrint(expression);
}

mini::MRead* mini::MStatement_factory::createRead(mini::MIdentifier *identifier) {
    return new mini::MRead(identifier);
}