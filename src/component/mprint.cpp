#include <minilang/mprint.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MPrint::prettify(int indent) {
    std::stringstream ss;
    ss << mini::utils::indent(indent) << "print " << m_expression->prettify() << ";";
    return ss.str();
}