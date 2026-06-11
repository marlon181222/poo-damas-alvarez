# Ladys - Juego de Damas

Proyecto de examen parcial de la asignatura Programacion Orientada a Objetos.
Carrera: Ingenieria en Telecomunicaciones y Electronica.
Universidad de Pinar del Rio "Hermanos Saiz Montes de Oca". Curso 2024-2025.

## Integrantes
- [Nombre 1] (lider)
- [Nombre 2]
- [Nombre 3]
- [Nombre 4]
- [Nombre 5]
- [Nombre 6]
- [Nombre 7]

## Sobre el proyecto

Implementamos el juego de damas digital en C++11 usando la biblioteca SFML
para la interfaz grafica. El juego tiene dos modos:
-Un solo jugador (vs CPU).
-Dos jugadores.
La CPU usa el algoritmo Minimax con profundidad 3 para
elegir sus movimientos. Se pueden guardar y cargar partidas desde un
archivo de texto.

## Reglas implementadas

- Las piezas normales solo se mueven hacia adelante en diagonal
- La captura es obligatoria cuando hay una pieza enemiga que se puede comer
- Las piezas normales no pueden comer hacia atras
- Cuando una pieza llega al extremo opuesto se corona y se convierte en reina
- La reina se puede mover en diagonal en cualquier direccion y cualquier
  numero de casillas
- El juego termina cuando un jugador se queda sin piezas o sin movimientos
- Gana el jugador que deja al rival sin piezas o sin movimientos posibles

## Controles

- Clic izquierdo: seleccionar y mover piezas
- G: guardar la partida actual en un archivo
- C: cargar la ultima partida guardada
- Icono de casita: volver al menu principal

## Como compilar

Compilar con TDM-GCC 9.2.0 64-bit en Dev C++ 6.3 con SFML 2.5.1
en modo estatico.

En Project Options, campo Linker agregar:
-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32
-lfreetype -lwinmm -lgdi32 -lflac -lvorbisenc -lvorbisfile
-lvorbis -logg -static-libgcc -static-libstdc++

En Project Options, campo C++ Compiler agregar:
-DSFML_STATIC

## Dependencias

- SFML 2.5.1 en modo estatico
- TDM-GCC 9.2.0 64-bit
- Dev C++ 6.3

## Estructura del proyecto

- src/dominio/      : clases principales del juego
- src/logica/       : reglas, partida, CPU y persistencia
- src/presentacion/ : interfaz grafica con SFML
- include/          : archivos de cabecera organizados igual que src
- assets/imagenes/  : imagen de fondo del menu
- assets/fuentes/   : fuente tipografica del juego

## Contenedores STL utilizados

### std::vector
Usado en la clase Tablero para representar la cuadricula de juego como
un vector de vectores de punteros a Pieza:
vector<vector<Pieza*>> cuadricula
Tambien usado en la clase Cpu para almacenar todos los movimientos
posibles antes de aplicar Minimax.

### std::set
Usado en la clase ReglasJuego para almacenar las casillas donde una
pieza puede moverse:
set<pair<int,int>> movimientos
El set evita movimientos duplicados y permite buscar rapidamente si
una casilla destino es valida.

### std::map
Usado en la clase Partida para registrar las estadisticas de cada
jugador asociando su nombre con su cantidad de victorias:
map<string, int> estadisticas

## Algoritmo Minimax

La CPU usa el algoritmo Minimax con profundidad 3. En cada turno
analiza todos sus movimientos posibles, simula 3 movimientos hacia
adelante y elige el que le da la mejor puntuacion. La funcion de
evaluacion asigna 1 punto por cada pieza normal y 3 puntos por cada
reina. Las piezas propias suman puntos y las del rival restan.
La CPU respeta todas las reglas del juego incluyendo la captura
obligatoria.
