//
// Created by solangel quiroga on 30/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_CONTROLADOR_H
#define PROYECTO_PROGRAMACION2_CONTROLADOR_H
#include <iostream>
#include <algorithm>  // La libreria <algorithm> define una colección de funciones especialmente diseñadas para usarse en rangos de elementos en nuestro caso transform.
#include <map>        // Libreria para utilizar map: Los mapas son contenedores asociativos que almacenan elementos formados por una combinación de un valor clave y un valor mapeado, siguiendo un orden específico.
#include <memory>     // Libreria para make_shared, dynamic_pointer_cast
#include <string>     // Liberia para string y tolower.
#include <vector>     // Libería para vectores.
#include <utility>    // Libería de encabezado que contiene utilidades en dominios no relacionados.
//make_shared: Asigna y construye un objeto pasando argumentos a su constructor y devuelve un objeto de tipo shared_ptr<Objeto> que posee y almacena un puntero a él.
//dynamic_pointer_cast: Es un reparto dinámico de shared_ptr.
//                      Devuelve una copia del puntero de pila del tipo adecuado con su puntero almacenado convertido dinámicamente de Objeto1* a Objeto2*.
//tolower: Convertir letra mayúscula a minúscula
//pair: El tipo de variable pair permite almacenar y mantener vincluados un par de valores o dos valores.
using namespace std;

#include "Color.h"
#include "TableroJuego.h"
#include "ErrorDelJuego.h"
#include "ModoDeJuego.h"
#include "InterfazJuego.h"
#include "Jugador.h"
#include "IAN.h"
#include "JugadorHumano.h"

class Controlador {
private:

    //shared_ptr es un puntero inteligente que retiene la propiedad
    // compartida de un objeto a través de un puntero.
    shared_ptr<TableroJuego> tablero;
    shared_ptr<InterfazJuego> interfazJuego;
    shared_ptr<Jugador> jugador1;
    shared_ptr<Jugador> jugador2;
    shared_ptr<Jugador> turnoActual;
    // En shared_ptr<V> la V  puede ser un tipo de función:
    // en este caso maneja un puntero a función, en lugar de un puntero a objeto.
    // Esto a veces se usa para mantener cargada una biblioteca dinámica o un complemento
    // siempre que se haga referencia a cualquiera de sus funciones.


    ModoDeJuego DevolverModoDeJuego();
    void getValidarEntrada();
    string getEntrada();

    bool movimientoValido(Movimiento jugar, bool forzarSalto);
    void realizarMovimiento(Movimiento jugar);

    bool elJuegoTieneMasTurnos();
    bool VolverAJugar();
public:
    Controlador();
    void IniciarJuego();
    void Jugar(bool);
    bool DevolverOpcionForzarSalto(bool);
};

#endif //PROYECTO_PROGRAMACION2_CONTROLADOR_H
