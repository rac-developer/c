#include <iostream>
#include <cmath>

using namespace std;

// Funcion para verificar si termina en 1
bool terminaEnUno (int numero) {
	return (numero % 10 == 1);
}

int main () {
	int encontrados = 0;
	int numero = 50000;
	
    cout << "Numero terminado en uno – División entre 21 – Raíz Cuadrada que termina en uno

\n" << endl;
    
    while (encontrados < 20) {
    	
    	// Verificamos si el numero termina en 1 (condicion a)
    	if (terminaEnUno(numero)) {
    		
    		// Verifica si es divisible entre 21 (condicion b)
    		if (numero % 21 == 0) {
    			int division = numero / 21;
    			
    			// Calcula la raiz cuadrada de la operacion
    			double raiz = sqrt(division);
    			
    			// Verifica si es la raiz entera y termina en 1 (condicion c)
    			if (raiz == floor(raiz)) {
    				int raizEntera = (int)raiz;
    				
    				if (terminaEnUno(raizEntera)) {
    					cout << numero << " - " << division << " - " << raizEntera << endl;
    					encontrados++;
					}
				}
			}
		}
		numero++;
	}
	
	
	return 0;
}
