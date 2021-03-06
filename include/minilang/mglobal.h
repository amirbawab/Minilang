#pragma once

#include <minilang/mscope.h>
#include <minilang/mvariable.h>
#include <minilang/mtable.h>

namespace mini {
    class MGlobal : public MScope {
    private:
        // Disable constructor
        MGlobal(){}

        // Variables
        std::vector<mini::MVariable*>* m_variables = nullptr;

        // Symbol table
        mini::MTable m_table;
    public:
        ~MGlobal();

        /**
         * Get single instance of this class
         * @return pointer to a singleton instance
         */
        static MGlobal* getInstance() {
            static MGlobal* instance(new MGlobal());
            return instance;
        }

        // Delete constructor and operator
        MGlobal(MGlobal const&) = delete;
        void operator=(MGlobal const&) = delete;

        /**
         * Set variables
         * @param variables
         */
        void setVariables(std::vector<mini::MVariable*>* variables) {m_variables = variables;}

        /**
         * Get variables
         * @return variables
         */
        std::vector<mini::MVariable*>* getVariables() {return m_variables;}

        /**
         * @see mini::MScope::prettify
         */
        std::string prettify(int indent);

        /**
         * @see mini::MScope::toC
         */
        std::string toC(int indent);

        /**
         * Find variable
         * @param name
         * @return variable | nullptr
         */
        mini::MVariable* findVariable(std::string name);

        /**
         * Type check
         */
        void typeCheck();

        /**
         * Get symbol table
         * @return symbol table
         */
        std::string toSymbolTable();
    };
}
