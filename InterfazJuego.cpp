//
// Created by solangel quiroga on 30/11/22.
//

#include "InterfazJuego.h"

// Constructor
InterfazJuego::InterfazJuego() {
    tablero = nullptr;
    jugador1 = nullptr;
    jugador2 = nullptr;
    numero_turno = 0;
}

// Inicialización de la interfaz de usuario.
void InterfazJuego::IniciarInterfaz(shared_ptr<TableroJuego> newTablero,
                                    shared_ptr<Jugador> newJugador1,
                                    shared_ptr<Jugador> newJugador2) {

    tablero = newTablero;
    jugador1 = newJugador1;
    jugador2 = newJugador2;
}

// Muestra el encabezado del juego y las opciones del menú del juego.
void InterfazJuego::MostrarMensajeDeBienvenida() {
    cout << "           ██████      ███   ██    ██   ███   ███████\n"
            "           ██    ██  ██   ██ ███  ███ ██   ██ ██     \n"
            "           ██    ██  ███████ ██ ██ ██ ███████ ███████\n"
            "           ██    ██  ██   ██ ██    ██ ██   ██      ██\n"
            "           ██████    ██   ██ ██    ██ ██   ██ ███████\n"
            "\n";
}

// Muestra las opciones del menú del juego.
void InterfazJuego::MostrarOpcionesDelJuego() {
    cout << "|---------OPCIONES---------|" << endl;
    cout << "  1. Mostrar instrucciones." << endl;
    cout << "  2. Un jugador." << endl;
    cout << "  3. Dos jugadores." << endl;
    cout << "  0. Salir." << endl;
    cout << "Escoja una opcion  :  ";
}

// Muestra las Instrucciones del juego.
void InterfazJuego::MostrarInstruccionesDelJuego() {
    cout << "Indicaciones\n"
            "Cada jugador cuenta con doce fichas que se pueden observar en\n"
            "pantalla, lado superior e inferior.                          \n"
            "Las fichas se colocan sobre las casillas oscuras, otorgando  \n"
            "por teclado la fila y la columna en la que se encuentra, des-\n"
            "pues se procede a otorgar mediante la tecla la fila y columna\n"
            " donde se quiere mover la ficha.                             \n"
            "Tener en cuenta que cuando la ficha llega a la fila inferior \n"
            "o superior(dependiento al lado del contricante), la ficha se \n"
            "convertira en una ficha reina, que puede ir de manera diago- \n"
            "al por mas de una casilla.                                   \n"
            "NOTA : Observar si forzar salto esta activado o desactivado. \n"
            "La funcion forzar salto se encarga de que el jugador tenga   \n"
            "que mover forzosamente una ficha con la condicion que pueda  \n"
            "'comer'\n" << endl;
}

//Ingreso de los nombres del Jugador.
void InterfazJuego::MostrarIngresarDatos(int numero) {
    cout << "JUGADOR " << numero << "\n"
                                    "Nombre : ";
}
//Muestra la opcion para activar o desactivar forzar Salto.
void InterfazJuego::MostrarOpcionForzarSalto() {
    cout << "CONFIGURACIONES\n"
            "Forzar salto esta desactivado. Desea activarlo? [s]/[n] : ";
}

void InterfazJuego::MostrarModoDeJuegoYTurnoActual(bool actualizarTurno, shared_ptr<Jugador> turnoActual) {
    ostringstream mostrar;
    if (actualizarTurno) numero_turno += 1;

    // Encabezado de juego.
    if (typeid(jugador1) == typeid(jugador2)) {
        mostrar << "DAMAS: Modo dos Jugadores      Turno # " << numero_turno <<  " : " << turnoActual->DevolverNombre() << "\n\n";
    }
    else {
        mostrar << "DAMAS: Modo un Jugador         Turno # " << numero_turno << " : " << turnoActual->DevolverNombre() << "\n\n";
    }
    cout << "\n\n" << mostrar.str();
}

void InterfazJuego::MostrarMarcador() {
    cout << "--->   \033[1;40m \u25CF \033[0m   " << jugador1->DevolverNombre() << "     " << jugador1->DevolverFichasComidas() << " - " << jugador2->DevolverFichasComidas() << "     " << jugador2->DevolverNombre() << "   \033[1;31;40m \u25CF \033[1;31;0m   <---";
}

