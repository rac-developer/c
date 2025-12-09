#include <iostream>
#include <cmath>

using namespace std;

// Funcion para saber si es primo
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

// Funcion para verificar si termina en 7
bool terminaEnSiete(int numero) {
	return (numero % 10 == 7);
}

int main () {
	int encontrados = 0;
	int numero = 100000;
	    
	cout << "Los 20 numeros que cumplen las condiciones son:" << endl;
    cout << "Numero - Raiz cuadrada (Primo que termina en siete)\n" << endl;
    
	while (encontrados < 20) {
		// Calcula la raiz
		double raiz = sqrt(numero);
		
		// Verifica si la raiz es un numero entreo
		if (raiz == floor(raiz)) {
			int raizEntera = (int)raiz;
			
			// Verifica si la raiz es primo y termina en 7
			if(esPrimo(raizEntera) && terminaEnSiete(raizEntera)) {
				cout << numero << " - " << raizEntera << endl;
				encontrados++;
			}
		}
		numero++;
	}
	return 0;
}
