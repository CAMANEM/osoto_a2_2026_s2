#ifndef SIMULATION_METRICS_HPP
#define SIMULATION_METRICS_HPP

#include <string>

/**
 * @brief Agrupa las métricas preliminares recolectadas por cada esquema de
 *        ejecución durante la Demostración 2.
 *
 * En esta etapa del proyecto solo se exige una medición funcional básica
 * (tiempo y cantidad de hilos); el análisis estadístico riguroso (200
 * ejecuciones, intervalos de confianza, boxplots) corresponde a la entrega
 * final y no forma parte de esta estructura.
 *
 * 
 */
struct SimulationMetrics {
    /** Nombre descriptivo del esquema de ejecución evaluado. */
    std::string schemeName;

    /** Cantidad de hilos (reales o virtuales) usados en la ejecución. */
    unsigned int threadsUsed;

    /** Tiempo total de ejecución en milisegundos. */
    double elapsedMilliseconds;

    /** Cantidad de boids efectivamente actualizados (puede ser parcial). */
    long long boidsProcessed;
};

#endif // SIMULATION_METRICS_HPP
