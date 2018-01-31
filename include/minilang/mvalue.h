#pragma once

#include <minilang/mexpression.h>

namespace mini {
    template<class T> class MValue{};

    template <>
    class MValue<int> : public MExpression {
    public:
        int m_value;
        MValue(int value) : m_value(value){}
        mini::TYPE evalType() { return INTEGER; }
    };

    template <>
    class MValue<bool> : public MExpression {
    public:
        bool m_value;
        MValue(bool value) : m_value(value){}
        mini::TYPE evalType() { return BOOLEAN; }
    };

    template <>
    class MValue<char*> : public MExpression {
    public:
        char* m_value;
        MValue(char* value) : m_value(value){}
        mini::TYPE evalType() { return STRING; }
    };

    template <>
    class MValue<float> : public MExpression {
    public:
        float m_value;
        MValue(float value) : m_value(value){}
        mini::TYPE evalType() { return FLOAT; }
    };

//    FIXME Identifier: get type from identifier
//    template <>
//    class MValue<int> : public MExpression {
//    public:
//        int m_value;
//        mini::TYPE evalType() { return INTEGER; }
//    };
}
