#include <stdio.h>

int main() {

//	Ejercio 1	
//	int x = 10;
//	while (x >= 1) {
//		printf("%d\n",x);
//		x = x-1;
//	//	x--;
//	}

// ----------------------------------------------------------------

//	Ejercicio 2

//	int secreto = 7, intento;
//	bool encontrado = true;
//	
////	Sin bool
//	
////	do {
////		printf("Adivine el numero de 1 al 10:");
////		scanf("%d", &intento);
////		
////		if ( intento != secreto) {
////			printf("Vuelve a intentarlo\n");
////		}
////	} while (intento != secreto); 
//
////	Con bool
//	
//	do {
//		printf("Adivine el numero de 1 al 10:");
//		scanf("%d", &intento);
//		
//		//1era condicion
//		
////		if ( intento != secreto) {
////			printf("Vuelve a intentarlo\n");
////		} else {
////			encontrado = false;
////		}
//		
//		//2da condicion ternario
//		
//		( intento != secreto ) ? printf("Vuelve a intentarlo\n") : encontrado = false;
//	} while (encontrado); 
//
//	printf("Correcto! El numero era %d\n", secreto);
	
// ----------------------------------------------------------------

//	Ejercicio 3

//	for (int i = 1; i<= 100; i++) {
//		if(i % 2 == 0) {
//			printf("%d\n", i);
//		}
//	}
	
// ----------------------------------------------------------------

//	Ejercicio 4

	float a,b;
	int opcion;
	bool salir = true;
	
/*	printf("Ingrese el valor a: ");
	scanf("%d", &a);
	printf("Ingrese el valor b: ");
	scanf("%d", &b);   */
	
	do {
		
		printf("Elije una opcion: ");
		scanf("%d", &opcion);
		
		if (opcion == 1) {
		printf("funciono");
		}else if (opcion == 2) {
		printf("Ingrese el valor b: ");
		}else if (opcion == 3) {
		printf("Ingrese el valor b: ");
		}else if (opcion == 4) {
		break;
		} else {
			printf("La opcion elegida no es valida");
		}	
			
	} while (salir);
	
	
	
	
	
	
	return 0;
}

