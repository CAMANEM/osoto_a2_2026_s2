# Flocking / Boids — Demostración 2 (CE4302, Proyecto Grupal 1)

## Compilar y ejecutar

```bash
make run
```

Imprime la tabla de métricas preliminares (con validación de correctitud) y exporta 70 frames `.ppm` en `frames/` mostrando 350 pasos de simulación. Para verlos como animación:

```bash
convert -delay 6 -loop 0 frames/frame_*.ppm flock.gif
```

(requiere ImageMagick; si no está instalado, cualquier herramienta que combine PPM en GIF/MP4 sirve, p. ej. `ffmpeg -i frames/frame_%03d.ppm flock.mp4`).

## Qué cumple esta entrega (según el enunciado de la Demo 2)

| Requisito de la Demo 2 | Dónde está |
|---|---|
| Ejecución del sistema base (sin hilos) | `SequentialScheme` |
| Identificación de variables críticas | Ver sección siguiente y comentarios en `main.cpp` |
| Ejecución dummy/parcial de grano fino | `FineGrainedScheme` (round-robin por vecino candidato, 20 boids) |
| Ejecución dummy de grano grueso | `CoarseGrainedScheme` (4 hilos tradicionales) |
| Ejecución dummy de SMT | `SmtScheme` (2× `hardware_concurrency()`, sobre-suscripción) |
| Ejecución dummy de CMP | `CmpScheme` (1 hilo por núcleo lógico reportado por el SO) |
| Mediciones de tiempo por esquema | `SimulationMetrics` + `Timer`, impresas en `main.cpp` |
| Evidencia visual funcional | `FrameWriter` + `frames/` (frames de la animación) |

Lo que **no** corresponde a esta etapa: las 200 ejecuciones por configuración, boxplots, intervalos de confianza al 95% y perfilado con `perf`/VTune — eso es para el reporte final.

## Variables críticas identificadas

- **`boidCount`**: determina el volumen total de trabajo; en el peor caso (brute-force, como en N-Body) cada paso evalúa hasta `boidCount × (boidCount - 1)` pares candidato-vecino.
- **`perceptionRadius` / `separationRadius`**: controlan cuántos vecinos **reales** evalúa cada boid dentro de ese radio. Aquí está la fuente de irregularidad de este problema: aunque el algoritmo *revisa* a todos los demás boids (como N-Body), solo *acumula* contribución de los que caen dentro del radio. Un boid en el centro de un grupo ya formado tiene muchos más vecinos "activos" que uno disperso en una zona vacía — density-dependent, similar en espíritu a la irregularidad de Mandelbrot, pero originada por la dinámica espacial del sistema en vez del tiempo de escape de un cálculo.
- **Pesos de las reglas (`separationWeight`, `alignmentWeight`, `cohesionWeight`) y `maxForce`**: no afectan el costo computacional, pero sí determinan si el enjambre converge en un grupo cohesionado o se fragmenta en sub-grupos — importante para explicar visualmente lo que se ve en la demo, aunque no es una variable de rendimiento.

## Decisiones de diseño relevantes para la defensa

- **Cálculo en dos fases** (`SequentialScheme` y `ThreadedScheme`): primero se calculan TODAS las fuerzas de dirección leyendo el enjambre sin modificar, y solo después se aplican TODAS las integraciones. Esto es indispensable para que el resultado no dependa del orden de procesamiento de los boids, y es lo que permite paralelizar sin condiciones de carrera (cada hilo escribe en una porción disjunta del vector de fuerzas, nunca en los boids directamente).
- **Grano fino con `SteeringContext`**: mismo mecanismo formal usado en Mandelbrot/matrices — un "ciclo" es examinar un único vecino candidato, con planificación round-robin por software. Aquí el análogo del "stall" es un boid con muchos vecinos por examinar (le toma más ciclos completar su cálculo).
- **`FlockingRules::combineForces` compartido**: tanto el barrido directo (`computeSteeringForBoid`) como el cálculo incremental (`SteeringContext`) usan exactamente la misma función de combinación final, evitando duplicar la fórmula de las tres reglas (principio DRY) y garantizando que ambos caminos den resultados idénticos.

## Cómo se ve la simulación

Con los parámetros por defecto, el enjambre arranca completamente disperso y, tras ~150-200 pasos, se agrupa en varios sub-enjambres que se mueven de forma coordinada (visible en las pequeñas líneas de dirección alineadas dentro de cada grupo). Es un comportamiento válido de boids: dependiendo de la semilla aleatoria y los pesos, el sistema puede converger en un solo grupo grande o en varios más pequeños. Si el grupo prefiere una única parvada grande y más vistosa para la presentación, se puede subir `cohesionWeight` (p. ej. a 1.5) y `perceptionRadius` (p. ej. a 70) en `main.cpp`.


D:/caman/Documents/Flash Drive Maya/College/Arquitectura de Computadores II/Proyecto/boids_demo2