void InterfazJuego::MostrarTablero() {
    ostringstream mostrar;

    // La parte superior izquierda y la parte inferior derecha son casillas de colores blancos.
    bool esTableroCasillaBlanco = true;

    // Ver colores y sintaxis en: https://elpuig.xeill.net/Members/vcarceler/articulos/escape-ansi.
    // La sintáxis sería: "\033[x;xx;xxm" dónde cada 'x' representa un dígito.
    string casillaNegraTablero = "\033[40m   \033[0m";
    string casillaBlancaTablero = "\033[47m   \033[0m";

    // Representación del tablero del juego.
    mostrar << "    1  2  3  4  5  6  7  8 \n\n";
    for (auto fila = 0; fila < 8; ++fila) {
        mostrar << static_cast<char>('A' + fila) << "  ";
        for (auto columna = 0; columna < 8; ++columna) {
            if (esTableroCasillaBlanco) {
                mostrar << casillaBlancaTablero;
            }
            else if (tablero->getFicha(fila, columna) == nullptr) {
                mostrar << casillaNegraTablero;
            }
            else {
                mostrar << *(tablero->getFicha(fila, columna));
            }
            esTableroCasillaBlanco = not esTableroCasillaBlanco;
        }
        mostrar << "  " << static_cast<char>('A' + fila) << endl;

        esTableroCasillaBlanco = not esTableroCasillaBlanco;
    }
    mostrar << "\n    1  2  3  4  5  6  7  8 \n" << endl;

    // Ingreso de Coordenadas.
    mostrar << "Introduzca una secuencia de coordenadas para mover una pieza:\n"
            << "  ejemplo: 'C2 D3' sería un salto simple.\n"
            << "  ejemplo: 'F1 D4 B1' sería un doble salto.\n";
    if (numero_turno % 2 == 1)
        mostrar << "\033[1;31;40mMovimiento Jugador Uno:\033[0m ";
    else
        mostrar << "\033[1;40mMovimiento Jugador Dos:\033[0m ";

    cout << "\n\n" << mostrar.str();
}
void InterfazJuego::MostrarRazonGanador(int razon){
    switch (razon) {
        case 1:
            cout << "GANADOR. Razon: Comio todas las fichas." << endl;
            break;
        case 2:
            cout << "GANADOR. Razon: Acorralo las piezas del rival, tal que se quedo sin mas movimientos permitidos." << endl;
            break;
        case 3:
            cout << "GANADOR. Razon: Ambos jugadores se quedan sin movimientos legales, gano el que tiene mas fichas en el tableo." << endl;
            break;
    }
}
// Salida de los mensajes para el Jugador que Gana.
void InterfazJuego::MostrarJuegoTerminado(bool jugador_1_gana) {

    const string menasajeParaJugador1 = "\n\n\n"
                                        "███████  ██    ██  ███████   ███   ██████    ██████  ██████      ██\n"
                                        "     ██  ██    ██  ██      ██   ██ ██    ██ ██    ██ ██   ██   ████\n"
                                        "     ██  ██    ██  ███████ ███████ ██    ██ ██    ██ ██████      ██\n"
                                        "██   ██  ██    ██  ██   ██ ██   ██ ██    ██ ██    ██ ██ ██       ██\n"
                                        " ████     ██████   ███████ ██   ██ ██████    ██████  ██   ██   ██████\n"
                                        "\n"
                                        "███████    ███    ██   ██   ███     ██ ██ ██          \n"
                                        "██       ██   ██  ███  ██ ██   ██   ██ ██ ██          \n"
                                        "███████  ███████  ██ █ ██ ███████   ██ ██ ██          \n"
                                        "██   ██  ██   ██  ██  ███ ██   ██                     \n"
                                        "███████  ██   ██  ██   ██ ██   ██   ██ ██ ██          \n";

    const string menasajeParaJugador2 = "\n\n\n"
                                        "████████ ██    ██  ███████   ███   ██████    ██████  ██████    ██████\n"
                                        "     ██  ██    ██  ██      ██   ██ ██    ██ ██    ██ ██   ██       ██\n"
                                        "     ██  ██    ██  ███████ ███████ ██    ██ ██    ██ ██████    ██████\n"
                                        "██   ██  ██    ██  ██   ██ ██   ██ ██    ██ ██    ██ ██ ██     ██\n"
                                        " ████     ██████   ███████ ██   ██ ██████    ██████  ██   ██   ██████\n"
                                        "\n"
                                        "███████    ███    ██   ██   ███     ██ ██ ██          \n"
                                        "██       ██   ██  ███  ██ ██   ██   ██ ██ ██          \n"
                                        "███████  ███████  ██ █ ██ ███████   ██ ██ ██          \n"
                                        "██   ██  ██   ██  ██  ███ ██   ██                     \n"
                                        "███████  ██   ██  ██   ██ ██   ██   ██ ██ ██          \n";

    const string preguntarSiJugarDeNuevo = "¿Te gustaría volver a jugar? [s] o [n]: ";

    if (jugador_1_gana) {
        cout << menasajeParaJugador1 << endl;
    }
    else {
        cout << menasajeParaJugador2 << endl;
    }

    cout << preguntarSiJugarDeNuevo;
}

// Salida cuando se cierra el Programa.
void InterfazJuego::MostrarMensajeDeDespedida() {

    const string limpiarPantalla = string(75, '\n');

    const string mensajeCerrarPrograma =
            "  ███    ██████   ████████  ██████  ███████  ██ ██ ██          \n"
            "██   ██  ██    ██    ██    ██    ██ ██       ██ ██ ██          \n"
            "███████  ██    ██    ██    ██    ██ ███████  ██ ██ ██          \n"
            "██   ██  ██    ██    ██    ██    ██      ██                    \n"
            "██   ██  ██████   ████████  ██████  ███████  ██ ██ ██          \n";

    cout << limpiarPantalla << mensajeCerrarPrograma << endl;
}

// Controla la salida de mensajes de error.
void InterfazJuego::MostrarMensajeDeError(ErrorDelJuego tipoDeError) {

    string mensajeDeError = "\n\033[31mERROR\033[0m: ";

    switch (tipoDeError) {
        // Salida cuando la entrada del usuario no es correcta.
        case ErrorDelJuego::ENTRADA_INVALIDA: {
            mensajeDeError += "Entrada no válida proporcionada";
            break;
        }
            // Salida cuando la entrada del usuario es correcta, pero rompe una de las reglas del juego.
        case ErrorDelJuego::MOVIMIENTO_INVALIDO: {
            mensajeDeError += "Intento de movimiento Invalido";
            break;
        }
    }

    cout << mensajeDeError << endl;
}
