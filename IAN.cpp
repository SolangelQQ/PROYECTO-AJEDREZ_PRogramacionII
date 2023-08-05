//
// Created by solangel quiroga on 12/11/22.
//

#include "IAN.h"

// Constructor.
IAN::IAN(Color colour,shared_ptr<TableroJuego> newTablero, string nombre): Jugador(colour, nombre), copia_tablero(newTablero)
{

}

// Esto siempre deber�a devolver falso ya que no es Humano.
bool IAN::esHumano() {
    return false;
}

// Obtiene el conjunto v�lido de secuencias de movimiento para el IAN y elige un movimiento
// al azar(esta no es una IA inteligente, pero por lo general solo hay una peque�a cantidad
// de secuencias de movimiento v�lidas en cualquier punto dado en el tiempo).
Movimiento IAN::getMovimiento() {

    // Consigue todos los movimientos posibles.
    vector<Movimiento> todosLosMovimientosValidos = copia_tablero->getTodosLosMovimientosValidos(DevolverColor());

    // Genera lo aleatorio.
    random_device recursoAleatorio;
    mt19937 generator(recursoAleatorio());
    uniform_int_distribution<> distribution(0, todosLosMovimientosValidos.size() - 1);

    return todosLosMovimientosValidos.at(distribution(generator));
}
