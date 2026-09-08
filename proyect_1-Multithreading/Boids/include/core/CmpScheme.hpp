#ifndef CMP_SCHEME_HPP
#define CMP_SCHEME_HPP

#include "core/ThreadedScheme.hpp"

/**
 * @brief Multiprocesamiento de chip (CMP): paralelismo real sobre múltiples
 *        núcleos físicos.
 *
 * A diferencia de SmtScheme (que sobre-suscribe hilos deliberadamente para
 * competir por los mismos núcleos), este esquema lanza exactamente un hilo
 * por núcleo lógico reportado por el sistema operativo
 * (std::thread::hardware_concurrency()).
 *
 * 
 */
class CmpScheme : public ThreadedScheme {
public:
    std::string getSchemeName() const override;

protected:
    unsigned int computeThreadCount(const Flock& flock) const override;
};

#endif // CMP_SCHEME_HPP
