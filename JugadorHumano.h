//
// Created by solangel quiroga on 12/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_JUGADORHUMANO_H
#define PROYECTO_PROGRAMACION2_JUGADORHUMANO_H

#include <iostream>
#include <algorithm>  // Librer�a para transform
#include <iostream>
#include <sstream>    // Librer�a para istringstream
#include <string>     // Librer�a para tolower
#include <vector>
#include <utility>    // Librer�a para pair

#include "Color.h"
#include "Movimiento.h"
#include "Jugador.h"

using namespace std;

class JugadorHumano : public Jugador {
private:
    string nombre;
    vector<string> Separador(string linea, char delim);
    string entrada;

public:
    JugadorHumano(Color color, string nombre);

    bool esHumano();
    Movimiento getMovimiento();

    void setEntrada();
    string getEntrada();
    bool tieneEntradaValida();

};



#endif //PROYECTO_PROGRAMACION2_JUGADORHUMANO_H
