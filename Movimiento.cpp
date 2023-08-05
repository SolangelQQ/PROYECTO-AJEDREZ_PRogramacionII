//
// Created by solangel quiroga on 12/11/22.
//

#include "Movimiento.h"

// Constructor Vacio.
Movimiento::Movimiento() {
    cursor = -1;
    secuencia = {};
}

// Constructor acepta una secuencia de movimiento.
Movimiento::Movimiento(vector< pair<int, int> > nuevaSecuencia) {
    cursor = -1;
    secuencia = nuevaSecuencia;
}

// Devuelve el primer movimiento en la secuencia de movimientos.
pair<int, int> Movimiento::getPrimero() {
    cursor = 0;
    return secuencia[cursor];
}

// Devuelve el siguiente movimiento en la secuencia de movimientos en funci�n de la posici�n del cursor.
pair<int, int> Movimiento::getSiguiente() {
    ++cursor;
    return secuencia[cursor];
}

// Comprueba si todav�a hay movimientos adicionales en la secuencia.
bool Movimiento::tieneOtroMovimiento() {
    return (cursor + 1) < (int)secuencia.size();
}

// Devuelve la secuencia de movimiento.
vector< pair<int, int> > Movimiento::getSecuenciaDeMovimiento() const {
    return secuencia;
}

// Devuelve el n�mero de movimientos en la secuencia.
int Movimiento::getLongitudDeSecuenciaDeMovimiento() {
    return secuencia.size();
}

// Operator de Igualdad de comparaci�n.
bool Movimiento::operator==(const Movimiento& otroMovimientoDeSecuencia) const {
    return this->getSecuenciaDeMovimiento() == otroMovimientoDeSecuencia.getSecuenciaDeMovimiento();
}

// Operator de no Igualdad de comparaci�n.
bool Movimiento::operator!=(const Movimiento& otroMovimientoDeSecuencia) const {
    return this->getSecuenciaDeMovimiento() != otroMovimientoDeSecuencia.getSecuenciaDeMovimiento();
}
