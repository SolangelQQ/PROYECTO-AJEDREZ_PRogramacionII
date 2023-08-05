//
// Created by solangel quiroga on 30/11/22.
//

#include "Controlador.h"

//MÉTODOS PÚBLICOS:
//Constructor
Controlador::Controlador() {
    interfazJuego = make_shared<InterfazJuego>(InterfazJuego());
}

//Este método nos permite controlar el comportamiento y la ejecución del Juego.
void Controlador::IniciarJuego() {
    bool forzarSalto;
    while (true) {
        forzarSalto = false;
        interfazJuego->MostrarMensajeDeBienvenida();
        interfazJuego->MostrarOpcionesDelJuego();
        tablero = make_shared<TableroJuego>(TableroJuego());
        switch (DevolverModoDeJuego()) {
            case ModoDeJuego::INSTRUCCIONES:
                interfazJuego->MostrarInstruccionesDelJuego();
                break;
            case ModoDeJuego::UN_JUGADOR:
                interfazJuego->MostrarIngresarDatos(1);
                jugador1 = make_shared<JugadorHumano>(JugadorHumano(Color::BLANCO, getEntrada()));
                jugador2 = make_shared<IAN>(IAN(Color::NEGRO, tablero, "computadora"));
                Jugar(DevolverOpcionForzarSalto(forzarSalto));

                break;
            case ModoDeJuego::DOS_JUGADORES:
                interfazJuego->MostrarIngresarDatos(1);
                jugador1 = make_shared<JugadorHumano>(JugadorHumano(Color::BLANCO, getEntrada()));
                interfazJuego->MostrarIngresarDatos(2);
                jugador2 = make_shared<JugadorHumano>(JugadorHumano(Color::NEGRO, getEntrada()));
                Jugar(DevolverOpcionForzarSalto(forzarSalto));
                break;
        }
        if (!VolverAJugar()) {
            interfazJuego->MostrarMensajeDeDespedida();
            break;
        }
    }
    interfazJuego->MostrarMensajeDeDespedida();
}

void Controlador::Jugar(bool forzarSalto) {
    turnoActual = jugador1;
    interfazJuego->IniciarInterfaz(tablero, jugador1, jugador2);
    while (elJuegoTieneMasTurnos()) {
        bool legalMoveFound = false;
        bool lastMoveWasLegal = true;

        while (not legalMoveFound) {

            interfazJuego->MostrarModoDeJuegoYTurnoActual(lastMoveWasLegal, turnoActual);
            interfazJuego->MostrarMarcador();
            interfazJuego->MostrarTablero();
            getValidarEntrada();

            // Stops turn increment in UI when false
            lastMoveWasLegal = true;

            if (movimientoValido(turnoActual->getMovimiento(), forzarSalto)) {
                legalMoveFound = true;
                realizarMovimiento(turnoActual->getMovimiento());

            }
            else {
                lastMoveWasLegal = false;
                interfazJuego->MostrarMensajeDeError(ErrorDelJuego::MOVIMIENTO_INVALIDO);
            }
        }

        turnoActual = (turnoActual == jugador1) ? jugador2 : jugador1;
    }
    // gano por que comio todas las fichas
    if ( turnoActual->DevolverFichasComidas() == 12 ) interfazJuego->MostrarRazonGanador(1);
    // gano por que acorralo al oponente
    if ( (tablero->movimientosRestantes( Color::BLANCO ) == false and tablero->movimientosRestantes( Color::NEGRO ) == true )
    or (tablero->movimientosRestantes( Color::BLANCO ) == true and tablero->movimientosRestantes( Color::NEGRO ) == false )){
        interfazJuego->MostrarRazonGanador(2);
    }
    // gano por que tiene mas fichas que el oponente
    if ( tablero->movimientosRestantes( Color::BLANCO ) == false and tablero->movimientosRestantes( Color::NEGRO ) == false  ) interfazJuego->MostrarRazonGanador(3);

    interfazJuego->MostrarJuegoTerminado(turnoActual != jugador1);
}

bool Controlador::DevolverOpcionForzarSalto(bool forzarSalto) {
    interfazJuego->MostrarOpcionForzarSalto();
    string entrada = getEntrada();
    if (entrada == "si" or entrada == "s") forzarSalto = true;
    else if (entrada == "no" or entrada == "n") forzarSalto = false;
    else forzarSalto = DevolverOpcionForzarSalto(forzarSalto);
    return forzarSalto;
}

//MÉTODOS PRIVADOS:

