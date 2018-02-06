#include <minilang/mread.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MRead::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "read " << m_identifier->getName() << ";";
    return ss.str();
}