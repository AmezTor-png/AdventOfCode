var entrada = [];

function main(){
    /*
    *      Array de objeto nodos
    *
    *      { [x,y,z] , siguienteNodo }
    */
    const nodos = [

    ]

    /*
    *      Array de objeto conexion
    *
    *      { nodo1 , nodo2, distancia }
    */
    const conexiones = []

    /*
    *      Array de objeto circuito
    *
    *      { nodos[] }
    */
    const circuitos = []

    // Asegura que cada circuito creado tenga un id único
    let contadorHash = 1;

    function llenarNodos(){
        for(let i = 0; i < entrada.length; i++){
            nodos.push({ x: entrada[i][0], y: entrada[i][1], z: entrada[i][2], circuito: undefined })
        }
    }

    function guardarConexion(conexion){
        const distanciaNueva = conexion.distancia;

        // Si el array está vacío, agregar directamente
        if(conexiones.length === 0){
            conexiones.push(conexion);
            return;
        }

        // Si es menor que el primero, insertar al inicio
        if(distanciaNueva <= conexiones[0].distancia){
            conexiones.splice(0, 0, conexion);
            return;
        }

        // Si es mayor que el último, insertar al final
        if(distanciaNueva >= conexiones[conexiones.length - 1].distancia){
            conexiones.push(conexion);
            return;
        }

        // Búsqueda binaria para encontrar la posición correcta
        let left = 0;
        let right = conexiones.length - 1;

        while(left <= right){
            let index = Math.floor((left + right) / 2);

            if(distanciaNueva < conexiones[index].distancia){
                right = index - 1;
            } else {
                left = index + 1;
            }
        }

        // Insertar en la posición correcta
        conexiones.splice(left, 0, conexion);
    }

    function crearTablaConexiones(){
    // Buscar conexión mas cercana
    for(let i = 0; i < nodos.length;i++){

        // Extraer posición primer nodo
        const x1 = nodos[i].x
        const y1 = nodos[i].y
        const z1 = nodos[i].z

        for(let j = 0; j < nodos.length; j++){
            // Si es el mismo nodo o uno anterior, saltar
            if(i>=j) continue;

            // Extraer posición segundo nodo 
            const x2 = nodos[j].x
            const y2 = nodos[j].y
            const z2 = nodos[j].z

            // Calcular distancia
            const distancia = Math.sqrt((x1-x2)**2 + (y1-y2)**2 + (z1-z2)**2); 

            // Crear nueva conexion 
            const conexion = {
                nodos:[i,j],
                distancia: distancia
            }

            guardarConexion(conexion);

        }
    }
    }

    function crearCircuito(nodo1, nodo2){
        // Crear nuevo circuito al final de la lista
        const circuito = { id:  contadorHash, nodos: [nodo1, nodo2] }
        circuitos.push(circuito)

        // Asignar circuito a los nodos
        nodos[nodo1].circuito = contadorHash;
        nodos[nodo2].circuito = contadorHash;
        
        contadorHash++;
        
        return contadorHash-1;
    }

    function migrarCircuito(origen, destino){
        let circuitoOrigen, circuitoDestino;
        
        for(let i = 0; i < circuitos.length; i++){
            if(circuitos[i].id == origen) circuitoOrigen = circuitos[i];
            if(circuitos[i].id == destino) circuitoDestino = circuitos[i];
        }
        
        // Reasignar nodos del circuito de origen al de destino
        for(let j = 0; j < circuitoOrigen.nodos.length; j++){
            nodos[circuitoOrigen.nodos[j]].circuito = destino;
            circuitoDestino.nodos.push(circuitoOrigen.nodos[j]);
        }

        // Borramos circuito vacío
        for(let i = 0; i < circuitos.length; i++){
            if(circuitos[i].id == origen){
                circuitos.splice(i,1);
                return 0;
            }
        }
    }

    // LLenar la clase nodos
    llenarNodos();
    console.log("Nodos: ",nodos)

    // Creamos todas las conexiones posibles ordenadas por distancia
    crearTablaConexiones();
    console.log("Conexiones: ", conexiones)

    const limite = 500;

    // Crear circuitos
    for(let i = 0; i < Math.min(conexiones.length, limite); i++){
        let conexionActual = conexiones[i];

        const nodo1 = nodos[conexionActual.nodos[0]];
        const nodo2 = nodos[conexionActual.nodos[1]];
        const numeroNodo1 = conexionActual.nodos[0];
        const numeroNodo2 = conexionActual.nodos[1];

        // Si no estan en un circuito , crear un circuito
        if(!nodo1.circuito && !nodo2.circuito){
            crearCircuito(numeroNodo1, numeroNodo2);
        }

        // Si uno está, añadir los dos al circuito
        if(nodo1.circuito && !nodo2.circuito){
            nodo2.circuito = nodo1.circuito;
            for(let c of circuitos){
                if(c.id == nodo1.circuito){
                    c.nodos.push(numeroNodo2);
                    break;
                }
            }
        }
        if(!nodo1.circuito && nodo2.circuito){
            nodo1.circuito = nodo2.circuito;
            for(let c of circuitos){
                if(c.id == nodo2.circuito){
                    c.nodos.push(numeroNodo1);
                    break;
                }
            }
        }

        // Si los dos están en distintos, añadir los dos al circuito
        if(nodo1.circuito && nodo2.circuito && nodo1.circuito !== nodo2.circuito){
            migrarCircuito(nodo1.circuito, nodo2.circuito)
        }
    }


    console.log(circuitos);
}

fetch('/input.txt')
.then(res => res.text())
.then(content => {
    const lines = content.split('\n');
    lines.forEach(line => {
        const trimmedLine = line.trim();
        if (trimmedLine) {
            const numeros = trimmedLine.split(',').map(Number);
            entrada.push(numeros);
        }
    });
}).then(()=> main());