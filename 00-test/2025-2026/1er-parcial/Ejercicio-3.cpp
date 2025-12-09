#include <iostream>
#include <cmath>

using namespace std;

// Función para verificar si un número termina en 4
bool terminaEnCuatro(int numero) {
    return (numero % 10 == 4);
}

int main() {
    int encontrados = 0;
    int numero = 50000;  

	cout << "Numero - Division entre 4 - Division entre 6 - Raiz Cuadrada" << endl;
    
    while (encontrados < 20) {
        // Verificamos si es divisible exactamente entre 4 (condición a)
        if (numero % 4 == 0) {
            // Verificamos si es divisible exactamente entre 6 (condición b)
            if (numero % 6 == 0) {
                double raiz = sqrt(numero);
                
                // Verificamos si la raíz es entera y termina en 4 (condición c)
                if (raiz == floor(raiz)) {
                    int raizEntera = (int)raiz;
                    
                    if (terminaEnCuatro(raizEntera)) {
                        int division4 = numero / 4;
                        int division6 = numero / 6;
                        
                        cout << numero << " - " << division4 << " - " << division6 << " - " << raizEntera << endl;
                        encontrados++;
                    }
                }
            }
        }
        
        numero++;
    }
    
    return 0;
}
