#include <iostream> 
#include <cstdlib>  
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// --- Función para obtener una carta (2-11) ---

int obtenerCarta(bool imprimir = true) {
    // rand() % 13 genera un número de 0 a 12. Le sumamos 1 (1-13)
    // 1 = As, 2-10 = 2-10, 11 = J, 12 = Q, 13 = K
    int carta = (rand() % 13) + 1;

    if (carta == 1) {
        // Es un As, vale 11 (por ahora)
        if (imprimir) cout << "(Carta: As) "; // <-- Solo imprime si 'imprimir' es true
        return 11;
    } else if (carta > 10) {
        // Es J, Q, o K, valen 10
        if (imprimir) { // <-- Solo imprime si 'imprimir' es true
            if (carta == 11) cout << "(Carta: J) ";
            if (carta == 12) cout << "(Carta: Q) ";
            if (carta == 13) cout << "(Carta: K) ";
        }
        return 10;
    } else {
        // Es 2, 3, 4, 5, 6, 7, 8, 9, 10
        if (imprimir) cout << "(Carta: " << carta << ") "; // <-- Solo imprime si 'imprimir' es true
        return carta;
    }
}

// --- Función para ajustar el puntaje si hay As (11) y se pasa de 21 ---

int ajustarPorAs(int puntaje, int &numAses) {
    // Mientras el puntaje sea mayor a 21 y queden Ases (que valen 11),
    // cambia el valor de un As a 1 (restando 10 al puntaje).
    while (puntaje > 21 && numAses > 0) {
        puntaje = puntaje - 10; // Un As ahora vale 1 en lugar de 11
        numAses--; // Usamos uno de los Ases
    }
    return puntaje;
}

int main() {
	
    // 1. Inicializar el generador de números aleatorios
    srand(time(NULL));

    int saldoJugador = 0;
    
    cout << "Bienvenido al Bj de la USM!" << endl;
    cout << "Ingresa tu saldo inicial para jugar: $";
    cin >> saldoJugador;

    // 2. Bucle principal del juego (mientras tenga dinero)
    while (saldoJugador > 0) {
        
        cout << "\n--------------------------" << endl;
        cout << "\nNueva Ronda. Tu saldo es: $" << saldoJugador << endl;
        
        // 3. Preguntar la apuesta
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
        int asesJugador = 0; 
        int asesDealer = 0;
        bool jugadorSePaso = false;
        bool dealerSePaso = false;
        
        // 4. Repartir Cartas
        
        cout << "\n--------------------------" << endl;
        
        // Carta 1 Jugador
        cout << "\nTu primera carta: ";
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
        int cartaD2_oculta = obtenerCarta(false);
		if (cartaD2_oculta == 11) asesDealer++;
        
        cout << "\nSegunda carta del Dealer: [BOCA ABAJO]" << endl;
        
        // Mostrar puntajes iniciales
        // Ajustamos por si sacó dos Ases (11+11 = 22 -> se ajusta a 12)
        puntajeJugador = ajustarPorAs(puntajeJugador, asesJugador);
        
        cout << "\n--- Tu Turno ---" << endl;
        cout << "Tu puntaje: " << puntajeJugador << endl;
        
        // 5. Revisar si el jugador tiene Blackjack (21 natural)
        
        bool jugadorTieneBlackjack = (puntajeJugador == 21);
        
        if (jugadorTieneBlackjack) {
            cout << "\n************************" << endl;
            cout << "BLACKJACK! Felicidades!" << endl;
            cout << "Ganas 2 a 1!" << endl;
            Beep(800, 200);
            saldoJugador += (apuesta * 2);
            // continue; salta al inicio del bucle while (nueva ronda)
            continue; 
        }

        // 6. Turno del Jugador
        
        char decision = ' ';
        while (puntajeJugador < 17 && !jugadorSePaso) {
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

        // 7. Turno del Dealer
        
        // Si el jugador no se pasó, es turno del dealer
        if (!jugadorSePaso) {
    		cout << "\n--- Turno del Dealer ---" << endl;
    		// Revelar la carta oculta
    		puntajeDealer += cartaD2_oculta;
    
	    	cout << "Primera carta: " << cartaD1 << endl;
			cout << "Revela su segunda carta oculta: " << cartaD2_oculta << endl;
	    
	    	// Ajustar por si el dealer tenía dos Ases
	    	puntajeDealer = ajustarPorAs(puntajeDealer, asesDealer);
	    	cout << "Puntaje total: " << puntajeDealer << endl;

            // El dealer pide cartas hasta tener 17 o más
            while (puntajeDealer < 17) {
                cout << "Pide carta: ";
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
        }

        // 8. Determinar Ganador
        cout << "\n--- Resultados de la Ronda ---" << endl;
        cout << "Tu puntaje: " << puntajeJugador << endl;
        cout << "Puntaje del Dealer: " << puntajeDealer << endl;

        if (jugadorSePaso) {
            cout << "Perdiste (Te pasaste)." << endl;
            saldoJugador -= apuesta;
            Beep(400, 300); // <-- SONIDO DE PERDER
        } else if (dealerSePaso) {
            cout << "Ganaste! (El Dealer se paso)." << endl;
            saldoJugador += apuesta;
            Beep(800, 200);
        } else if (puntajeJugador > puntajeDealer) {
            cout << "Ganaste! (Mayor puntaje)." << endl;
            saldoJugador += apuesta;
            Beep(800, 200);
        } else if (puntajeDealer > puntajeJugador) {
            cout << "Perdiste. (Dealer tiene mayor puntaje)." << endl;
            saldoJugador -= apuesta;
            Beep(400, 300);
        } else {
            cout << "Empate (Push). Nadie gana." << endl;
            Beep(600, 100); 
        }
    }

    cout << "\n--------------------------" << endl;
    cout << "JUEGO TERMINADO" << endl;
    cout << "Perdiste todo tu dinero." << endl;
    
    _getch();
    
    return 0;
}
