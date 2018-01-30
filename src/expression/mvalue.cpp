#include <minilang/mvalue.h>

template<class T>
mini::TYPE mini::MValue<T>::evalType() {
    switch (m_kind) {
        case V_INTEGER:
            return TYPE::INTEGER;
        case V_FLOAT:
            return TYPE::FLOAT;
        case V_STRING:
            return TYPE::STRING;
        case V_BOOLEAN:
            return TYPE::BOOLEAN;
        case V_IDENTIFIER:
            // FIXME get type of the identifier
            return mini::TYPE::INTEGER;
    }
    return TYPE::UNDEFINED;
}
