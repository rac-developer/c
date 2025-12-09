#include <stdio.h>

int main() {

//	Ejercio 1. Leer 5 números, copiarlos multiplicados por 2 y mostrar el segundo array.	

	int numeros[5], multiplicados[5];
    
    printf("Ingrese 5 numeros:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &numeros[i]);
        multiplicados[i] = numeros[i] * 2;
    }
    
    printf("Array multiplicado por 2:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", multiplicados[i]);
    }
    printf("\n");


	return 0;
}

