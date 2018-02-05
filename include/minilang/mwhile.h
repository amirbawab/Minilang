#pragma once

#include <minilang/mscope.h>
#include <minilang/mexpression.h>
#include <minilang/mstatement.h>
#include <vector>

class MWhile : public mini::MScope, public mini::MStatement {
private:

    // While loop condition
    mini::MExpression* m_condition = nullptr;
};