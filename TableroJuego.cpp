//
// Created by solangel quiroga on 12/11/22.
//

#include "TableroJuego.h"


// M�TODOS P�BLICOS
// Constructor
TableroJuego::TableroJuego() {
    fichasNegras = 12;
    fichasBlancas = 12;

    // Configurar piezas negras del juego.
    for (auto fila = 0; fila < 3; ++fila) {

        // Se usa para alternar entre fichas claras y oscuras en el tablero.
        bool colocarFicha = fila % 2 != 0;

        for (auto columna = 0; columna < 8; ++columna) {
            if (colocarFicha) {
                tablero[fila][columna] = make_shared<Ficha>(Ficha(Color::NEGRO));
            }
            colocarFicha = !colocarFicha;
        }
    }

    // Configurar piezas blancas del juego.
    for (auto fila = 5; fila < 8; ++fila) {

        // Se usa para alternar entre fichas claras y oscuras en el tablero.
        bool colocarFicha = fila % 2 != 0;

        for (auto columna = 0; columna < 8; ++columna) {
            if (colocarFicha) {
                tablero[fila][columna] = make_shared<Ficha>(Ficha(Color::BLANCO));
            }
            colocarFicha = !colocarFicha;
        }
    }
}

// Constructor de asignaciones.
TableroJuego::TableroJuego(TableroJuego* obj) {

    fichasNegras = obj->fichasNegras;
    fichasBlancas = obj->fichasBlancas;

    for (auto fila = 0; fila < 8; ++fila) {
        for (auto columna = 0; columna < 8; ++columna) {
            if (obj->getFicha(fila, columna) != nullptr) {
                Color copiarColor = (obj->getFicha(fila, columna))->getColor();
                TipoDeFicha copiarTipo = (obj->getFicha(fila, columna))->getTipo();
                tablero[fila][columna] = make_shared<Ficha>(copiarTipo, copiarColor);
            }
        }
    }
}

// Constructor para copias.
TableroJuego::TableroJuego(const TableroJuego& obj) {

    fichasNegras = obj.fichasNegras;
    fichasBlancas = obj.fichasBlancas;

    for (auto fila = 0; fila < 8; ++fila) {
        for (auto columna = 0; columna < 8; ++columna) {
            if (obj.getFicha(fila, columna) != nullptr) {
                Color copiarColor = obj.getFicha(fila, columna)->getColor();
                TipoDeFicha copiarTipo = obj.getFicha(fila, columna)->getTipo();
                tablero[fila][columna] = make_shared<Ficha>(copiarTipo, copiarColor);
            }
        }
    }
}

// Destructor.
TableroJuego::~TableroJuego() {

    for (auto fila : tablero) {
        for (auto puntoCuadricula : fila) {
            puntoCuadricula = nullptr;
        }
    }
}

// Obtiene el objeto Ficha directamente usando coordenadas.
shared_ptr<Ficha> TableroJuego::getFicha(int fila, int columna) const {

    if (fila < 0 or 7 < fila or columna < 0 or 7 < columna) {
        return nullptr;
    }
    return tablero[fila][columna];
}

// Obtiene objeto Ficha indirectamente a partir de coordenadas en objeto puntoCuadricula.
shared_ptr<Ficha> TableroJuego::getFicha(pair<int, int> puntoCuadricula) const {
    return getFicha(puntoCuadricula.first, puntoCuadricula.second);
}

// Comprueba si existe un objeto Ficha en las coordenadas del objeto puntoCuadricula.
bool TableroJuego::estaVacio(pair<int, int> puntoCuadricula) {

    return tablero[puntoCuadricula.first][puntoCuadricula.second] == nullptr;
}

// Comprueba si las coordenadas especificadas por el objeto puntoCuadricula son v�lidas para el Tablero.
bool TableroJuego::entreLimites(pair<int, int> puntoCuadricula) {

    const int limiteInferior = 0;
    const int esValidoElSuperior = 7;

    bool esValidoElInferior = (puntoCuadricula.first >= limiteInferior)
                              and (puntoCuadricula.second >= limiteInferior);
    bool isValidUp = (puntoCuadricula.first <= esValidoElSuperior)
                     and (puntoCuadricula.second <= esValidoElSuperior);

    return esValidoElInferior and isValidUp;
}

