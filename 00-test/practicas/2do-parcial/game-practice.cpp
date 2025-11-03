#include <iostream> // Para entrada (cin) y salida (cout)
#include <cstdlib>  // Para números aleatorios (rand, srand)
#include <ctime>    // Para inicializar los números aleatorios (time)
#include <conio.h>

// Usamos el espacio de nombres std para no tener que escribir std::cout
using namespace std;

// --- Función para obtener una carta (2-11) ---
// La ponemos aquí arriba para que main() la pueda ver.
int obtenerCarta() {
    // rand() % 13 genera un número de 0 a 12. Le sumamos 1 (1-13)
    // 1 = As, 2-10 = 2-10, 11 = J, 12 = Q, 13 = K
    int carta = (rand() % 13) + 1;

    if (carta == 1) {
        // Es un As, vale 11 (por ahora)
        cout << "(Carta: As) ";
        return 11;
    } else if (carta > 10) {
        // Es J, Q, o K, valen 10
        if (carta == 11) cout << "(Carta: J) ";
        if (carta == 12) cout << "(Carta: Q) ";
        if (carta == 13) cout << "(Carta: K) ";
        return 10;
    } else {
        // Es 2, 3, 4, 5, 6, 7, 8, 9, 10
        cout << "(Carta: " << carta << ") ";
        return carta;
    }
}

// --- Función para ajustar el puntaje si hay As (11) y se pasa de 21 ---
// Recibe el puntaje actual y el número de Ases que tiene.
// Devuelve el nuevo puntaje.
int ajustarPorAs(int puntaje, int numAses) {
    // Mientras el puntaje sea mayor a 21 y queden Ases (que valen 11),
    // cambia el valor de un As a 1 (restando 10 al puntaje).
    while (puntaje > 21 && numAses > 0) {
        puntaje = puntaje - 10; // Un As ahora vale 1 en lugar de 11
        numAses--; // Usamos uno de los Ases
        cout << "[Ajuste de As: Tu puntaje ahora es " << puntaje << "] ";
    }
    return puntaje;
}


