#include "../../include/presentacion/Renderer.h"

Renderer::Renderer(sf::RenderWindow* vent) {
    ventana = vent;
    tamCelda = 100.0f;
    fuente.loadFromFile("assets/fuentes/arial.ttf");
    confetiIniciado = false;
}

Renderer::~Renderer() {
}

void Renderer::dibujarTablero() {
    sf::RectangleShape borde(sf::Vector2f(808, 808));
    borde.setPosition(-4, -4);
    borde.setFillColor(sf::Color(40, 40, 40));
    ventana->draw(borde);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape celda(sf::Vector2f(tamCelda, tamCelda));
            celda.setPosition(j * tamCelda, i * tamCelda);

            if ((i + j) % 2 == 0) {
                celda.setFillColor(sf::Color(240, 217, 181));
            } else {
                celda.setFillColor(sf::Color(160, 110, 70));
            }

            ventana->draw(celda);
        }
    }
}

void Renderer::dibujarPiezas(Tablero* tablero) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pieza* pieza = tablero->getPieza(i, j);
            if (pieza != NULL) {
                float x = j * tamCelda + tamCelda / 2;
                float y = i * tamCelda + tamCelda / 2;
                float radio = tamCelda / 2 - 8;

                sf::CircleShape sombra(radio);
                sombra.setOrigin(radio, radio);
                sombra.setPosition(x + 4, y + 4);
                sombra.setFillColor(sf::Color(0, 0, 0, 80));
                ventana->draw(sombra);

                sf::CircleShape exterior(radio);
                exterior.setOrigin(radio, radio);
                exterior.setPosition(x, y);

                if (pieza->getColor() == BLANCO) {
                    exterior.setFillColor(sf::Color(230, 230, 230));
                    exterior.setOutlineColor(sf::Color(180, 180, 180));
                } else {
                    exterior.setFillColor(sf::Color(40, 40, 40));
                    exterior.setOutlineColor(sf::Color(20, 20, 20));
                }

                exterior.setOutlineThickness(3);
                ventana->draw(exterior);

                float radioInterior = radio - 8;
                sf::CircleShape interior(radioInterior);
                interior.setOrigin(radioInterior, radioInterior);
                interior.setPosition(x - 4, y - 4);

                if (pieza->getColor() == BLANCO) {
                    interior.setFillColor(sf::Color(255, 255, 255, 150));
                } else {
                    interior.setFillColor(sf::Color(80, 80, 80, 150));
                }

                ventana->draw(interior);

                if (pieza->getEsReina()) {
                    dibujarCorona(x, y);
                }
            }
        }
    }
}

