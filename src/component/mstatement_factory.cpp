#include <minilang/mstatement_factory.h>

mini::MWhile* mini::MStatementFactory::createWhile(mini::MExpression *condition) {
    return new mini::MWhile(condition);
}

mini::MIf* mini::MStatementFactory::createIf(mini::MExpression *condition) {
    return new mini::MIf(condition);
}

mini::MElse* mini::MStatementFactory::createElse() {
    return new mini::MElse();
}

mini::MIdentifier* mini::MStatementFactory::createIdentifier(mini::MExpression *expression) {
    mini::MIdentifier* identifier = new mini::MIdentifier();
    identifier->setExpression(expression);
}

mini::MPrint* mini::MStatementFactory::createPrint(mini::MExpression *expression) {
    return new mini::MPrint(expression);
}

mini::MRead* mini::MStatementFactory::createRead(mini::MIdentifier* identifier) {
    return new mini::MRead(identifier);
}