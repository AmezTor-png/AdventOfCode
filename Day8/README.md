# Día 8 del Advent of Code.

## Introducción.
El ejercicio trata la conexión de múltiples nodos (cajas de conexiones eléctricas) en un espacio 3D entre sí, por lo que se ha optado por resolver el problema mediante una estructura de grafos.

## Resolución del problema.
Se han implementado dos estructuras de datos, `Nodo` (definidas las coordenadas 3D de este) y `Conexiones` (definidos los diferentes nodos que se van a conectar, y la distancia euclidiana entre ellos).
