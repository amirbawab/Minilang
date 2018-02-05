#pragma once

#include <vector>

class MScope {
protected:

    // Keep track of nested scopes
    std::vector<MScope*> m_scopes;
};