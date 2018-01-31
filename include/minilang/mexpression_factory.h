#include <minilang/mbinary.h>

namespace mini {
    class MExpressionFactory {
    public:

        /**
         * Create a plus binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createPlus(mini::MExpression* left, mini::MExpression* right);

        /**
         * Create a minus binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createMinus(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create a times binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createTimes(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create a divide binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createDivide(mini::MExpression* left, mini::MExpression* right);

        /**
         * Create an is equal binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createIsEqual(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create an is not equal binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createIsNotEqual(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create an AND binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createAND(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create an OR binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createOR(mini::MExpression* left, mini::MExpression* right);
    };

}
