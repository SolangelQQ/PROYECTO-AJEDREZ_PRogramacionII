//
// Created by solangel quiroga on 30/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_JUGADOR_H
#define PROYECTO_PROGRAMACION2_JUGADOR_H

#include <iostream>

#include "Color.h"
#include "Movimiento.h"

using namespace std;

class Jugador {
private:
    Color color;
    string nombre;
    int fichasComidas;
public:
    Jugador(Color, string);
    Color DevolverColor();
    string DevolverNombre();
    int DevolverFichasComidas();
    void IncrementarFichasComidas();

    virtual bool esHumano() = 0;
    virtual Movimiento getMovimiento() = 0;
};


#endif //PROYECTO_PROGRAMACION2_JUGADOR_H