//Determina las opciones y comportamiento del menú principal.
ModoDeJuego Controlador::DevolverModoDeJuego() {
    map< std::string, int > userChoice = {
            { "1",    1 },
            { "2",    2 },
            { "3",    3 },
            { "0",    0 }
    };
    string entrada = getEntrada();
    switch (userChoice[entrada]) {
        case 0:
            interfazJuego->MostrarMensajeDeDespedida();
            exit(0);
        case 1:
            return ModoDeJuego::INSTRUCCIONES;
        case 2:
            return ModoDeJuego::UN_JUGADOR;
        case 3:
            return ModoDeJuego::DOS_JUGADORES;
        default:
            interfazJuego->MostrarMensajeDeError(ErrorDelJuego::ENTRADA_INVALIDA);
            interfazJuego->MostrarMensajeDeBienvenida();
            return DevolverModoDeJuego();
    }
}

//Obtiene la entrada basada en el juego del usuario y verifica si es válida.
void Controlador::getValidarEntrada() {
    if (turnoActual->esHumano()) {
        dynamic_pointer_cast<JugadorHumano>(turnoActual)->setEntrada();

        while (not dynamic_pointer_cast<JugadorHumano>
                (turnoActual)->tieneEntradaValida()) {

            interfazJuego->MostrarMensajeDeError(ErrorDelJuego::ENTRADA_INVALIDA);
            interfazJuego->MostrarModoDeJuegoYTurnoActual(false, turnoActual);

            dynamic_pointer_cast<JugadorHumano>(turnoActual)->setEntrada();
        }

        string entrada = dynamic_pointer_cast<JugadorHumano>
                (turnoActual)->getEntrada();

        if (entrada == "0") {
            interfazJuego->MostrarMensajeDeDespedida();
            exit(0);
        }
    }
}
//Obtiene la entrada del usuario para opciones no relacionadas con el juego.
string Controlador::getEntrada() {
    string entrada;
    getline(cin, entrada, '\n');
    transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);
    return entrada;
}

// Comprueba si la secuencia de movimientos se ajusta a las reglas del juego.
bool Controlador::movimientoValido(Movimiento jugar, bool forzarSalto) {
    bool MovimientoEsValido = false;
    auto todosLosMovimientosValidos = tablero->getTodosLosMovimientosValidos(turnoActual->DevolverColor());

    for (const auto& movimientoValido : todosLosMovimientosValidos) {
        if (jugar == movimientoValido) {
            MovimientoEsValido = true;
            break;
        }
    }
    return MovimientoEsValido;
}

//Este método lleva a cabo la secuencia de movimientos dada y es asumida como válida.
void Controlador::realizarMovimiento(Movimiento jugar) {

    pair<int, int> deCasilla = jugar.getPrimero();
    pair<int, int> aCasilla;

    //Secuencia de movimiento de salto único.
    if (jugar.getLongitudDeSecuenciaDeMovimiento() == 2) {
        aCasilla = jugar.getSiguiente();
        if (not tablero->esCambioValido(tablero->getFicha(deCasilla), deCasilla, aCasilla)) {
            tablero->removerFicha({
                                          (deCasilla.first + aCasilla.first) / 2,
                                          (deCasilla.second + aCasilla.second) / 2});
            turnoActual->IncrementarFichasComidas();
        }
        tablero->moverFicha(deCasilla, aCasilla);
        //Secuencia de movimiento de salto múltiple.
    }
    else {
        while (jugar.tieneOtroMovimiento()) {
            aCasilla = jugar.getSiguiente();

            tablero->removerFicha({
                                          (deCasilla.first + aCasilla.first) / 2,
                                          (deCasilla.second + aCasilla.second) / 2
                                  });
            turnoActual->IncrementarFichasComidas();
            tablero->moverFicha(deCasilla, aCasilla);

            deCasilla = aCasilla;
        }
    }
}

//Comprueba si el jugador en turno tiene posibles movimientos, si no, pierde.
bool Controlador::elJuegoTieneMasTurnos() {
    auto colorDelJugador = turnoActual->DevolverColor();

    bool puedeMoverUnaFicha = tablero->movimientosRestantes(colorDelJugador);
    bool leQuedanPiezas = tablero->fichasRestantes(colorDelJugador);

    return puedeMoverUnaFicha or leQuedanPiezas;
}

//Pregunta al usuario si quiere jugar otro juego.
bool Controlador::VolverAJugar() {
    while (true) {
        auto entrada = getEntrada();
        if (entrada == "q" or entrada == "abandonar" or entrada == "salir" or entrada == "n" or entrada == "no") {
            return false;

        }
        else if (entrada == "s" or entrada == "si" or entrada == "") {
            return true;
        }
        else {
            interfazJuego->MostrarMensajeDeError(ErrorDelJuego::ENTRADA_INVALIDA);
        }
    }
}
