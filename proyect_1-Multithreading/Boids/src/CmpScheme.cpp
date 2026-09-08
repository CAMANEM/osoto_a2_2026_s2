#include "CmpScheme.hpp"

#include <algorithm>
#include <thread>

unsigned int CmpScheme::computeThreadCount(const Flock& /*flock*/) const {
    return std::max(1u, std::thread::hardware_concurrency());
}

std::string CmpScheme::getSchemeName() const {
    return "CMP (multiprocesamiento de chip)";
}
