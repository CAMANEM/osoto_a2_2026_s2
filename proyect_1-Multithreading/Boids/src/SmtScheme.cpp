#include "SmtScheme.hpp"

#include <algorithm>
#include <thread>

SmtScheme::SmtScheme(unsigned int oversubscriptionFactor)
    : oversubscriptionFactor_(oversubscriptionFactor) {
}

unsigned int SmtScheme::computeThreadCount(const Flock& /*flock*/) const {
    const unsigned int logicalCores = std::max(1u, std::thread::hardware_concurrency());
    return logicalCores * oversubscriptionFactor_;
}

std::string SmtScheme::getSchemeName() const {
    return "SMT (sobre-suscripcion de hilos logicos)";
}
