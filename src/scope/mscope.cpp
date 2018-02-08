#include <minilang/mscope.h>

mini::MScope::~MScope() {
    if(m_statements) {
        for(mini::MStatement* statement : *m_statements) {
            delete statement;
        }
    }
    delete m_statements;
}