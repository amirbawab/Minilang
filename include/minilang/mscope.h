#pragma once

#include <minilang/mstatement.h>
#include <vector>

namespace mini {
    class MScope {
    protected:

        // Keep track of nested scopes
        std::vector<mini::MScope*> m_scopes;

        // While loop statements
        std::vector<mini::MStatement*>* m_statements;
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
    };
}
