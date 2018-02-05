#include <minilang/mscope.h>

void mini::MScope::addStatement(mini::MStatement *statement) {
    m_statements.push_back(statement);
}