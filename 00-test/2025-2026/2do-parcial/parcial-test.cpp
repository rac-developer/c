#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm> // Para reverse()
#include <windows.h> // Para Sleep()
#include <ctime>     // Para time()
#include <conio.h>   // Para kbhit() y getch()
#include <sstream>   // Para dividir la frase en palabras
#include <cctype>    // Para isalpha(), tolower(), toupper()

using namespace std;

// --- Funciones Auxiliares para la Opción B ---

/**
 * @brief Verifica si un caracter es una vocal (sensible a mayúsculas/minúsculas).
 */
bool esVocal(char c) {
    char lower_c = tolower(c); // Convierte a minúscula
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

/**
 * @brief Invierte una cadena de caracteres.
 */
string invertirCadena(string s) {
    reverse(s.begin(), s.end());
    return s;
}

// --- Lógica de las Opciones ---

/**
 * @brief Opción A: Genera 10 números aleatorios entre -6.3 y -2.2, cada 1 seg.
 */
void generarNumerosAleatorios() {
    cout << "\n--- Ejecutando Opción A: Generación de 10 Números Aleatorios ---\n";
    const double MIN_VAL = -6.3;
    const double MAX_VAL = -2.2;
    const int NUM_COUNT = 10;

    for (int i = 0; i < NUM_COUNT; ++i) {
        double random_fraction = (double)rand() / RAND_MAX;
        double numero = MIN_VAL + (MAX_VAL - MIN_VAL) * random_fraction;

        cout << "Número " << (i + 1) << ": " << numero << endl;

        // Pausa de 1 segundo (1000 milisegundos) usando windows.h
        Sleep(1000); 
    }
    cout << "--- Generación de números aleatorios finalizada ---\n";
}

/**
 * @brief Opción B: Procesa la frase ingresada.
 * @param salida Arreglo de strings donde se guardarán los resultados.
 */
void procesarFrase(string salida[]) {
    string frase_ingresada;
    cout << "\n--- Ejecutando Opción B: Manipulación de Frase ---\n";
    cout << "Ingrese una frase de mínimo 3 palabras: ";
    
    // *** CORRECCIÓN IMPORTANTE ***
    // Se usa 'cin >> ws' para consumir cualquier espacio en blanco o nueva línea
    // que haya quedado en el buffer (por culpa de getch/cin) ANTES de que getline() lea.
    getline(cin >> ws, frase_ingresada);

    // 1. Validar si hay al menos 3 palabras
    stringstream ss(frase_ingresada);
    string palabra_temporal;
    int contador_palabras = 0;
    while (ss >> palabra_temporal) {
        contador_palabras++;
    }

    if (contador_palabras < 3) {
        cout << "Error: La frase debe tener al menos 3 palabras. Volviendo al menú.\n";
        return; 
    }
    
    // 2. Extraer vocales y consonantes (recorriendo la frase completa)
    string vocales_totales = "";
    string consonantes_totales = "";

    // Bucle 'for' tradicional (compatible con C++98)
    for (size_t i = 0; i < frase_ingresada.length(); ++i) {
        char c = frase_ingresada[i];
        
        if (isalpha(c)) { 
            if (esVocal(c)) {
                vocales_totales += c;
            } else {
                consonantes_totales += c;
            }
        }
    }

    // 3. Llenar el arreglo 'salida'
    salida[0] = vocales_totales;      // salida[1] del ejercicio
    salida[1] = consonantes_totales;  // salida[2] del ejercicio
    salida[2] = invertirCadena(salida[0]); // salida[3] del ejercicio
    salida[3] = invertirCadena(salida[1]); // salida[4] del ejercicio

    // 4. Presentar resultados
    cout << "\n--- Resultados de la Opción B ---\n";
    cout << "salida[1] (Vocales):      " << salida[0] << endl;
    cout << "salida[2] (Consonantes):  " << salida[1] << endl;
    cout << "salida[3] (Vocales Inv.): " << salida[2] << endl;
    cout << "salida[4] (Conson. Inv.): " << salida[3] << endl;
    cout << "--------------------------------\n";
}

/**
 * @brief Función principal que maneja el menú y la selección kbhit/getch.
 */
int main() {
    string salida[4]; 
    srand(time(0)); 

    cout << "========================================\n";
    cout << "  Bienvenido al Selector de Opciones C++\n";
    cout << "========================================\n";
    cout << "Presione A para generar numeros aleatorios.\n";
    cout << "Presione B para procesar una frase.\n";

    // Bucle principal (infinito, ya que no hay opción de salir)
    while (true) {
        
        if (kbhit()) { 
            char opcion = getch(); 
            char opcion_normalizada = toupper(opcion); 

            if (opcion_normalizada == 'A') {
                generarNumerosAleatorios();
            } 
            else if (opcion_normalizada == 'B') {
                procesarFrase(salida);
            } 
            else {
                // Mensaje de error modificado (sin 'Q')
                cout << "\nOpción no válida. Por favor, presione 'A' o 'B'.\n";
            }
            
            // Reimprime el menú para la siguiente selección
            cout << "\nPresione A (Números) o B (Frase)." << endl;
        }
        
        Sleep(100); 
    }

    // El programa nunca llegará aquí, pero es buena práctica.
    return 0;
}