// Remueve una Pieza del Tablero de Juego en las coordenadas especificadas en el objeto
// (deCasilla) y coloca la pieza en las coordenadas especificadas en el objeto (aCasilla).
void TableroJuego::moverFicha(pair<int, int> deCasilla, pair<int, int> aCasilla) {

    tablero[aCasilla.first][aCasilla.second] = make_shared<Ficha>(*(getFicha(deCasilla)));
    tablero[deCasilla.first][deCasilla.second] = nullptr;

    if (aCasilla.first == 0 and getFicha(aCasilla)->getColor() == Color::BLANCO) {
        getFicha(aCasilla)->setTipo(TipoDeFicha::REINA);
    }

    if (aCasilla.first == 7 and getFicha(aCasilla)->getColor() == Color::NEGRO) {
        getFicha(aCasilla)->setTipo(TipoDeFicha::REINA);
    }
}

// Extrae una Ficha del TableroJuego en las coordenadas especificadas en el objeto puntoCuadricula.
void TableroJuego::removerFicha(pair<int, int> puntoCuadricula) {

    if (getFicha(puntoCuadricula)->getColor() == Color::BLANCO) {
        fichasBlancas -= 1;
    }

    if (getFicha(puntoCuadricula)->getColor() == Color::NEGRO) {
        fichasNegras -= 1;
    }

    tablero[puntoCuadricula.first][puntoCuadricula.second] = nullptr;
}

// Devuelve el n�mero de Fichas que tiene un jugador en el tablero.
bool TableroJuego::fichasRestantes(Color color) {

    return (color == Color::NEGRO) ? (fichasNegras > 0) : (fichasBlancas > 0);
}

// Comprueba los movimientos v�lidos entre dos fichas como parte de una condici�n de victoria para el juego.
bool TableroJuego::movimientosRestantes(Color color) {

    bool resultado = false;
    for (auto fila = 0; fila < 8; fila++) {
        for (auto columna = 0; columna < 8; ++columna) {
            auto ficha = getFicha(fila, columna);

            if (ficha == nullptr || ficha->getColor() != color) {
                continue;
            }

            if ((ficha->getTipo() == TipoDeFicha::REINA or color == Color::BLANCO)
                and (esSaltoValido(ficha,
                                   make_pair(fila, columna),
                                   make_pair(fila - 2, columna + 2))
                     or esSaltoValido(ficha,
                                      make_pair(fila, columna),
                                      make_pair(fila - 2, columna - 2))
                     or esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila - 1, columna + 1))
                     or esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila - 1, columna - 1)))) {
                resultado = true;
            }

            if ((ficha->getTipo() == TipoDeFicha::REINA or color == Color::NEGRO)
                and (esSaltoValido(ficha,
                                   make_pair(fila, columna),
                                   make_pair(fila + 2, columna + 2))
                     or esSaltoValido(ficha,
                                      make_pair(fila, columna),
                                      make_pair(fila + 2, columna - 2))
                     or esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila + 1, columna + 1))
                     or esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila + 1, columna - 1)))) {
                resultado = true;
            }
        }
    }
    return resultado;
}

// Comprueba los movimientos de cambio validos entre dos casillas adyacentes en diagonal.
bool TableroJuego::esCambioValido(shared_ptr<Ficha> ficha, pair<int, int> deCasilla, pair<int, int> aCasilla) {

    if (ficha == nullptr
        or (not entreLimites(aCasilla))
        or getFicha(aCasilla) != nullptr) {
        return false;
    }

    if ((ficha->getTipo() == TipoDeFicha::REINA
         or ficha->getColor() == Color::BLANCO)
        and (aCasilla.first - deCasilla.first == -1)
        and (abs(aCasilla.second - deCasilla.second) == 1)) {

        return true;
    }

    if ((ficha->getTipo() == TipoDeFicha::REINA
         or ficha->getColor() == Color::NEGRO)
        and (aCasilla.first - deCasilla.first == 1)
        and (abs(aCasilla.second - deCasilla.second) == 1)) {
        return true;
    }
    return false;
}

