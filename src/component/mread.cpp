#include <minilang/mread.h>
#include <minilang/mutils.h>
#include <sstream>

std::string mini::MRead::prettify(int indent) {
    std::stringstream ss;
    // FIXME
    ss << mini::utils::indent(indent) << "scanf (" << m_identifier->getName() << ");"<< std::endl;
    return ss.str();
}