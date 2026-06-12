#include <SFML/Graphics.hpp>
#include "include/dominio/Tablero.h"
#include "include/dominio/Jugador.h"
#include "include/logica/Partida.h"
#include "include/logica/ReglasJuego.h"
#include "include/logica/Cpu.h"
#include "include/presentacion/Renderer.h"
#include "include/presentacion/GestorEventos.h"
#include "include/presentacion/Menu.h"

using namespace std;

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 850), "Ladys");
    ventana.setFramerateLimit(60);

    while (ventana.isOpen()) {
        Menu* menu = new Menu(&ventana);
        int opcion = menu->mostrar();
        delete menu;

        if (opcion == -1 || !ventana.isOpen()) return 0;

        Jugador* jugador1 = new Jugador("Jugador 1", BLANCO);
        Jugador* jugador2 = NULL;
        Partida* partida = NULL;

        if (opcion == 1) {
            jugador2 = new Jugador("Jugador 2", NEGRO);
            partida = new Partida(jugador1, jugador2);
        } else {
            partida = new Partida(jugador1, NULL);
            jugador2 = new Cpu("CPU", NEGRO, partida->getReglas(), partida->getTablero());
            partida->setJugador2(jugador2);
        }

        partida->iniciar();

        Renderer* renderer = new Renderer(&ventana);
        GestorEventos* gestor = new GestorEventos(&ventana, partida, renderer);

        renderer->limpiar();
        renderer->dibujarTablero();
        renderer->dibujarPiezas(partida->getTablero());
        renderer->dibujarInfo(partida);
        renderer->mostrar();

        while (ventana.isOpen() && !gestor->quiereVolverAlMenu()) {
            gestor->procesarEventos();
            if (partida->isPartidaTerminada()) {
                renderer->limpiar();
                renderer->dibujarTablero();
                renderer->dibujarPiezas(partida->getTablero());
                renderer->dibujarInfo(partida);
                renderer->dibujarPantallaFin(partida->getGanador());
                renderer->mostrar();
            }
        }

        delete gestor;
        delete renderer;
        delete partida;
        delete jugador1;
        delete jugador2;
    }

    return 0;
}