// --- Función Principal del Programa ---
int main() {
    // 1. Inicializar el generador de números aleatorios
    // Esto se hace SOLO UNA VEZ al inicio del programa.
    srand(time(NULL));

    int saldoJugador = 0;
    
    cout << "Bienvenido al Blackjack!" << endl;
    cout << "Ingresa tu saldo inicial para jugar: $";
    cin >> saldoJugador;

    // 2. Bucle principal del juego (mientras tenga dinero)
    while (saldoJugador > 0) {
        
        cout << "\n--------------------------" << endl;
        cout << "Nueva Ronda. Tu saldo es: $" << saldoJugador << endl;
        
        // 3. Preguntar la apuesta (Regla 2)
        int apuesta = 0;
        do {
            cout << "Cuanto desea apostar? (Min $1): $";
            cin >> apuesta;
            
            if (apuesta > saldoJugador) {
                cout << "No puedes apostar mas de lo que tienes! ($" << saldoJugador << ")" << endl;
            }
            if (apuesta <= 0) {
                cout << "La apuesta debe ser positiva." << endl;
            }
        } while (apuesta <= 0 || apuesta > saldoJugador);

        // Variables de la ronda
        int puntajeJugador = 0;
        int puntajeDealer = 0;
        int asesJugador = 0; // Cuántos Ases (11) tiene el jugador
        int asesDealer = 0;  // Cuántos Ases (11) tiene el dealer

        // Banderas (flags) para saber si alguien se pasó
        bool jugadorSePaso = false;
        bool dealerSePaso = false;
        
        // 4. Repartir Cartas (Regla 6)
        
        cout << "\n--------------------------" << endl;
        
        // Carta 1 Jugador
        cout << "Tu primera carta: ";
        int cartaJ1 = obtenerCarta();
        if (cartaJ1 == 11) asesJugador++;
        puntajeJugador += cartaJ1;

        // Carta 1 Dealer
        cout << "\nPrimera carta del Dealer: ";
        int cartaD1 = obtenerCarta();
        if (cartaD1 == 11) asesDealer++;
        puntajeDealer += cartaD1;

        // Carta 2 Jugador
        cout << "\nTu segunda carta: ";
        int cartaJ2 = obtenerCarta();
        if (cartaJ2 == 11) asesJugador++;
        puntajeJugador += cartaJ2;

        // Carta 2 Dealer (Oculta)
        int cartaD2_oculta = obtenerCarta();
        if (cartaD2_oculta == 11) asesDealer++;
        
        cout << "\nSegunda carta del Dealer: [BOCA ABAJO]" << endl;
        
        // Mostrar puntajes iniciales
        // Ajustamos por si sacó dos Ases (11+11 = 22 -> se ajusta a 12)
        puntajeJugador = ajustarPorAs(puntajeJugador, asesJugador);
        
        cout << "\n--- Tu Turno ---" << endl;
        cout << "Tu puntaje: " << puntajeJugador << endl;
        cout << "Puntaje visible del Dealer: " << puntajeDealer << endl;

        // 5. Revisar si hay Blackjack (21 natural) (Regla 8)
        bool jugadorTieneBlackjack = (puntajeJugador == 21);
        
        if (jugadorTieneBlackjack) {
            cout << "\n************************" << endl;
            cout << "BLACKJACK! Felicidades!" << endl;
            cout << "Ganas 2 a 1!" << endl;
            // Gana el doble de su apuesta (o sea, 2 * apuesta se suma a su saldo)
            saldoJugador += (apuesta * 2);
            // continue; salta al inicio del bucle while (nueva ronda)
            continue; 
        }

        // 6. Turno del Jugador (Reglas 5 y 7)
        char decision = ' ';
        // Mientras el jugador NO se plante y NO se pase de 21
        // Y según tus reglas (Regla 5 y 7), si es 16 o menos, debe decidir.
        // Si es 17 o más, se planta.
        
        while (puntajeJugador < 17 && !jugadorSePaso) {
            cout << "\nTu puntaje (" << puntajeJugador << ") es menor a 17." << endl;
            cout << "Deseas pedir (P) o plantarte (T)?: ";
            cin >> decision;

            if (decision == 'P' || decision == 'p') {
                // Pedir carta
                cout << "Pides carta: ";
                int nuevaCarta = obtenerCarta();
                if (nuevaCarta == 11) asesJugador++;
                
                puntajeJugador += nuevaCarta;
                cout << "\nTu nuevo puntaje: " << puntajeJugador << endl;

                // Revisar si se pasó (y ajustar por Ases)
                if (puntajeJugador > 21) {
                    puntajeJugador = ajustarPorAs(puntajeJugador, asesJugador);

                    // Si después de ajustar sigue > 21, se pasó
                    if (puntajeJugador > 21) {
                        cout << "TE PASASTE DE 21 (Bust)!" << endl;
                        jugadorSePaso = true;
                    }
                }
            } else if (decision == 'T' || decision == 't') {
                // Plantarse
                cout << "Te plantas con " << puntajeJugador << endl;
                break; // Sale del bucle del turno del jugador
            }
        }

        if (puntajeJugador >= 17 && puntajeJugador <= 21 && !jugadorTieneBlackjack) {
            cout << "\nTe plantas automaticamente con " << puntajeJugador << " (Regla: 17 a 21)" << endl;
        }

        // 7. Turno del Dealer (Regla 5 y 6)
        
        // Si el jugador no se pasó, es turno del dealer
        if (!jugadorSePaso) {
            cout << "\n--- Turno del Dealer ---" << endl;
            // Revelar la carta oculta (Regla 6)
            puntajeDealer += cartaD2_oculta;
            cout << "El Dealer revela su carta oculta: ";
            // (Mostramos el valor, aunque la función ya imprimió el tipo)
            cout << cartaD2_oculta << endl;
            
            // Ajustar por si el dealer tenía dos Ases
            puntajeDealer = ajustarPorAs(puntajeDealer, asesDealer);
            cout << "Puntaje total del Dealer: " << puntajeDealer << endl;

            // El dealer pide cartas hasta tener 17 o más (Regla 5)
            while (puntajeDealer < 17) {
                cout << "El Dealer pide carta: ";
                int nuevaCartaDealer = obtenerCarta();
                if (nuevaCartaDealer == 11) asesDealer++;
                
                puntajeDealer += nuevaCartaDealer;
                cout << "\nNuevo puntaje del Dealer: " << puntajeDealer << endl;

                // Revisar si se pasó (y ajustar por Ases)
                if (puntajeDealer > 21) {
                    puntajeDealer = ajustarPorAs(puntajeDealer, asesDealer);
                    
                    if (puntajeDealer > 21) {
                        cout << "EL DEALER SE PASO DE 21 (Bust)!" << endl;
                        dealerSePaso = true;
                    }
                }
            }
            cout << "El Dealer se planta con " << puntajeDealer << endl;
        }

        // 8. Determinar Ganador
        cout << "\n--- Resultados de la Ronda ---" << endl;
        cout << "Tu puntaje: " << puntajeJugador << endl;
        cout << "Puntaje del Dealer: " << puntajeDealer << endl;

        if (jugadorSePaso) {
            cout << "Perdiste (Te pasaste)." << endl;
            saldoJugador -= apuesta;
        } else if (dealerSePaso) {
            cout << "Ganaste! (El Dealer se paso)." << endl;
            saldoJugador += apuesta;
        } else if (puntajeJugador > puntajeDealer) {
            cout << "Ganaste! (Mayor puntaje)." << endl;
            saldoJugador += apuesta;
        } else if (puntajeDealer > puntajeJugador) {
            cout << "Perdiste. (Dealer tiene mayor puntaje)." << endl;
            saldoJugador -= apuesta;
        } else {
            // Empate
            cout << "Empate (Push). Nadie gana." << endl;
            // El saldo no cambia
        }
    } // Fin del bucle principal (while saldo > 0)

    // 9. Fin del juego (Regla 9)
    cout << "\n--------------------------" << endl;
    cout << "JUEGO TERMINADO" << endl;
    cout << "Perdiste todo tu dinero." << endl;
    
    cout << "\nPresiona cualquier tecla para salir..." << endl;
    _getch();
    
    return 0; // Indica que el programa terminó exitosamente
}
