#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <optional>

enum Estado {
    INICIO,
    JUGANDO,
    GAME_OVER
};

struct Topo {
    sf::Vector2f posicion;
    bool activo;
    float tiempoVisible;
    float temporizador;
    int tipo;
    int vidas;
};

void reiniciarJuego(std::vector<Topo>& topos, int& puntaje, int& vidas, float& tiempo, float& spawn) {
    puntaje = 0;
    vidas = 5;
    tiempo = 60.0f;
    spawn = 0.0f;

    for (auto& t : topos) {
        t.activo = false;
        t.temporizador = 0;
        t.tipo = 0;
        t.vidas = 1;
    }
}

void golpearTopo(std::vector<Topo>& topos, int indice, int& puntaje, int& vidas) {
    if (indice < 0 || indice >= (int)topos.size()) return;

    if (topos[indice].activo) {
        if (topos[indice].tipo == 0) {
            puntaje += 10;
            topos[indice].activo = false;
        }
        else if (topos[indice].tipo == 1) {
            topos[indice].vidas--;

            if (topos[indice].vidas <= 0) {
                puntaje += 25;
                topos[indice].activo = false;
            }
        }
        else if (topos[indice].tipo == 2) {
            puntaje -= 20;
            vidas--;
            topos[indice].activo = false;
        }
    }
    else {
        puntaje -= 2;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const unsigned int ancho = 1080;
    const unsigned int alto = 720;

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(ancho, alto)),
        "Proyecto 252 - Topo Mania PRO"
    );

    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "ERROR: No se pudo cargar assets/Fonts/arial.ttf\n";
        return 1;
    }

    sf::Texture texturaMenu;
    if (!texturaMenu.loadFromFile("assets/Imagenes/menu.png")) {
        std::cout << "ERROR: No se pudo cargar assets/Imagenes/menu.png\n";
        return 1;
    }

    sf::Texture texturaJuego;
    if (!texturaJuego.loadFromFile("assets/Imagenes/juego.jpg")) {
        std::cout << "ERROR: No se pudo cargar assets/Imagenes/juego.jpg\n";
        return 1;
    }

    sf::Sprite fondoMenu(texturaMenu);
    fondoMenu.setScale(sf::Vector2f(
        (float)ancho / texturaMenu.getSize().x,
        (float)alto / texturaMenu.getSize().y
    ));

    sf::Sprite fondoJuego(texturaJuego);
    fondoJuego.setScale(sf::Vector2f(
        (float)ancho / texturaJuego.getSize().x,
        (float)alto / texturaJuego.getSize().y
    ));

    Estado estado = INICIO;

    std::vector<Topo> topos;
    const int totalTopos = 4;

    int inicioX = 180;
    int inicioY = 390;
    int espacioX = 240;

    for (int i = 0; i < totalTopos; i++) {
        Topo t;
        t.posicion = sf::Vector2f(inicioX + i * espacioX, inicioY);
        t.activo = false;
        t.tiempoVisible = 1.5f;
        t.temporizador = 0;
        t.tipo = 0;
        t.vidas = 1;
        topos.push_back(t);
    }

    int puntaje = 0;
    int vidas = 5;
    float tiempo = 60.0f;
    float temporizadorSpawn = 0.0f;
    float intervaloSpawn = 0.75f;

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }

                if (estado == INICIO && keyEvent->code == sf::Keyboard::Key::Enter) {
                    reiniciarJuego(topos, puntaje, vidas, tiempo, temporizadorSpawn);
                    estado = JUGANDO;
                }

                if (estado == GAME_OVER && keyEvent->code == sf::Keyboard::Key::Enter) {
                    estado = INICIO;
                }

                if (estado == JUGANDO) {
                    if (keyEvent->code == sf::Keyboard::Key::Num1) golpearTopo(topos, 0, puntaje, vidas);
                    if (keyEvent->code == sf::Keyboard::Key::Num2) golpearTopo(topos, 1, puntaje, vidas);
                    if (keyEvent->code == sf::Keyboard::Key::Num3) golpearTopo(topos, 2, puntaje, vidas);
                    if (keyEvent->code == sf::Keyboard::Key::Num4) golpearTopo(topos, 3, puntaje, vidas);
                }
            }
        }

        if (estado == JUGANDO) {
            tiempo -= dt;
            temporizadorSpawn += dt;

            if (tiempo <= 0 || vidas <= 0) {
                estado = GAME_OVER;
            }

            intervaloSpawn = 0.75f;
            if (puntaje >= 100) intervaloSpawn = 0.60f;
            if (puntaje >= 200) intervaloSpawn = 0.48f;
            if (puntaje >= 350) intervaloSpawn = 0.35f;

            if (temporizadorSpawn >= intervaloSpawn) {
                temporizadorSpawn = 0;

                int indice = rand() % totalTopos;

                if (!topos[indice].activo) {
                    int prob = rand() % 100;

                    if (prob < 65) {
                        topos[indice].tipo = 0;
                        topos[indice].vidas = 1;
                        topos[indice].tiempoVisible = 1.4f;
                    }
                    else if (prob < 85) {
                        topos[indice].tipo = 1;
                        topos[indice].vidas = 2;
                        topos[indice].tiempoVisible = 1.8f;
                    }
                    else {
                        topos[indice].tipo = 2;
                        topos[indice].vidas = 1;
                        topos[indice].tiempoVisible = 1.2f;
                    }

                    topos[indice].activo = true;
                    topos[indice].temporizador = 0;
                }
            }

            for (auto& t : topos) {
                if (t.activo) {
                    t.temporizador += dt;

                    if (t.temporizador >= t.tiempoVisible) {
                        if (t.tipo != 2) vidas--;
                        t.activo = false;
                    }
                }
            }
        }

        window.clear();

        if (estado == INICIO) {
            window.draw(fondoMenu);

            sf::RectangleShape capa(sf::Vector2f(1080, 720));
            capa.setFillColor(sf::Color(0, 0, 0, 80));
            window.draw(capa);

            sf::Text titulo(font, "TOPO MANIA PRO", 60);
            titulo.setFillColor(sf::Color::White);
            titulo.setOutlineThickness(5);
            titulo.setOutlineColor(sf::Color::Black);
            titulo.setPosition(sf::Vector2f(295, 100));
            window.draw(titulo);

            sf::Text texto(font, "Presiona ENTER para iniciar", 34);
            texto.setFillColor(sf::Color::Yellow);
            texto.setOutlineThickness(4);
            texto.setOutlineColor(sf::Color::Black);
            texto.setPosition(sf::Vector2f(340, 330));
            window.draw(texto);

            sf::Text controles(font, "Controles: 1, 2, 3 y 4 para golpear | ESC para salir", 24);
            controles.setFillColor(sf::Color::White);
            controles.setOutlineThickness(3);
            controles.setOutlineColor(sf::Color::Black);
            controles.setPosition(sf::Vector2f(215, 400));
            window.draw(controles);
        }

        else {
            window.draw(fondoJuego);

            sf::RectangleShape barra(sf::Vector2f(1080, 90));
            barra.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(barra);

            sf::Text titulo(font, "TOPO MANIA PRO", 36);
            titulo.setFillColor(sf::Color::White);
            titulo.setPosition(sf::Vector2f(30, 24));
            window.draw(titulo);

            sf::Text datos(font, "", 26);
            datos.setFillColor(sf::Color::White);
            datos.setString(
                "Puntaje: " + std::to_string(puntaje) +
                "   Vidas: " + std::to_string(vidas) +
                "   Tiempo: " + std::to_string((int)tiempo)
            );
            datos.setPosition(sf::Vector2f(570, 30));
            window.draw(datos);

            for (int i = 0; i < totalTopos; i++) {
                sf::Vector2f pos = topos[i].posicion;

                sf::Text numero(font, std::to_string(i + 1), 38);
                numero.setFillColor(sf::Color::White);
                numero.setOutlineThickness(3);
                numero.setOutlineColor(sf::Color::Black);
                numero.setPosition(sf::Vector2f(pos.x - 10, pos.y - 125));
                window.draw(numero);

                sf::CircleShape sombra(75);
                sombra.setOrigin(sf::Vector2f(75, 75));
                sombra.setScale(sf::Vector2f(1.25f, 0.45f));
                sombra.setPosition(sf::Vector2f(pos.x + 8, pos.y + 35));
                sombra.setFillColor(sf::Color(0, 0, 0, 120));
                window.draw(sombra);

                sf::CircleShape agujero(70);
                agujero.setOrigin(sf::Vector2f(70, 70));
                agujero.setScale(sf::Vector2f(1.2f, 0.5f));
                agujero.setPosition(sf::Vector2f(pos.x, pos.y + 30));
                agujero.setFillColor(sf::Color(55, 30, 12));
                window.draw(agujero);

                if (topos[i].activo && estado == JUGANDO) {
                    sf::Color colorTopo;

                    if (topos[i].tipo == 0) colorTopo = sf::Color(155, 85, 45);
                    else if (topos[i].tipo == 1) colorTopo = sf::Color(120, 120, 120);
                    else colorTopo = sf::Color(220, 40, 40);

                    sf::CircleShape cuerpo(48);
                    cuerpo.setOrigin(sf::Vector2f(48, 48));
                    cuerpo.setPosition(sf::Vector2f(pos.x, pos.y - 10));
                    cuerpo.setFillColor(colorTopo);
                    cuerpo.setOutlineThickness(4);
                    cuerpo.setOutlineColor(sf::Color(80, 45, 25));
                    window.draw(cuerpo);

                    sf::CircleShape panza(24);
                    panza.setOrigin(sf::Vector2f(24, 24));
                    panza.setPosition(sf::Vector2f(pos.x, pos.y + 10));
                    panza.setFillColor(sf::Color(220, 160, 110, 180));
                    window.draw(panza);

                    sf::CircleShape ojo1(7);
                    ojo1.setOrigin(sf::Vector2f(7, 7));
                    ojo1.setPosition(sf::Vector2f(pos.x - 17, pos.y - 28));
                    ojo1.setFillColor(sf::Color::Black);
                    window.draw(ojo1);

                    sf::CircleShape ojo2(7);
                    ojo2.setOrigin(sf::Vector2f(7, 7));
                    ojo2.setPosition(sf::Vector2f(pos.x + 17, pos.y - 28));
                    ojo2.setFillColor(sf::Color::Black);
                    window.draw(ojo2);

                    sf::CircleShape nariz(9);
                    nariz.setOrigin(sf::Vector2f(9, 9));
                    nariz.setPosition(sf::Vector2f(pos.x, pos.y - 7));
                    nariz.setFillColor(sf::Color(255, 150, 180));
                    window.draw(nariz);

                    if (topos[i].tipo == 1) {
                        sf::RectangleShape casco(sf::Vector2f(84, 26));
                        casco.setOrigin(sf::Vector2f(42, 13));
                        casco.setPosition(sf::Vector2f(pos.x, pos.y - 58));
                        casco.setFillColor(sf::Color(30, 70, 200));
                        window.draw(casco);

                        sf::Text txt(font, "CASCO", 13);
                        txt.setFillColor(sf::Color::White);
                        txt.setPosition(sf::Vector2f(pos.x - 29, pos.y - 67));
                        window.draw(txt);
                    }

                    if (topos[i].tipo == 2) {
                        sf::Text bomba(font, "!", 50);
                        bomba.setFillColor(sf::Color::Yellow);
                        bomba.setPosition(sf::Vector2f(pos.x - 8, pos.y - 82));
                        window.draw(bomba);

                        sf::Text txtBomba(font, "BOMBA", 13);
                        txtBomba.setFillColor(sf::Color::White);
                        txtBomba.setPosition(sf::Vector2f(pos.x - 28, pos.y + 38));
                        window.draw(txtBomba);
                    }
                }
            }

            sf::RectangleShape barraInfo(sf::Vector2f(820, 55));
            barraInfo.setPosition(sf::Vector2f(25, 640));
            barraInfo.setFillColor(sf::Color(255, 255, 255, 190));
            barraInfo.setOutlineThickness(3);
            barraInfo.setOutlineColor(sf::Color::Black);
            window.draw(barraInfo);

            sf::Text ayuda(font, "Presiona 1, 2, 3 o 4 para golpear el agujero correspondiente", 20);
            ayuda.setFillColor(sf::Color::Black);
            ayuda.setPosition(sf::Vector2f(45, 655));
            window.draw(ayuda);
        }

        if (estado == GAME_OVER) {
            sf::RectangleShape capa(sf::Vector2f(1080, 720));
            capa.setFillColor(sf::Color(0, 0, 0, 180));
            window.draw(capa);

            sf::Text fin(font, "JUEGO TERMINADO", 56);
            fin.setFillColor(sf::Color::White);
            fin.setOutlineThickness(3);
            fin.setOutlineColor(sf::Color::Black);
            fin.setPosition(sf::Vector2f(295, 240));
            window.draw(fin);

            sf::Text final(font, "Puntaje final: " + std::to_string(puntaje), 36);
            final.setFillColor(sf::Color::Yellow);
            final.setOutlineThickness(3);
            final.setOutlineColor(sf::Color::Black);
            final.setPosition(sf::Vector2f(395, 320));
            window.draw(final);

            sf::Text volver(font, "Presiona ENTER para volver al inicio", 28);
            volver.setFillColor(sf::Color::White);
            volver.setOutlineThickness(3);
            volver.setOutlineColor(sf::Color::Black);
            volver.setPosition(sf::Vector2f(330, 390));
            window.draw(volver);
        }

        window.display();
    }

    return 0;
}