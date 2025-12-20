# Día 8 del Advent of Code.

## Introducción.
El ejercicio trata la conexión de múltiples nodos (cajas de conexiones eléctricas) en un espacio 3D entre sí, por lo que se ha optado por resolver el problema mediante una estructura de grafos.

## Resolución del problema.
Se han implementado dos estructuras de datos, `Nodo` (definidas las coordenadas 3D de este) y `Conexiones` (definidos los diferentes nodos que se van a conectar, y la distancia euclidiana entre ellos).
Se ha introducido también la clase `Grafo`, que calcula todas las conexiones posibles entre los diferentes nodos, y lo almacena en vector (tablaConexiones).
Para finalizar, se ha implementado la clase `Circuito`, que sigue un algoritmo Union-Find. Las variables consisten de, un vector de enteros **padre** que indica el nodo padre del circuito al que pertenece (siendo inicialmente cada nodo su padre, indicado en el constructor), y un vector de enteros **tamanyo** que indica el tamaño de cada circuito. Los métodos consisten de: `Circuito(int n)`, el constructor; `encontrar(int nodox)`, para encontrar el verdadero padre del circuito; `migrar(int nodo1, int nodo2)`, para migrar nodo2 a nodo1, cambiando el padre de nodo2 y actualizando el tamaño de nodo1; y `getTamanyo()`, que devuelve los tamaños de los nodos que son padres, que en el main se ordenan para sacar la solución.