void Renderer::dibujarCorona(float x, float y) {
    y = y - 5;

    sf::ConvexShape base;
    base.setPointCount(4);
    base.setPoint(0, sf::Vector2f(x - 22, y + 16));
    base.setPoint(1, sf::Vector2f(x + 22, y + 16));
    base.setPoint(2, sf::Vector2f(x + 18, y + 4));
    base.setPoint(3, sf::Vector2f(x - 18, y + 4));
    base.setFillColor(sf::Color(218, 165, 32));
    base.setOutlineColor(sf::Color(139, 101, 8));
    base.setOutlineThickness(1.5);
    ventana->draw(base);

    sf::ConvexShape pIzq;
    pIzq.setPointCount(3);
    pIzq.setPoint(0, sf::Vector2f(x - 18, y + 4));
    pIzq.setPoint(1, sf::Vector2f(x - 22, y - 16));
    pIzq.setPoint(2, sf::Vector2f(x - 8, y + 4));
    pIzq.setFillColor(sf::Color(218, 165, 32));
    pIzq.setOutlineColor(sf::Color(139, 101, 8));
    pIzq.setOutlineThickness(1.5);
    ventana->draw(pIzq);

    sf::ConvexShape pCen;
    pCen.setPointCount(3);
    pCen.setPoint(0, sf::Vector2f(x - 8, y + 4));
    pCen.setPoint(1, sf::Vector2f(x, y - 24));
    pCen.setPoint(2, sf::Vector2f(x + 8, y + 4));
    pCen.setFillColor(sf::Color(255, 200, 0));
    pCen.setOutlineColor(sf::Color(139, 101, 8));
    pCen.setOutlineThickness(1.5);
    ventana->draw(pCen);

    sf::ConvexShape pDer;
    pDer.setPointCount(3);
    pDer.setPoint(0, sf::Vector2f(x + 8, y + 4));
    pDer.setPoint(1, sf::Vector2f(x + 22, y - 16));
    pDer.setPoint(2, sf::Vector2f(x + 18, y + 4));
    pDer.setFillColor(sf::Color(218, 165, 32));
    pDer.setOutlineColor(sf::Color(139, 101, 8));
    pDer.setOutlineThickness(1.5);
    ventana->draw(pDer);

    sf::CircleShape gemaTop(5);
    gemaTop.setOrigin(5, 5);
    gemaTop.setPosition(x, y - 24);
    gemaTop.setFillColor(sf::Color(139, 0, 0));
    gemaTop.setOutlineColor(sf::Color(180, 0, 0));
    gemaTop.setOutlineThickness(1);
    ventana->draw(gemaTop);

    sf::CircleShape gemaIzq(4);
    gemaIzq.setOrigin(4, 4);
    gemaIzq.setPosition(x - 22, y - 16);
    gemaIzq.setFillColor(sf::Color(0, 0, 100));
    gemaIzq.setOutlineColor(sf::Color(0, 0, 150));
    gemaIzq.setOutlineThickness(1);
    ventana->draw(gemaIzq);

    sf::CircleShape gemaDer(4);
    gemaDer.setOrigin(4, 4);
    gemaDer.setPosition(x + 22, y - 16);
    gemaDer.setFillColor(sf::Color(0, 0, 100));
    gemaDer.setOutlineColor(sf::Color(0, 0, 150));
    gemaDer.setOutlineThickness(1);
    ventana->draw(gemaDer);

    sf::CircleShape gemaBase1(3);
    gemaBase1.setOrigin(3, 3);
    gemaBase1.setPosition(x - 12, y + 10);
    gemaBase1.setFillColor(sf::Color(139, 0, 0));
    gemaBase1.setOutlineColor(sf::Color(180, 0, 0));
    gemaBase1.setOutlineThickness(1);
    ventana->draw(gemaBase1);

    sf::CircleShape gemaBase2(3);
    gemaBase2.setOrigin(3, 3);
    gemaBase2.setPosition(x, y + 10);
    gemaBase2.setFillColor(sf::Color(0, 0, 100));
    gemaBase2.setOutlineColor(sf::Color(0, 0, 150));
    gemaBase2.setOutlineThickness(1);
    ventana->draw(gemaBase2);

    sf::CircleShape gemaBase3(3);
    gemaBase3.setOrigin(3, 3);
    gemaBase3.setPosition(x + 12, y + 10);
    gemaBase3.setFillColor(sf::Color(139, 0, 0));
    gemaBase3.setOutlineColor(sf::Color(180, 0, 0));
    gemaBase3.setOutlineThickness(1);
    ventana->draw(gemaBase3);
}

void Renderer::dibujarMovimientosValidos(set<pair<int,int>> movimientos) {
    for (auto mov : movimientos) {
        float x = mov.second * tamCelda + tamCelda / 2;
        float y = mov.first * tamCelda + tamCelda / 2;
        float radio = tamCelda / 4;

        sf::CircleShape circulo(radio);
        circulo.setOrigin(radio, radio);
        circulo.setPosition(x, y);
        circulo.setFillColor(sf::Color(150, 150, 150, 180));
        circulo.setOutlineColor(sf::Color(100, 100, 100, 220));
        circulo.setOutlineThickness(2);
        ventana->draw(circulo);
    }
}

