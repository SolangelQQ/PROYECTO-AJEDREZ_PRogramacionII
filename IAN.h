//
// Created by solangel quiroga on 12/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_IAN_H
#define PROYECTO_PROGRAMACION2_IAN_H

#include <iostream>
#include <memory>   // Librer�a para shared_ptr
#include <random>   // Librer�a para mt19937, random_device y uniform_int_distribution
#include <vector>   // Librer�a para vector

#include "Color.h"
#include "TableroJuego.h"
#include "Movimiento.h"
#include "Jugador.h"

using namespace std;

using namespace std;

class IAN : public Jugador {
private:
    shared_ptr<TableroJuego> copia_tablero;

public:
    IAN(Color newColor, shared_ptr<TableroJuego> newTablero, string nombre);

    bool esHumano();
    Movimiento getMovimiento();
};



#endif //PROYECTO_PROGRAMACION2_IAN_H
