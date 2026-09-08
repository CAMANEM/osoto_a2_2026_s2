#ifndef FLOCKING_CONFIG_HPP
#define FLOCKING_CONFIG_HPP

/**
 * @brief Encapsula los parámetros que gobiernan el comportamiento del
 *        enjambre (parvada) y el mundo donde se simula.
 *
 * Estas son las variables críticas identificadas para la paralelización:
 * el radio de percepción determina cuántos vecinos evalúa cada boid (y por
 * lo tanto cuánto trabajo real hace), mientras que la cantidad de boids
 * determina el volumen total de pares a evaluar en el peor caso.
 *
 * 
 */
class FlockingConfig {
public:
    /**
     * @brief Construye la configuración de la simulación.
     * @param boidCount Cantidad de agentes (boids) en el enjambre.
     * @param worldWidth Ancho del mundo (también usado como ancho del
     *        lienzo de exportación, para simplificar el mapeo).
     * @param worldHeight Alto del mundo.
     * @param perceptionRadius Radio dentro del cual un boid considera a
     *        otro como vecino para alineación y cohesión.
     * @param separationRadius Radio (más pequeño que perceptionRadius)
     *        dentro del cual se aplica la fuerza de separación.
     * @param maxSpeed Rapidez máxima permitida para un boid.
     * @param maxForce Magnitud máxima de la fuerza de dirección aplicada
     *        por paso de simulación.
     * @param separationWeight Peso de la regla de separación.
     * @param alignmentWeight Peso de la regla de alineación.
     * @param cohesionWeight Peso de la regla de cohesión.
     * @param deltaTime Paso de tiempo de integración por actualización.
     */
    FlockingConfig(int boidCount, double worldWidth, double worldHeight,
                   double perceptionRadius, double separationRadius,
                   double maxSpeed, double maxForce,
                   double separationWeight, double alignmentWeight, double cohesionWeight,
                   double deltaTime);

    int getBoidCount() const;
    double getWorldWidth() const;
    double getWorldHeight() const;
    double getPerceptionRadius() const;
    double getSeparationRadius() const;
    double getMaxSpeed() const;
    double getMaxForce() const;
    double getSeparationWeight() const;
    double getAlignmentWeight() const;
    double getCohesionWeight() const;
    double getDeltaTime() const;

private:
    int boidCount_;
    double worldWidth_;
    double worldHeight_;
    double perceptionRadius_;
    double separationRadius_;
    double maxSpeed_;
    double maxForce_;
    double separationWeight_;
    double alignmentWeight_;
    double cohesionWeight_;
    double deltaTime_;
};

#endif // FLOCKING_CONFIG_HPP
