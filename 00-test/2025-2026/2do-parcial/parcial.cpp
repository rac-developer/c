#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm> 
#include <windows.h> 
#include <ctime>     
#include <conio.h>   
#include <sstream>   
#include <cctype>    

using namespace std;

bool esVocal(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

string invertirCadena(string s) {
    reverse(s.begin(), s.end());
    return s;
}

void generarNumerosAleatorios() {
    const double MIN_VAL = -6.3;
    const double MAX_VAL = -2.2;
    const int NUM_COUNT = 10;

    for (int i = 0; i < NUM_COUNT; ++i) {
        double random_fraction = (double)rand() / RAND_MAX;
        double numero = MIN_VAL + (MAX_VAL - MIN_VAL) * random_fraction;

        cout << "Numero " << (i + 1) << ": " << numero << endl;

        Sleep(1000); 
    }
}

void procesarFrase(string salida[]) {
    string frase_ingresada;
    cout << "Ingrese una frase de minimo 3 palabras: ";
    
    getline(cin >> ws, frase_ingresada);

    stringstream ss(frase_ingresada);
    string palabra_temporal;
    int contador_palabras = 0;
    while (ss >> palabra_temporal) {
        contador_palabras++;
    }

    if (contador_palabras < 3) {
        cout << "Error: La frase debe tener al menos 3 palabras.\n";
        return; 
    }
    
    string vocales_totales = "";
    string consonantes_totales = "";

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

    salida[0] = vocales_totales;     
    salida[1] = consonantes_totales;  
    salida[2] = invertirCadena(salida[0]); 
    salida[3] = invertirCadena(salida[1]); 

    cout << "salida[1] (Vocales):      " << salida[0] << endl;
    cout << "salida[2] (Consonantes):  " << salida[1] << endl;
    cout << "salida[3] (Vocales Inv.): " << salida[2] << endl;
    cout << "salida[4] (Conson. Inv.): " << salida[3] << endl;
}

int main() {
    string salida[4]; 
    srand(time(0)); 
    
    cout << "Presione A para generar numeros aleatorios.\n";
    cout << "Presione B para procesar una frase.\n";

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
                cout << "\nOpcion no valida. Por favor, presione 'A' o 'B'.\n";
            }
            cout << "\nPresione A o B." << endl;
        }
        
        Sleep(100); 
    }

    return 0;
}
