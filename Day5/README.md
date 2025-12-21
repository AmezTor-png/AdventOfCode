# Día 5 del Advent of Code

## Introducción.
El ejercicio trata sobre determinar qué IDs de ingredientes están frescos en base a rangos de IDs proporcionados. Para resolverlo, hemos optado por una estructura de árbol de intervalos, que permite buscar de manera eficiente si un ID pertenece a algún rango.

## Resolución del problema.
Se han implementado las siguientes estructuras y conceptos:

`IntervalNode()`: el constructor. Cada nodo representa un rango de IDs (low, high). Tiene punteros a left y right para construir el árbol de intervalos.

**Árbol de Intervalos**: Permite almacenar todos los rangos de ingredientes frescos de manera jerárquica. Para cada ID, se recorre el árbol recursivamente para determinar si está contenido en algún rango.

De las funciones principales destacan: `insert(IntervalNode* root, long long l, long long h)`, que inserta un nuevo rango en el árbol; y `contains(IntervalNode* root, long long id)`, que devuelve true si el ID pertenece a algún rango.

## Compilación.
`g++ -std=c++17 -o parte2 parte2_dia5.cpp` -> Compilar
`./main` -> Ejecutar (abre el archivo input.txt)

## Valoración personal.
Este problema nos ha hecho entender y aplicar árboles de intervalos para resolver problemas de pertenencia en rangos. El uso del árbol permite justificar estructuras jerárquicas en problemas de búsqueda. Hemos aprendido a combinar lectura de datos, estructuras de datos y recursión para resolver un problema práctico de inventario.
