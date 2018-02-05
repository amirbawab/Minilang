#pragma once

#include <minilang/mstatement.h>
#include <vector>

namespace mini {
    class MScope {
    protected:

        // Keep track of nested scopes
        std::vector<mini::MScope*> m_scopes;

        // While loop statements
        std::vector<mini::MStatement*> m_statements;
    };
}
