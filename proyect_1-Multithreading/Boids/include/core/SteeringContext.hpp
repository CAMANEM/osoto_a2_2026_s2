#ifndef STEERING_CONTEXT_HPP
#define STEERING_CONTEXT_HPP

#include "core/Flock.hpp"
#include "core/FlockingConfig.hpp"
#include "core/Vector2D.hpp"

/**
 * @brief Representa el estado de ejecución de "un hilo virtual" que
 *        calcula la fuerza de dirección de un único boid, evaluando un
 *        vecino candidato a la vez.
 *
 * Esta clase existe exclusivamente para simular el modelo de multihilo de
 * grano fino (ver FineGrainedScheme), tal como lo exige el enunciado:
 * "planificación cooperativa o simulación de ejecución por ciclos o
 * cuantums, donde el cambio de hilo ocurre en cada ciclo (quantum mínimo)
 * en forma round-robin, independientemente de si el hilo actual ha
 * sufrido un stall". Aquí, un "ciclo" equivale a examinar un único vecino
 * candidato: el contexto evalúa la distancia, acumula su contribución si
 * corresponde, y cede el turno sin importar que a otros contextos les
 * queden muchos más candidatos por examinar (su "stall").
 *
 * 
 */
class SteeringContext {
public:
    /**
     * @brief Crea un contexto de ejecución para un boid específico.
     * @param boidIndex Índice del boid cuya fuerza de dirección calculará
     *        este contexto.
     * @param flock Enjambre completo (de solo lectura durante el cálculo).
     * @param config Configuración de la simulación.
     */
    SteeringContext(int boidIndex, const Flock& flock, const FlockingConfig& config);

    /**
     * @brief Ejecuta un único ciclo: examina el siguiente vecino candidato
     *        pendiente y acumula su contribución si está dentro del radio
     *        de percepción (o de separación).
     * @return true si el contexto sigue activo (le quedan candidatos por
     *         examinar), false si ya examinó a todos los demás boids.
     */
    bool stepOnce();

    /** @return true si el contexto ya terminó de examinar candidatos. */
    bool isFinished() const;

    /**
     * @brief Combina las sumas parciales acumuladas durante el round-robin
     *        en la fuerza de dirección final del boid.
     * @return Fuerza de dirección combinada, ya limitada a maxForce.
     */
    Vector2D computeFinalSteering() const;

    /** @return Índice del boid asociado a este contexto. */
    int getBoidIndex() const;

private:
    int boidIndex_;
    const Flock* flock_;
    const FlockingConfig* config_;
    int candidateCursor_;
    int neighborCount_;
    Vector2D separationSum_;
    Vector2D velocitySum_;
    Vector2D positionSum_;
    bool finished_;

    /** @brief Avanza candidateCursor_ saltando el propio índice del boid. */
    void skipSelfIndex();
};

#endif // STEERING_CONTEXT_HPP
