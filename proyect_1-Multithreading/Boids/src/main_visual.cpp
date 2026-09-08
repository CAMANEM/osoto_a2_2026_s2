#include <cstdlib>
#include <iostream>

#include "core/Flock.hpp"
#include "core/FlockingConfig.hpp"
#include "core/SequentialScheme.hpp"
#include "visual/Renderer.hpp"

int main() {
    const int boidCount = 150;
    const int windowWidth = 900;
    const int windowHeight = 700;

    const FlockingConfig config(boidCount, static_cast<double>(windowWidth),
                                 static_cast<double>(windowHeight),
                                 /*perceptionRadius=*/50.0, /*separationRadius=*/20.0,
                                 /*maxSpeed=*/2.6, /*maxForce=*/0.18,
                                 /*separationWeight=*/1.0, /*alignmentWeight=*/1.4,
                                 /*cohesionWeight=*/0.8, /*deltaTime=*/1.0);

    Renderer* renderer = createRaylibRenderer();
    if (!renderer->init(windowWidth, windowHeight, "Flocking - Sequential")) {
        std::cerr << "Error al inicializar la ventana\n";
        delete renderer;
        return 1;
    }

    Flock flock(config, /*seed=*/42);
    SequentialScheme scheme;

    while (!renderer->shouldClose()) {
        scheme.simulateStep(flock, config);

        renderer->beginDrawing();
        renderer->drawFlock(flock);
        renderer->endDrawing();
    }

    renderer->shutdown();
    delete renderer;
    return 0;
}
