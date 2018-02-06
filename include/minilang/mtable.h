#pragma once

#include <minilang/mvariable.h>
#include <map>

namespace mini {
    class MTable {
    private:

        // Registered variables
        std::map<std::string, mini::MVariable*> m_variableMap;
    public:

        /**
         * Register a new variable
         * @param variable
         */
        void registerVariable(mini::MVariable* variable);

        /**
         * Get registered variable by name
         * @param name
         * @return variable | nullptr
         */
        mini::MVariable* getVariable(std::string name);

        /**
         * Generate symbol table
         * @return symbol table
         */
        std::string str();
    };
}