// Comprueba los saltos diagonales legales entre dos casillas.
bool TableroJuego::esSaltoValido(shared_ptr<Ficha> ficha, pair<int, int> deCasilla, pair<int, int> aCasilla) {

    if (ficha == nullptr
        or (not entreLimites(aCasilla))
        or (getFicha(aCasilla) != nullptr)) {

        return false;
    }

    if ((ficha->getTipo() == TipoDeFicha::REINA
         or ficha->getColor() == Color::BLANCO)
        and (aCasilla.first - deCasilla.first == -2)
        and (abs(aCasilla.second - deCasilla.second) == 2)) {

        auto saltoRealizado = getFicha((aCasilla.first + 1),
                                       (aCasilla.second + deCasilla.second) / 2);
        return (saltoRealizado != nullptr) and (saltoRealizado->getColor() != ficha->getColor());
    }

    if ((ficha->getTipo() == TipoDeFicha::REINA
         or ficha->getColor() == Color::NEGRO)
        and (aCasilla.first - deCasilla.first == 2)
        and (abs(aCasilla.second - deCasilla.second) == 2)) {

        auto saltoRealizado = getFicha((aCasilla.first - 1),
                                       (aCasilla.second + deCasilla.second) / 2);
        return (saltoRealizado != nullptr) and (saltoRealizado->getColor() != ficha->getColor());
    }
    return false;
}

// Verifica los saltos diagonales legales disponibles (no se puede hacer cambio de Movimiento si hay un salto disponible).
bool TableroJuego::saltosDisponibles(Color color) {

    for (auto fila = 0; fila < 8; ++fila) {
        for (auto columna = 0; columna < 8; ++columna) {

            auto ficha = tablero[fila][columna];
            if (ficha == nullptr or ficha->getColor() != color) {
                continue;
            }

            if ((ficha->getTipo() == TipoDeFicha::REINA or color == Color::BLANCO)
                and (esSaltoValido(ficha,
                                   make_pair(fila, columna),
                                   make_pair(fila - 2, columna + 2))
                     or esSaltoValido(ficha,
                                      make_pair(fila, columna),
                                      make_pair(fila - 2, columna - 2)))) {
                //color == Color::BLANCO

                return true;
            }

            if ((ficha->getTipo() == TipoDeFicha::REINA or color == Color::NEGRO)
                and (esSaltoValido(ficha,
                                   make_pair(fila, columna),
                                   make_pair(fila + 2, columna + 2))
                     or esSaltoValido(ficha,
                                      make_pair(fila, columna),
                                      make_pair(fila + 2, columna - 2)))) {

                return true;
            }
        }
    }

    return false;
}

