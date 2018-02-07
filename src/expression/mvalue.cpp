#include <minilang/mvalue.h>
#include <minilang/mvariable.h>
#include <sstream>

/**********
 * INTEGER
 **********/

mini::TYPE mini::MValue<int>::evalType() {
    return INTEGER;
}
std::string mini::MValue<int>::prettify() {
    return std::to_string(m_value);
}
std::string mini::MValue<int>::toC() {
    return std::to_string(m_value);
}

/**********
 *  FLOAT
 **********/

mini::TYPE mini::MValue<float>::evalType() {
    return FLOAT;
}
std::string mini::MValue<float>::prettify() {
    return std::to_string(m_value);
}
std::string mini::MValue<float>::toC() {
    return std::to_string(m_value);
}

/**********
 * STRING
 **********/

mini::TYPE mini::MValue<char*>::evalType() {
    return STRING;
}
std::string mini::MValue<char*>::prettify() {
    return m_value;
}
std::string mini::MValue<char*>::toC() {
    return m_value;
}

/**********
 * BOOLEAN
 **********/

mini::TYPE mini::MValue<bool>::evalType() {
    return BOOLEAN;
}
std::string mini::MValue<bool>::prettify() {
    return m_value ? "TRUE" : "FALSE";
}
std::string mini::MValue<bool>::toC() {
    return m_value ? "true" : "false";
}

