# osoto_-a2_2026_s2
Projects developed for Computer Arquitecture II (CE4302) course


# Proposed Structure

```bash
osoto_a2_2026_s2/
├── README.md
├── .gitgnore
└── Proyect_1-Multithreading/
    ├── shared/                      # Infraestructura compartida (una sola vez)
    │   ├── include/
    │   │   ├── Timer.hpp
    │   │   ├── ExecutionMetrics.hpp     # struct genérico: schemeName, threads, ms, unitsProcessed
    │   │   └── MetricsCsvWriter.hpp     # exporta metrics a CSV con formato único
    │   └── src/
    │       ├── Timer.cpp
    │       └── MetricsCsvWriter.cpp
    │
    ├── n_body/
    │   └── include/  src/  docs/  README.md  Makefile
    │
    ├── Fluids/
    │   └── include/  src/  docs/  README.md  Makefile
    │
    ├── Ray_Tracing/
    │   └── include/  src/  docs/  README.md  Makefile
    │
    ├── Boids/
    │   └── include/  src/  docs/  README.md  Makefile
    │
    ├── docs/                         # LaTeX del reporte final, compartido
    │   ├── informe_final.tex
    │   ├── Proyectos_Arqui2_Proyecto_Individual_v3.pdf
    │   └── informe_final_link
    │
    ├── scripts/
    │   └── plot_metrics.py           # lee los CSV de los 4 y genera las gráficas
    │
    └── Makefile                      # top-level: make all / make Fluids / make Boids...
```