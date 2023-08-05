//
// Created by solangel quiroga on 12/11/22.
//
#include "Ficha.h"

// M�TODOS P�BLICOS:
// Constructor para fihas normales.
Ficha::Ficha(Color newColor) {
    color = newColor;
    tipo = TipoDeFicha::NORMAL;
}

// Constructor para cualquier ficha de juego.
Ficha::Ficha(TipoDeFicha newTipo, Color newColor) {
    color = newColor;
    tipo = newTipo;
}

// Destructor
Ficha::~Ficha() {

};

// Devuelve el color de la ficha.
Color Ficha::getColor() const {
    return color;
}

// Devuelve el tipo de la ficha (es decir, normal o Reina).
TipoDeFicha Ficha::getTipo() const {
    return tipo;
}

// Cambia el tipo de ficha del juego (por ejemplo, normal => Reina).
void Ficha::setTipo(TipoDeFicha newTipo) {
    tipo = newTipo;
}

// Operador de flujo sobrecargado para permitir la salida de fichas directamente.
ostream& operator<< (ostream& salida, const Ficha& ficha) {
    string token;
    switch (ficha.getColor()) {
        case Color::NEGRO: {
            token = Ficha::RED;
            break;
        }
        case Color::BLANCO: {
            token = Ficha::WHITE;
            break;
        }
    }

    switch (ficha.getTipo()) {
        case TipoDeFicha::NORMAL: {
            token += Ficha::NORMAL;
            break;
        }
        case TipoDeFicha::REINA: {
            token += Ficha::REINA;
            break;
        }
    }

    return salida << token << Ficha::RESET_STREAM;
}

// CONSTANTES PRIVADAS:
// Determina c�mo se renderiza un objeto Ficha cuando sale.
const string Ficha::RED = "\033[1;31;40m";
const string Ficha::WHITE = "\033[1;40m";
const string Ficha::RESET_STREAM = "\033[0m";
const string Ficha::NORMAL = " \u25CF "; //"\u25CF" => c�rculo lleno
const string Ficha::REINA = " \u265B "; //"\u25CB" => c�rculo hueco
