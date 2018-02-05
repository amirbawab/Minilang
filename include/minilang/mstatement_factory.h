#pragma once

#include <minilang/mwhile.h>
#include <minilang/mif.h>
#include <minilang/midentifier.h>
#include <minilang/mprint.h>
#include <minilang/mread.h>
#include <minilang/melse.h>

namespace mini {
    class MStatementFactory {
    public:

        /**
         * Create while statement
         * @param condition
         * @return pointer to a while statement
         */
        static mini::MWhile* createWhile(mini::MExpression* condition);

        /**
         * Create if statement
         * @param condition
         * @return pointer to an if statement
         */
        static mini::MIf* createIf(mini::MExpression* condition);

        /**
         * Create else statement
         * @return pointer to an else statement
         */
        static mini::MElse* createElse();

        /**
         * Create identifier
         * @param expression
         * @return pointer an identifier
         */
        static mini::MIdentifier* createIdentifier(mini::MExpression* expression);

        /**
         * Create print expression
         * @param expression
         * @return pointer to a print statement
         */
        static mini::MPrint* createPrint(mini::MExpression* expression);

        /**
         * Create a read statement
         * @param identifier
         * @return pointer to a read statement
         */
        static mini::MRead* createRead(mini::MIdentifier* identifier);
    };
}