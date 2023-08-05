//
// Created by solangel quiroga on 12/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_TABLEROJUEGO_H
#define PROYECTO_PROGRAMACION2_TABLEROJUEGO_H

#include <iostream>
#include <cmath>      // Librer�a para abs()
#include <memory>     // Librer�a parashared_ptr y make_shared
#include <vector>
#include <utility>    // Librer�a para pair y make_pair
#include <array>

#include "Color.h"
#include "TableroJuego.h"
#include "Movimiento.h"
#include "Ficha.h"
#include "TipoDeFicha.h"

using namespace std;

class TableroJuego {
private:
    bool noTieneMovimientosRepetidos(vector<pair<int, int>>& secuencia, pair<int, int>& finalizar);
    int fichasNegras;
    int fichasBlancas;
    array<array<shared_ptr<Ficha>, 8>, 8> tablero;
public:
    TableroJuego();
    TableroJuego(TableroJuego* obj);
    TableroJuego(const TableroJuego& obj);
    ~TableroJuego();

    shared_ptr<Ficha> getFicha(int fila, int columna) const;
    shared_ptr<Ficha> getFicha(pair<int, int> puntoCuadricula) const;
    bool estaVacio(pair<int, int> puntoCuadricula);

    bool entreLimites(pair<int, int> puntoCuadricula);
    void moverFicha(pair<int, int> deCasilla, pair<int, int> aCasilla);
    void removerFicha(pair<int, int> puntoCuadricula);

    bool fichasRestantes(Color color);
    bool movimientosRestantes(Color color);

    bool esCambioValido(shared_ptr<Ficha> ficha, pair<int, int> deCasilla, pair<int, int> aCasilla);
    bool esSaltoValido(shared_ptr<Ficha> Ficha, pair<int, int> deCasilla, pair<int, int> aCasilla);
    bool saltosDisponibles(Color color);
    void getSaltosMultiples(shared_ptr<Ficha> ficha,
                            vector<pair<int, int>> sSecuencia,
                            vector<Movimiento>& todosLosMovimientosValidos);
    vector<Movimiento> getTodosLosMovimientosValidos(Color color);

    TableroJuego& operator=(TableroJuego newtablero);

};

#endif //PROYECTO_PROGRAMACION2_TABLEROJUEGO_H
