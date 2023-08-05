//
// Created by solangel quiroga on 12/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_MOVIMIENTO_H
#define PROYECTO_PROGRAMACION2_MOVIMIENTO_H

#include <iostream>
#include <vector>     // Librer�a para vector
#include <utility>    // Librer�a para pair y make_pair

using namespace std;

class Movimiento {
public:
    Movimiento();
    Movimiento(vector< pair<int, int> > nuevaSecuencia);

    pair<int, int> getPrimero();
    pair<int, int> getSiguiente();
    bool tieneOtroMovimiento();
    vector< pair<int, int> > getSecuenciaDeMovimiento() const;
    int getLongitudDeSecuenciaDeMovimiento();

    bool operator==(const Movimiento& otroMovimientoDeSecuencia) const;
    bool operator!=(const Movimiento& otroMovimientoDeSecuencia) const;

private:
    int cursor;
    vector< pair<int, int> > secuencia;
};

#endif //PROYECTO_PROGRAMACION2_MOVIMIENTO_H
