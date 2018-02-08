#pragma once

#include <minilang/mexpression.h>
#include <minilang/midentifier.h>

namespace mini {
    template<class T> class MValue{};

    template <>
    class MValue<int> : public MExpression {
    public:
        int m_value;
        int m_line;
        MValue(int value, int line) : m_value(value), m_line(line){ m_kind = mini::MExpression::KIND::VALUE; }
        mini::TYPE evalType();
        std::string prettify();
        std::string toC();
        int getLine() { return m_line; }
    };

    template <>
    class MValue<bool> : public MExpression {
    public:
        bool m_value;
        int m_line;
        MValue(bool value, int line) : m_value(value), m_line(line){m_kind = mini::MExpression::KIND::VALUE;}
        mini::TYPE evalType();
        std::string prettify();
        std::string toC();
        int getLine() { return m_line; }
    };

    template <>
    class MValue<char*> : public MExpression {
    public:
        char* m_value;
        int m_line;
        MValue(char* value, int line) : m_value(value), m_line(line){m_kind = mini::MExpression::KIND::VALUE;}
        mini::TYPE evalType();
        std::string prettify();
        std::string toC();
        int getLine() { return m_line; }
    };

    template <>
    class MValue<float> : public MExpression {
    public:
        float m_value;
        int m_line;
        MValue(float value, int line) : m_value(value), m_line(line){m_kind = mini::MExpression::KIND::VALUE;}
        mini::TYPE evalType();
        std::string prettify();
        std::string toC();
        int getLine() { return m_line; }
    };
}
