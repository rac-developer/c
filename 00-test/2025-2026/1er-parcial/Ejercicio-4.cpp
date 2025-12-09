#include <iostream>
#include <cmath>

using namespace std;

bool esPrimo (int numero) {
	if (numero <= 1) return false;
	if (numero == 2) return true;
	if (numero % 2 == 0) return false;
	
	for (int i = 3; i*i <= numero; i += 2) {
		if (numero % i == 0) {
			return false;
		}
	}
	return true;
}

bool terminaEnTres (int numero) {
	return(numero % 10 == 3);
}

int main () {
	int encontrados = 0;
	int numero = 500000;

    cout << "Numero - Division entre 14 - Raiz Cuadrada y numero Primo\n" << endl;
		
	while (encontrados < 20) {
        // Verificamos si es divisible exactamente entre 4 (condición a)
        if (numero % 4 == 0) {
            // Verificamos si es divisible exactamente entre 6 (condición b)
            if (numero % 6 == 0) {
                // Calculamos la raíz cuadrada
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
		numero++;
	}
	
	return 0;
}
