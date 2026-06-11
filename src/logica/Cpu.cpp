#include "../../include/logica/Cpu.h"

Cpu::Cpu(string nom, Color c, ReglasJuego* r, Tablero* t) : Jugador(nom, c) {
    reglas = r;
    tablero = t;
}

Cpu::~Cpu() {
}

bool Cpu::esCPU() const {
    return true;
}

int Cpu::evaluar() {
    int puntuacion = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!tablero->estaVacia(i, j)) {
                Pieza* pieza = tablero->getPieza(i, j);
                int valor = pieza->getEsReina() ? 3 : 1;
                if (pieza->getColor() == color) {
                    puntuacion += valor;
                } else {
                    puntuacion -= valor;
                }
            }
        }
    }
    return puntuacion;
}

vector<pair<pair<int,int>, pair<int,int>>> Cpu::obtenerMovimientos(Color c) {
    vector<pair<pair<int,int>, pair<int,int>>> movimientos;
    vector<pair<pair<int,int>, pair<int,int>>> capturas;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!tablero->estaVacia(i, j) &&
                tablero->getPieza(i, j)->getColor() == c) {
                if (reglas->hayCaptura(i, j)) {
                    set<pair<int,int>> movsPieza = reglas->getMovimientosValidos(i, j);
                    for (auto mov : movsPieza) {
                        capturas.push_back(make_pair(make_pair(i, j), mov));
                    }
                }
            }
        }
    }

    if (!capturas.empty()) return capturas;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!tablero->estaVacia(i, j) &&
                tablero->getPieza(i, j)->getColor() == c) {
                set<pair<int,int>> movsPieza = reglas->getMovimientosValidos(i, j);
                for (auto mov : movsPieza) {
                    movimientos.push_back(make_pair(make_pair(i, j), mov));
                }
            }
        }
    }

    return movimientos;
}

int Cpu::minimax(int profundidad, bool esMaximizador) {
    if (profundidad == 0) {
        return evaluar();
    }

    Color colorActual = esMaximizador ? color : (color == BLANCO ? NEGRO : BLANCO);
    vector<pair<pair<int,int>, pair<int,int>>> movimientos = obtenerMovimientos(colorActual);

    if (movimientos.empty()) {
        return esMaximizador ? -1000 : 1000;
    }

    if (esMaximizador) {
        int mejorPuntuacion = INT_MIN;
        for (auto mov : movimientos) {
            Tablero* copia = tablero->copiar();
            Tablero* tableroAnterior = tablero;
            ReglasJuego* reglasAnterior = reglas;

            tablero = copia;
            reglas = new ReglasJuego(tablero);

            reglas->realizarMovimiento(
                mov.first.first, mov.first.second,
                mov.second.first, mov.second.second
            );

            int puntuacion = minimax(profundidad - 1, false);

            delete reglas;
            delete tablero;
            tablero = tableroAnterior;
            reglas = reglasAnterior;

            mejorPuntuacion = max(mejorPuntuacion, puntuacion);
        }
        return mejorPuntuacion;
    } else {
        int mejorPuntuacion = INT_MAX;
        for (auto mov : movimientos) {
            Tablero* copia = tablero->copiar();
            Tablero* tableroAnterior = tablero;
            ReglasJuego* reglasAnterior = reglas;

            tablero = copia;
            reglas = new ReglasJuego(tablero);

            reglas->realizarMovimiento(
                mov.first.first, mov.first.second,
                mov.second.first, mov.second.second
            );

            int puntuacion = minimax(profundidad - 1, true);

            delete reglas;
            delete tablero;
            tablero = tableroAnterior;
            reglas = reglasAnterior;

            mejorPuntuacion = min(mejorPuntuacion, puntuacion);
        }
        return mejorPuntuacion;
    }
}

void Cpu::realizarMovimiento() {
    vector<pair<pair<int,int>, pair<int,int>>> movimientos = obtenerMovimientos(color);

    if (movimientos.empty()) return;

    int mejorPuntuacion = INT_MIN;
    pair<pair<int,int>, pair<int,int>> mejorMovimiento = movimientos[0];

    for (auto mov : movimientos) {
        Tablero* copia = tablero->copiar();
        Tablero* tableroAnterior = tablero;
        ReglasJuego* reglasAnterior = reglas;

        tablero = copia;
        reglas = new ReglasJuego(tablero);

        reglas->realizarMovimiento(
            mov.first.first, mov.first.second,
            mov.second.first, mov.second.second
        );

        int puntuacion = minimax(3, false);

        delete reglas;
        delete tablero;
        tablero = tableroAnterior;
        reglas = reglasAnterior;

        if (puntuacion > mejorPuntuacion) {
            mejorPuntuacion = puntuacion;
            mejorMovimiento = mov;
        }
    }

    reglas->realizarMovimiento(
        mejorMovimiento.first.first,
        mejorMovimiento.first.second,
        mejorMovimiento.second.first,
        mejorMovimiento.second.second
    );
}