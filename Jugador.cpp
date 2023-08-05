//
// Created by solangel quiroga on 30/11/22.
//

#include "Jugador.h"

// M�TODOS P�BLICOS:
// Constructor
Jugador::Jugador(Color color, string nombre) {
    this->color = color;
    this->nombre = nombre;
    this->fichasComidas = 0;
}

// Devuelve el color de la ficha de juego utilizada por el jugador.
Color Jugador::DevolverColor() {
    return color;
}
string Jugador::DevolverNombre() {
    return nombre;
}
int Jugador::DevolverFichasComidas() {
    return fichasComidas;
}
void Jugador::IncrementarFichasComidas() {
    fichasComidas++;
}
