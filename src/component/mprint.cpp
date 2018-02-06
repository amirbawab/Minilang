#include <minilang/mprint.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MPrint::prettify(int indent) {
    std::stringstream ss;
    // FIXME
    ss << mini::utils::indent(indent) << "printf ( " << m_expression->prettify() << " );" << std::endl;
    return ss.str();
}