void Renderer::dibujarInfo(Partida* partida) {
    if (!fuente.loadFromFile("assets/fuentes/arial.ttf")) return;

    sf::RectangleShape fondo(sf::Vector2f(800, 50));
    fondo.setPosition(0, 800);
    fondo.setFillColor(sf::Color(30, 30, 30));
    ventana->draw(fondo);

    sf::Text turno;
    turno.setFont(fuente);
    turno.setCharacterSize(20);
    turno.setFillColor(sf::Color::White);
    turno.setPosition(10, 812);
    turno.setString("Turno: " + partida->getJugadorActual()->getNombre());
    ventana->draw(turno);

    sf::Text controles;
    controles.setFont(fuente);
    controles.setCharacterSize(16);
    controles.setFillColor(sf::Color(180, 180, 180));
    controles.setPosition(280, 815);
    controles.setString("G: Guardar   C: Cargar");
    ventana->draw(controles);

    float cx = 755;
    float cy = 825;

    sf::RectangleShape base(sf::Vector2f(30, 18));
    base.setPosition(cx - 15, cy - 6);
    base.setFillColor(sf::Color(160, 110, 70));
    base.setOutlineColor(sf::Color(200, 160, 100));
    base.setOutlineThickness(1.5);
    ventana->draw(base);

    sf::RectangleShape puerta(sf::Vector2f(8, 11));
    puerta.setPosition(cx - 4, cy + 1);
    puerta.setFillColor(sf::Color(80, 50, 20));
    puerta.setOutlineColor(sf::Color(120, 80, 40));
    puerta.setOutlineThickness(1);
    ventana->draw(puerta);

    sf::RectangleShape ventanita(sf::Vector2f(6, 6));
    ventanita.setPosition(cx - 13, cy - 3);
    ventanita.setFillColor(sf::Color(150, 210, 255));
    ventanita.setOutlineColor(sf::Color(200, 160, 100));
    ventanita.setOutlineThickness(1);
    ventana->draw(ventanita);

    sf::ConvexShape techo;
    techo.setPointCount(3);
    techo.setPoint(0, sf::Vector2f(cx - 18, cy - 6));
    techo.setPoint(1, sf::Vector2f(cx, cy - 20));
    techo.setPoint(2, sf::Vector2f(cx + 18, cy - 6));
    techo.setFillColor(sf::Color(160, 110, 70));
    techo.setOutlineColor(sf::Color(200, 160, 100));
    techo.setOutlineThickness(1.5);
    ventana->draw(techo);
}

void Renderer::dibujarPantallaFin(string ganador) {
    if (!confetiIniciado) {
        confeti.iniciar();
        confetiIniciado = true;
    }

    confeti.actualizar();

    sf::RectangleShape fondo(sf::Vector2f(800, 800));
    fondo.setFillColor(sf::Color(0, 0, 0, 160));
    ventana->draw(fondo);

    confeti.dibujar(ventana);

    if (!fuente.loadFromFile("assets/fuentes/arial.ttf")) return;

    sf::Text sombra;
    sombra.setFont(fuente);
    sombra.setCharacterSize(55);
    sombra.setFillColor(sf::Color(0, 0, 0, 200));
    sombra.setString("Gano: " + ganador);
    sombra.setPosition(202, 322);
    ventana->draw(sombra);

    sf::Text texto;
    texto.setFont(fuente);
    texto.setCharacterSize(55);
    texto.setFillColor(sf::Color(255, 215, 0));
    texto.setOutlineColor(sf::Color(180, 140, 0));
    texto.setOutlineThickness(2);
    texto.setString("Gano: " + ganador);
    texto.setPosition(200, 320);
    ventana->draw(texto);

    sf::RectangleShape boton(sf::Vector2f(300, 50));
    boton.setPosition(250, 430);
    boton.setFillColor(sf::Color(101, 67, 33, 220));
    boton.setOutlineColor(sf::Color(255, 215, 0));
    boton.setOutlineThickness(2);
    ventana->draw(boton);

    sf::Text textoBoton;
    textoBoton.setFont(fuente);
    textoBoton.setCharacterSize(24);
    textoBoton.setFillColor(sf::Color(255, 240, 200));
    textoBoton.setString("Volver al Menu");
    textoBoton.setPosition(272, 440);
    ventana->draw(textoBoton);
}

void Renderer::actualizarConfeti() {
    confeti.actualizar();
}

void Renderer::limpiar() {
    ventana->clear(sf::Color(50, 50, 50));
}

void Renderer::mostrar() {
    ventana->display();
}