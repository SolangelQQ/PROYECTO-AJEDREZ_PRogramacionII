//
// Created by solangel quiroga on 12/11/22.
//

#include "JugadorHumano.h"

// M�TODOS P�BLICOS:
// Constructor.
JugadorHumano::JugadorHumano(Color color, string nombre) : Jugador(color, nombre), entrada("")
{
}

// Esta es la �nica clase que indica verdadero para esta funci�n ya que es Humano el Jugador.
bool JugadorHumano::esHumano() {
    return true;
}

// Verfica la entrada del usuario en busca de coordenadas de cuadr�cula y construye una secuencia de movimientos.
Movimiento JugadorHumano::getMovimiento() {

    if (not tieneEntradaValida()) {
        return Movimiento();
    }

    vector<pair<int, int>> secuencia;
    auto entrada_dividida = Separador(entrada, ' ');

    for (auto const& coordenadas : entrada_dividida) {
        int fila = coordenadas[0] - 'a';
        int columna = coordenadas[1] - '1';
        secuencia.emplace_back(fila, columna);
    }

    return secuencia;
}

// Obtiene la entrada del usuario desde cin y la almacena en el objeto JugadorHumano.
void JugadorHumano::setEntrada() {
    string newEntrada;
    getline(cin, newEntrada);

    // Convierte todas las entradas a min�sculas.
    transform(newEntrada.begin(), newEntrada.end(), newEntrada.begin(), ::tolower);

    entrada = newEntrada;
}

// Recupera la entrada almacenada por el objeto JugadorHumano.
string JugadorHumano::getEntrada() {
    return entrada;
}

// Comprueba si la entrada almacenada por el objeto JugadorHumano es un
// conjunto de coordenadas v�lido o un comando reconocido.
bool JugadorHumano::tieneEntradaValida() {
    if (entrada.length() < 2) {
        return false;
    }

    if (entrada == "q"
        or entrada == "abandonar"
        or entrada == "salir") {
        return true;
    }

    vector<string> entrada_dividida = Separador(entrada, ' ');
    if (entrada_dividida.size() < 2) {
        return false;
    }

    for (auto const& coordenadas : entrada_dividida) {

        if (not ((coordenadas.length() == 2)
                 and (0 <= (coordenadas[0] - 'a'))
                 and (7 >= (coordenadas[0] - 'a'))
                 and (0 <= (coordenadas[1] - '1'))
                 and (7 >= (coordenadas[1] - '1')))) {

            return false;
        }
    }

    return true;
}

// M�TODOS PRIVADOS:
// Comprueba la secuencia de la cadena de entrada en conjuntos individuales de coordenadas.
vector<string> JugadorHumano::Separador(string entrada, char delim) {

    istringstream secuenciaDeEntrada(entrada);
    string newEntrada;
    vector<string> elementos;

    while (getline(secuenciaDeEntrada, newEntrada, delim)) {
        elementos.emplace_back(newEntrada);
    }

    return elementos;
}
