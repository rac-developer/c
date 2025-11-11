// Estas son las "librerías" que necesitamos para que C++
// sepa cómo manejar la entrada/salida (iostream),
// texto (string), números aleatorios (cstdlib, ctime)
// y revisar caracteres (cctype).
#include <iostream>
#include <string>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <cctype>  // Para isdigit()

// Usamos el "espacio de nombres" std para no tener que
// escribir std::cout, std::string, etc.
using namespace std;

/**
 *  Muestra las reglas del juego al jugador.
 */
void mostrarReglas() {
    cout << "========================================" << endl;
    cout << "  Bienvenido a Muertos y Heridos" << endl;
    cout << "========================================" << endl;
    cout << "Voy a pensar un numero de 4 digitos distintos." << endl;
    cout << "Tu objetivo es adivinarlo en 7 intentos." << endl;
    cout << "\n";
    cout << "Por cada intento, te dire:" << endl;
    cout << "  - Muertos: Digitos correctos en la posicion correcta." << endl;
    cout << "  - Heridos: Digitos correctos en la posicion incorrecta." << endl;
    cout << "\n";
    cout << "REGLA IMPORTANTE:" << endl;
    cout << "Si introduces un numero con digitos repetidos" << endl;
    cout << "(o un valor invalido), perderas un intento." << endl;
    cout << "¡Mucha suerte!" << endl;
    cout << "----------------------------------------" << endl;
}

/**
 * @brief Verifica si un string (numero) tiene digitos duplicados.
 * @param numero El string a verificar.
 * @return true si tiene duplicados, false si no.
 */
bool tieneDuplicados(string numero) {
    // Usamos dos bucles "anidados" para comparar cada
    // digito con todos los que le siguen.
    for (int i = 0; i < numero.length(); ++i) {
        for (int j = i + 1; j < numero.length(); ++j) {
            // Si encontramos dos digitos iguales en posiciones
            // diferentes, es un duplicado.
            if (numero[i] == numero[j]) {
                return true;
            }
        }
    }
    // Si terminamos los bucles sin encontrar duplicados,
    // devolvemos false.
    return false;
}

/**
 * @brief Genera un numero secreto de 4 digitos distintos.
 * @return Un string con el numero secreto.
 */
