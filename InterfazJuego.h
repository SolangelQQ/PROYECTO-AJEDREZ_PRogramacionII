//
// Created by solangel quiroga on 30/11/22.
//

#ifndef PROYECTO_PROGRAMACION2_INTERFAZJUEGO_H
#define PROYECTO_PROGRAMACION2_INTERFAZJUEGO_H


#include <iostream>
#include <memory>     // Libreria para shared_ptr, make_shared
#include <sstream>    // Libreria para ostringstream, también llamado Flujo de cadena de salida es una Clase de flujo de salida para operar en cadenas.
#include <string>     // Libreria para string
#include <typeinfo>   // Libreria para typeid, Consulta información de un tipo.
//Se utiliza cuando se debe conocer el tipo dinámico de un objeto polimórfico y para la identificación del tipo estático.

#include "TableroJuego.h"
#include "ErrorDelJuego.h"
#include "Jugador.h"

using namespace std;

class InterfazJuego {
private:
    shared_ptr<TableroJuego> tablero;
    shared_ptr<Jugador> jugador1;
    shared_ptr<Jugador> jugador2;
    int numero_turno;
public:
    InterfazJuego();

    void IniciarInterfaz(shared_ptr<TableroJuego> newTablero, shared_ptr<Jugador> newJugador1, shared_ptr<Jugador> newJugador2);

    void MostrarMensajeDeBienvenida();
    void MostrarOpcionesDelJuego();
    void MostrarInstruccionesDelJuego();
    void MostrarIngresarDatos(int);
    void MostrarOpcionForzarSalto();
    void MostrarModoDeJuegoYTurnoActual(bool actualizarTurno, shared_ptr<Jugador>);
    void MostrarMarcador();
    void MostrarTablero();
    void MostrarRazonGanador(int);
    void MostrarJuegoTerminado(bool jugador_1_gana);
    void MostrarMensajeDeDespedida();

    void MostrarMensajeDeError(ErrorDelJuego tipoDeError);
};
#endif //PROYECTO_PROGRAMACION2_INTERFAZJUEGO_H
