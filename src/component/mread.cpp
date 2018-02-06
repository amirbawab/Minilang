#include <minilang/mread.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MRead::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "read " << m_identifier->getName() << ";";
    return ss.str();
}

void mini::MRead::typeCheck() {
    m_identifier->typeCheck();
}

std::string mini::MRead::toC(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "scanf (" << m_identifier->getName() << " );";
    return ss.str();
}
