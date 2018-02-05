#pragma once

#include <minilang/mscope.h>

namespace mini {
    class MGlobal : public MScope {
    private:
        // Disable constructor
        MGlobal(){}
    public:
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
    };
}
