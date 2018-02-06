#include <minilang/mread.h>
#include <minilang/mutils.h>
#include <iostream>

std::string mini::MRead::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "read " << m_identifier->getName() << ";";
    return ss.str();
}

void mini::MRead::typeCheck() {
    m_identifier->evalType();
}

std::string mini::MRead::toC(int indent) {
    std::stringstream ss;
    mini::TYPE idType = m_identifier->evalType();
    ss << mini::utils::indent(indent) << "scanf(\"" << mini::utils::toCStringFormat(idType) << "\", "
       << m_identifier->getName() << ");";
    return ss.str();
}
