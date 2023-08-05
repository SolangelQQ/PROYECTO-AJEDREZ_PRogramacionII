//
// Created by solangel quiroga on 12/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_FICHA_H
#define PROYECTO_PROGRAMACION2_FICHA_H
#include <iostream>
#include <string>

#include "Color.h"
#include "TipoDeFicha.h"

using namespace std;

class Ficha {
private:
    TipoDeFicha tipo;
    Color color;

    static const string RED;
    static const string WHITE;
    static const string RESET_STREAM;

    static const string NORMAL;
    static const string REINA;
public:
    Ficha(TipoDeFicha newTipo, Color newColor);
    Ficha(Color newColor);
    ~Ficha();

    Color getColor() const;
    TipoDeFicha getTipo() const;
    void setTipo(TipoDeFicha tipo);

    // Una funci�n friend es una funci�n que no es miembro de una clase
    // pero tiene acceso a los miembros privados y protegidos de la clase.
    friend ostream& operator<<(ostream& salida, const Ficha& ficha);


};

#endif //PROYECTO_PROGRAMACION2_FICHA_H
