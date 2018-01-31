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
         * Create a divice binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createDivide(mini::MExpression* left, mini::MExpression* right);
    };

}
