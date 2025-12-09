#include <iostream>
#include <string>	// Manejar cadendas de texto
#include <cstdlib>	// Para srand()
#include <ctime>	// Para time(NULL) 
#include <cctype>
#include <windows.h>

using namespace std;

// ========================================
//	Funciones
// ========================================

void mostrarReglas() {
	cout << "========================================" << endl;
    cout << "  Bienvenido a Muertos y Heridos" << endl;
    cout << "========================================" << endl;
    cout << "Voy a pensar un numero de 4 digitos distintos." << endl;
    cout << "Tu objetivo es adivinarlo en 7 intentos.\n" << endl;
    cout << "Por cada intento, te dire:" << endl;
    cout << "  - Muertos: Digitos correctos en la posicion correcta." << endl;
    cout << "  - Heridos: Digitos correctos en la posicion incorrecta.\n" << endl;
    cout << "REGLA IMPORTANTE:" << endl;
    cout << "Si introduces un numero con digitos repetidos" << endl;
    cout << "(o un valor invalido), perderas un intento." << endl;
    cout << "Mucha suerte!" << endl;
    cout << "----------------------------------------" << endl;
}

bool tieneDuplicados (string numero) {
	// Usamos dos bucles "anidados" para comparar cada
    // digito con todos los que le siguen.
	for (int i = 0; i < numero.length(); i++) {
		for(int j  = i + 1; j < numero.length(); ++j) {
			if (numero[i] == numero[j]) {
            // Si encontramos dos digitos iguales en posiciones
            // diferentes, es un duplicado.
				return true;
			}
		}
	}
	// Si terminamos los bucles sin encontrar duplicados,
    // devolvemos false.
    return false;
}

// Genera un numero secreto de 4 digitos distintos.
// retorna un string con el numero secreto

string generarSecreto () {
	string secreto = "";
	
	while(secreto.length() < 4) {
		// 1. Genera un numero aleatorio entre 0 y 9.
        int digito = rand() % 10;

        // 2. Convierte ese numero (int) a un caracter (char).
        // Ej: 5 (numero) se vuelve '5' (caracter), por la tabla ASCII
        char digitoChar = digito + '0';

        // 3. Revisa si el digito YA esta en el string.
        //    string::npos es un valor especial que significa "no encontrado".
        if (secreto.find(digitoChar) == string::npos) {
            // 4. Si no esta, lo agregamos al secreto.
            secreto += digitoChar;
        }
	}
    return secreto;
}

// Verifica si la entrada del usuario es válida (4 digitos, sin letras).

bool esEntradaValida (string apuesta) {
	// 1. ¿Tiene 4 caracteres?
    if (apuesta.length() != 4) {
        return false;
    }
    
    // 2. ¿Son todos los caracteres digitos numericos?
    for (int i = 0; i < apuesta.length(); ++i) {
    	// isdigit() revisa si el caracter es un numero ('0' a '9')
        if (!isdigit(apuesta[i])) {
            return false;
    	}
	}
    
    // Si paso las dos pruebas, es una entrada valida
    return true;
}

// ========================================
//	Programa
// ========================================

int main () {
    // 1. Preparamos el generador de numeros aleatorios.
    //    Esto usa la hora actual como "semilla" para que
    //    los numeros sean diferentes cada vez que juegas.
	srand(time(NULL));
	
	// 2. Mostramos las reglas e inicializamos el juego
	mostrarReglas();
	string secreto = generarSecreto();
	int intentos = 100;
	bool gano = false;
	
	// 3. Bucle principal del juego
    //    Se repite mientras queden intentos Y el jugador no haya ganado.
	while (intentos > 0 && !gano) {
		
		cout << "\nTe quedan " << intentos << " intentos." << endl;
        cout << "Introduce tu numero de 4 digitos: ";
        
        string apuesta;
        cin >> apuesta;
        
        // Cambio que pidio el profesor
        if(apuesta == "4444") {
        	cout << "\n****************************************" << endl;
            cout << "  MODO DEBUG: El secreto es: " << secreto << endl;
            cout << "****************************************\n" << endl;
            cout << "Escribe una tecla y presiona Enter para continuar: ";
            
            char esperar;
            cin >> esperar;
            cout << "Continuando tu intento..." << endl;
            
            // Usamos 'continue' para saltar al INICIO del bucle 'while'
            // Esto evita que "4444" se cuente como un intento fallido
            // y no le resta una vida al jugador.
            continue;
		}
        
        // 4. Validación de la entrada
        // Primero, revisamos si es una entrada invalida (longitud o letras)
        if (!esEntradaValida(apuesta)) {
            cout << "Entrada invalida. Debe ser de 4 digitos numericos." << endl;
            cout << "Pierdes un intento." << endl;
            Beep(400, 300);
            intentos--; // Penalización
            continue; // Salta al siguiente ciclo del bucle
        }
        
        // Segundo, revisamos la regla de digitos repetidos
        if (tieneDuplicados(apuesta)) {
            cout << "¡Error! Tu numero tiene digitos repetidos." << endl;
            cout << "Pierdes un intento." << endl;
            Beep(400, 300);
            intentos--; // Penalización
            continue; // Salta al siguiente ciclo del bucle
        }
        
        // 5. Si la entrada es valida, calculamos Muertos y Heridos
        
        int muertos = 0;
        int heridos = 0;

        // 1) Contar Muertos (igual que antes)
        for (int i = 0; i < 4; ++i) {
            if (apuesta[i] == secreto[i]) {
                muertos++;
            }
        }

        // 2) Contar Heridos
        for (int i = 0; i < 4; ++i) { // Digito de la apuesta
            // Revisamos si el digito de la apuesta esta en el secreto
            if (secreto.find(apuesta[i]) != string::npos) {
                // Si esta, PERO no esta en la misma posicion
                // (o sea, no es un Muerto), entonces es un Herido.
                if (apuesta[i] != secreto[i]) {
                    heridos++;
                }
            }
        }
        
        // 6. Mostrar resultado del intento
        cout << "----------------------------------------" << endl;
        cout << "Resultado: " << muertos << " Muertos y " << heridos << " Heridos." << endl;
        cout << "----------------------------------------" << endl;
        
		if (muertos == 0 && heridos == 0) {
			Beep(400, 300);
		} else {
			Beep(800, 200);
		}
        
		// 7. Revisa si gano
		if (muertos == 4) {
			gano == true;
		} else {
			intentos--;
		}
	}
	
	// 8. Mostrar mensaje final (fuera del bucle)
	
	if (gano) {
		cout << "\n¡FELICIDADES! Has adivinado el numero secreto: " << secreto << endl;
		Beep(800, 200);
    } else {
        cout << "\nLO SIENTO, PERDISTE. Se te acabaron los intentos." << endl;
        Beep(400, 300);
        cout << "El numero secreto era: " << secreto << endl;
	}
	
	return 0;
}