// Un m�todo recursivo que busca otros Movimientos de salto que se pueden agregar a la lista actual de
// Movimientos. Si no se encuentran saltos adicionales, la secuencia de salto actual se agrega a un vector que almacena posibles secuencias de Movimiento.
//Este m�todo probablemente deber�a dividirse en algunos otros que son m�s cortos y se repiten menos.
void TableroJuego::getSaltosMultiples(shared_ptr<Ficha> ficha, vector<pair<int, int>> sSecuencia, vector<Movimiento>& todosLosMovimientosValidos) {
    pair<int, int> deCasilla = sSecuencia.back(); // Punto de inicio del siguiente salto

    bool saltar_arriba_derecha = false;
    bool saltar_arriba_izquierda = false;

    // Comprueba los Movimientos de salto subiendo en el tablero (hacia el jugador 1).
    if ((ficha->getTipo() == TipoDeFicha::REINA) or (ficha->getColor() == Color::BLANCO)) {

        pair<int, int> aCasilla = make_pair(deCasilla.first - 2, deCasilla.second + 2);

        if (esSaltoValido(ficha, deCasilla, aCasilla)
            and (aCasilla != *(sSecuencia.end() - 2))
            and noTieneMovimientosRepetidos(sSecuencia, aCasilla)) {

            auto newSSecuencia = sSecuencia;
            newSSecuencia.emplace_back(aCasilla);
            getSaltosMultiples(ficha, newSSecuencia, todosLosMovimientosValidos);
            saltar_arriba_derecha = true;
        }

        aCasilla = make_pair(deCasilla.first - 2, deCasilla.second - 2);
        if (esSaltoValido(ficha, deCasilla, aCasilla)
            and (aCasilla != *(sSecuencia.end() - 2))
            and noTieneMovimientosRepetidos(sSecuencia, aCasilla)) {

            auto newSSecuencia = sSecuencia;
            newSSecuencia.emplace_back(aCasilla);
            getSaltosMultiples(ficha, newSSecuencia, todosLosMovimientosValidos);
            saltar_arriba_izquierda = true;
        }

        if ((ficha->getTipo() != TipoDeFicha::REINA)
            and (not saltar_arriba_derecha)
            and (not saltar_arriba_izquierda)) {

            todosLosMovimientosValidos.emplace_back(Movimiento(sSecuencia));
        }
    }

    bool saltar_abajo_derecha = false;
    bool saltar_abajo_izquierda = false;

    // Checks for jump Movimientos going down on the tablero (towards player 2)
    if ((ficha->getTipo() == TipoDeFicha::REINA)
        or (ficha->getColor() == Color::NEGRO)) {

        auto aCasilla = make_pair(deCasilla.first + 2, deCasilla.second + 2);

        if (esSaltoValido(ficha, deCasilla, aCasilla)
            and (aCasilla != *(sSecuencia.end() - 2))
            and noTieneMovimientosRepetidos(sSecuencia, aCasilla)) {

            auto newSSecuencia = sSecuencia;
            newSSecuencia.emplace_back(aCasilla);
            getSaltosMultiples(ficha, newSSecuencia, todosLosMovimientosValidos);
            saltar_abajo_derecha = true;
        }

        aCasilla = make_pair(deCasilla.first + 2, deCasilla.second - 2);
        if (esSaltoValido(ficha, deCasilla, aCasilla)
            and (aCasilla != *(sSecuencia.end() - 2))
            and noTieneMovimientosRepetidos(sSecuencia, aCasilla)) {

            auto newSSecuencia = sSecuencia;
            newSSecuencia.emplace_back(aCasilla);
            getSaltosMultiples(ficha, newSSecuencia, todosLosMovimientosValidos);
            saltar_abajo_izquierda = true;
        }

        if ((ficha->getTipo() != TipoDeFicha::REINA)
            and (not saltar_abajo_derecha)
            and (not saltar_abajo_izquierda)) {

            todosLosMovimientosValidos.emplace_back(Movimiento(sSecuencia));
        }
    }

    if ((ficha->getTipo() == TipoDeFicha::REINA)
        and (not saltar_arriba_derecha)
        and (not saltar_arriba_izquierda)
        and (not saltar_abajo_derecha)
        and (not saltar_abajo_izquierda)) {

        todosLosMovimientosValidos.emplace_back(Movimiento(sSecuencia));
    }
}