string generarSecreto() {
    string secreto = "";

    // Bucle que se repite hasta que el string "secreto"
    // tenga 4 caracteres de longitud.
    while (secreto.length() < 4) {
        // 1. Genera un numero aleatorio entre 0 y 9.
        int digito = rand() % 10;

        // 2. Convierte ese numero (int) a un caracter (char).
        // Ej: 5 (numero) se vuelve '5' (caracter)
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

/**
 * @brief Verifica si la entrada del usuario es válida (4 digitos, sin letras).
 * @param apuesta El string ingresado por el usuario.
 * @return true si es válida, false si no.
 */
bool esEntradaValida(string apuesta) {
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
    // (luego revisaremos duplicados por separado)
    return true;
}

int main() {
    // 1. Preparamos el generador de numeros aleatorios.
    //    Esto usa la hora actual como "semilla" para que
    //    los numeros sean diferentes cada vez que juegas.
    srand(time(NULL));

    // 2. Mostramos las reglas e inicializamos el juego
    mostrarReglas();
    string secreto = generarSecreto();
    int intentos = 7;
    bool gano = false;

    // (Opcional) Descomenta la siguiente linea para ver
    // el numero secreto y hacer pruebas:
    // cout << "(Pista: El secreto es " << secreto << ")" << endl;

    // 3. Bucle principal del juego
    //    Se repite mientras queden intentos Y el jugador no haya ganado.
    while (intentos > 0 && !gano) {
        cout << "\nTe quedan " << intentos << " intentos." << endl;
        cout << "Introduce tu numero de 4 digitos: ";

        string apuesta;
        cin >> apuesta;

        // 4. Validación de la entrada
        // Primero, revisamos si es una entrada invalida (longitud o letras)
        if (!esEntradaValida(apuesta)) {
            cout << "Entrada invalida. Debe ser de 4 digitos numericos." << endl;
            cout << "Pierdes un intento." << endl;
            intentos--; // Penalización
            continue; // Salta al siguiente ciclo del bucle
        }

        // Segundo, revisamos la regla de digitos repetidos
        if (tieneDuplicados(apuesta)) {
            cout << "¡Error! Tu numero tiene digitos repetidos." << endl;
            cout << "Pierdes un intento." << endl;
            intentos--; // Penalización
            continue; // Salta al siguiente ciclo del bucle
        }

        // 5. Si la entrada es válida, calculamos Muertos y Heridos
        int muertos = 0;
        int heridos = 0;

        // --- Calculo de Muertos ---
        // Comparamos caracter por caracter en la misma posicion
        for (int i = 0; i < 4; ++i) {
            if (apuesta[i] == secreto[i]) {
                muertos++;
            }
        }

        // --- Calculo de Heridos ---
        // Comparamos cada digito de la apuesta con TODOS
        // los digitos del secreto.
        for (int i = 0; i < 4; ++i) { // Digito de la apuesta
            for (int j = 0; j < 4; ++j) { // Digito del secreto
                
                // ¿Coinciden los digitos?
                if (apuesta[i] == secreto[j]) {
                    // ¿Estan en POSICION DIFERENTE?
                    if (i != j) {
                        // Si estan en posicion diferente, es un Herido.
                        heridos++;
                    }
                    // Si i == j, es un Muerto, pero esos ya los
                    // contamos en el bucle anterior, asi que no
                    // hacemos nada.
                }
            }
        }
        
        // CORRECCIÓN: El método anterior de Heridos puede contar
        // un "Muerto" como "Herido" si el dígito está duplicado
        // en la apuesta (aunque ya validamos eso). Una forma más segura:
        
        /*
        // --- Cálculo Alternativo (y más seguro) ---
        int muertos = 0;
        int heridos = 0;

        // 1. Contar Muertos (igual que antes)
        for (int i = 0; i < 4; ++i) {
            if (apuesta[i] == secreto[i]) {
                muertos++;
            }
        }

        // 2. Contar Heridos
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
        // Puedes usar cualquiera de los dos métodos de cálculo.
        // El segundo es más directo para este problema.
        // Voy a dejar el código con el segundo método.
        */
       
        // (Borrando el primer método de cálculo y usando el segundo)
        muertos = 0;
        heridos = 0;

        // 1. Contar Muertos
        for (int i = 0; i < 4; ++i) {
            if (apuesta[i] == secreto[i]) {
                muertos++;
            }
        }

        // 2. Contar Heridos
        for (int i = 0; i < 4; ++i) { // Itera sobre la apuesta
            // `find` busca el caracter apuesta[i] dentro de "secreto"
            // Si lo encuentra (no es npos) Y no es un muerto (posiciones
            // diferentes), entonces es un herido.
            if (secreto.find(apuesta[i]) != string::npos && apuesta[i] != secreto[i]) {
                heridos++;
            }
        }


        // 6. Mostrar resultado del intento
        cout << "----------------------------------------" << endl;
        cout << "Resultado: " << muertos << " Muertos y " << heridos << " Heridos." << endl;
        cout << "----------------------------------------" << endl;

        // 7. Revisar si gano
        if (muertos == 4) {
            gano = true;
        } else {
            // Si no gano, pierde un intento
            intentos--;
        }
    } // Fin del bucle while

    // 8. Mostrar mensaje final (fuera del bucle)
    if (gano) {
        cout << "\n¡FELICIDADES! Has adivinado el numero secreto: " << secreto << endl;
    } else {
        cout << "\nLO SIENTO, PERDISTE. Se te acabaron los intentos." << endl;
        cout << "El numero secreto era: " << secreto << endl;
    }

    return 0; // Termina el programa
}
