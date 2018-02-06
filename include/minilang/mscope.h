#pragma once

#include <minilang/mstatement.h>
#include <vector>

namespace mini {
    class MScope {
    protected:

        // While loop statements
        std::vector<mini::MStatement*>* m_statements = nullptr;
    public:

        /**
         * Set statement to this scope
         * @param statements
         */
        void setStatements(std::vector<mini::MStatement*>* statements) {m_statements = statements;};

        /**
         * Get statements
         * @return vector of statements
         */
        std::vector<mini::MStatement*>* getStatements() const { return m_statements; }

        /**
         * Prettify code
         * @param indent
         * @return pretty code
         */
        virtual std::string prettify(int indent) = 0;

        /**
         * Generate C code
         * @param indent
         * @return c code
         */
        virtual std::string toC(int indent) = 0;
    };
}