// Busca y devuelve todos los conjuntos posibles de secuencias de Movimiento de
// cada Ficha para el Color dado.
vector<Movimiento> TableroJuego::getTodosLosMovimientosValidos(Color color) {

    vector<Movimiento> todosLosMovimientosValidos;
    vector<pair<int, int>> secuenciaDeMovimiento;

    for (auto fila = 0; fila < 8; ++fila) {
        for (auto columna = 0; columna < 8; ++columna) {

            shared_ptr<Ficha> ficha = getFicha(fila, columna);

            // Comprueba si la ficha esta vacia o la casilla del jugador es incorrecta.
            if (ficha == nullptr or ficha->getColor() != color) {
                continue;
            }

            // Comprueba si hay movimientos legales de salto hacia arriba.
            if (ficha->getTipo() == TipoDeFicha::REINA
                or ficha->getColor() == Color::BLANCO) {

                secuenciaDeMovimiento = { make_pair(fila, columna), make_pair(fila - 2, columna + 2) };
                if (esSaltoValido(ficha, secuenciaDeMovimiento[0], secuenciaDeMovimiento[1])) {
                    getSaltosMultiples(ficha, secuenciaDeMovimiento, todosLosMovimientosValidos);
                }

                secuenciaDeMovimiento = { make_pair(fila, columna), make_pair(fila - 2, columna - 2) };
                if (esSaltoValido(ficha, secuenciaDeMovimiento[0], secuenciaDeMovimiento[1])) {
                    getSaltosMultiples(ficha, secuenciaDeMovimiento, todosLosMovimientosValidos);
                }
            }

            // Verifica los movimientos v�lidos de salto hacia abajo.
            if (ficha->getTipo() == TipoDeFicha::REINA
                or ficha->getColor() == Color::NEGRO) {

                secuenciaDeMovimiento = { make_pair(fila, columna), make_pair(fila + 2, columna + 2) };
                if (esSaltoValido(ficha, secuenciaDeMovimiento[0], secuenciaDeMovimiento[1])) {
                    getSaltosMultiples(ficha, secuenciaDeMovimiento, todosLosMovimientosValidos);
                }

                secuenciaDeMovimiento = { make_pair(fila, columna), make_pair(fila + 2, columna - 2) };
                if (esSaltoValido(ficha, secuenciaDeMovimiento[0], secuenciaDeMovimiento[1])) {
                    getSaltosMultiples(ficha, secuenciaDeMovimiento, todosLosMovimientosValidos);
                }
            }
        }
    }

    // Si no hay Movimientos de salto v�lidos, se intenta encontrar Movimientos de cambio de posici�n v�lidos.
    if (todosLosMovimientosValidos.empty()) {
        for (auto fila = 0; fila < 8; ++fila) {
            for (auto columna = 0; columna < 8; ++columna) {

                shared_ptr<Ficha> ficha = getFicha(fila, columna);

                // Comprueba si la casilla est� vac�a o la pieza del jugador es incorrecta.
                if (ficha == nullptr or ficha->getColor() != color) {
                    continue;
                }

                // Comprueba si hay movimientos de deslizamiento hacia arriba v�lidos.
                if (ficha->getTipo() == TipoDeFicha::REINA
                    or ficha->getColor() == Color::BLANCO) {

                    if (esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila - 1, columna + 1))) {

                        Movimiento abajoDerecha = Movimiento({make_pair(fila, columna), make_pair(fila - 1, columna + 1) });
                        todosLosMovimientosValidos.emplace_back(abajoDerecha);
                    }

                    if (esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila - 1, columna - 1))) {

                        Movimiento abajoIzquierda = Movimiento({make_pair(fila, columna), make_pair(fila - 1, columna - 1) });
                        todosLosMovimientosValidos.emplace_back(abajoIzquierda);
                    }
                }

                // Verifique los Movimientos v�lidos de cambio de posici�n hacia abajo.
                if (ficha->getTipo() == TipoDeFicha::REINA or ficha->getColor() == Color::NEGRO) {

                    if (esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila + 1, columna + 1))) {

                        Movimiento abajoIzquierda = Movimiento({make_pair(fila, columna), make_pair(fila + 1, columna + 1) });
                        todosLosMovimientosValidos.emplace_back(abajoIzquierda);
                    }

                    if (esCambioValido(ficha,
                                       make_pair(fila, columna),
                                       make_pair(fila + 1, columna - 1))) {

                        Movimiento abajoIzquierda = Movimiento({make_pair(fila    , columna), make_pair(fila + 1, columna - 1) });
                        todosLosMovimientosValidos.emplace_back(abajoIzquierda);
                    }
                }
            }
        }
    }
    return todosLosMovimientosValidos;
}

// Operador de Asignaci�n
TableroJuego& TableroJuego::operator=(TableroJuego newtablero) {

    swap(fichasNegras, newtablero.fichasNegras);
    swap(fichasBlancas, newtablero.fichasBlancas);
    swap(tablero, newtablero.tablero);
    return *this;
}

// M�TODOS PRIVADOS:
// Comprueba la secuencia de Movimiento para conjuntos repetidos de Movimientos.
// Esto asegura que el objeto Ficha no quede atrapado creando una secuencia infinita
// de saltos en caso de que el camino de las secuencias de salto se cruce.
bool TableroJuego::noTieneMovimientosRepetidos(vector<pair<int, int>>& secuencia, pair<int, int>& aCasilla) {

    bool hasNoRepeatMovimientos = true;

    for (int i = 1; i < ((int)secuencia.size() - 1); ++i) {
        if (secuencia.at(i) == secuencia.back()
            and (secuencia.at(i - 1) == aCasilla
                 or secuencia.at(i + 1) == aCasilla)) {

            hasNoRepeatMovimientos = false;
            break;
        }
    }

    return hasNoRepeatMovimientos;
}