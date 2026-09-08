#include "FineGrainedScheme.hpp"
#include "SteeringContext.hpp"
#include "Timer.hpp"

#include <algorithm>
#include <vector>

FineGrainedScheme::FineGrainedScheme(int partialBoidCount)
    : partialBoidCount_(partialBoidCount) {
}

SimulationMetrics FineGrainedScheme::simulateStep(Flock& flock, const FlockingConfig& config) {
    Timer timer;
    timer.start();

    const int boidsToProcess = std::min(partialBoidCount_, flock.getBoidCount());

    std::vector<SteeringContext> contexts;
    contexts.reserve(boidsToProcess);
    for (int i = 0; i < boidsToProcess; ++i) {
        contexts.emplace_back(i, flock, config);
    }

    // Planificación round-robin: cada contexto recibe un único ciclo (un
    // vecino candidato examinado) por turno, sin importar si otro contexto
    // ya "hizo stall" (le quedan muchos más candidatos). El ciclo continúa
    // hasta que todos los contextos hayan terminado de examinar a todos
    // los demás boids.
    bool anyContextActive = true;
    while (anyContextActive) {
        anyContextActive = false;
        for (auto& context : contexts) {
            if (!context.isFinished()) {
                context.stepOnce();
                if (!context.isFinished()) {
                    anyContextActive = true;
                }
            }
        }
    }

    // Única vez que se toca el enjambre: se aplican las integraciones ya
    // finalizadas de cada contexto.
    for (auto& context : contexts) {
        flock.applyIntegration(context.getBoidIndex(), context.computeFinalSteering(), config);
    }

    const double elapsedMs = timer.stopAndGetMilliseconds();
    return SimulationMetrics{getSchemeName(), static_cast<unsigned int>(boidsToProcess), elapsedMs,
                              boidsToProcess};
}

std::string FineGrainedScheme::getSchemeName() const {
    return "Grano Fino (round-robin por vecino, parcial)";
}
