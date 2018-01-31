#include <minilang/mbinary.h>
#include <minilang/munary.h>

namespace mini {
    class MExpressionFactory {
    public:

        /**
         * Create a plus binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBPlus(mini::MExpression* left, mini::MExpression* right);

        /**
         * Create a minus binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBMinus(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create a times binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBTimes(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create a divide binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBDivide(mini::MExpression* left, mini::MExpression* right);

        /**
         * Create an is equal binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBIsEqual(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create an is not equal binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBIsNotEqual(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create an AND binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBAND(mini::MExpression* left, mini::MExpression* right);
        /**
         * Create an OR binary expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MBinary* createBOR(mini::MExpression* left, mini::MExpression* right);

        /**
         * Create a unary minus expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MUnary* createUMinus(mini::MExpression* operand);

        /**
         * Create a unary not expression
         * @param left
         * @param right
         * @return pointer to an expression
         */
        static mini::MUnary* createUNot(mini::MExpression* operand);
    };

}
