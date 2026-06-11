#include "../../include/logica/Persistencia.h"

Persistencia::Persistencia() {
}

Persistencia::~Persistencia() {
}

bool Persistencia::guardarPartida(Partida* partida, string nombreArchivo) {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        return false;
    }

    Tablero* tablero = partida->getTablero();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pieza* pieza = tablero->getPieza(i, j);
            if (pieza == NULL) {
                archivo << "0 ";
            } else if (pieza->getColor() == BLANCO && !pieza->getEsReina()) {
                archivo << "1 ";
            } else if (pieza->getColor() == NEGRO && !pieza->getEsReina()) {
                archivo << "2 ";
            } else if (pieza->getColor() == BLANCO && pieza->getEsReina()) {
                archivo << "3 ";
            } else {
                archivo << "4 ";
            }
        }
        archivo << "\n";
    }

    archivo << partida->getJugadorActual()->getNombre() << "\n";
    archivo << partida->getJugador1()->getNombre() << "\n";
    archivo << partida->getJugador2()->getNombre() << "\n";

    archivo.close();
    return true;
}

bool Persistencia::cargarPartida(Partida* partida, string nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        return false;
    }

    Tablero* tablero = partida->getTablero();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero->eliminarPieza(i, j);
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int tipo;
            archivo >> tipo;

            if (tipo == 1) {
                tablero->setPieza(i, j, new PiezaNormal(BLANCO, i, j));
            } else if (tipo == 2) {
                tablero->setPieza(i, j, new PiezaNormal(NEGRO, i, j));
            } else if (tipo == 3) {
                tablero->setPieza(i, j, new Reina(BLANCO, i, j));
            } else if (tipo == 4) {
                tablero->setPieza(i, j, new Reina(NEGRO, i, j));
            }
        }
    }

    archivo.close();
    return true;
}