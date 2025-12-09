#include <stdio.h>

int main() {

//	Ejercio 1. Contador regresivo (while)	
//	int x = 10;
//	while (x >= 1) {
//		printf("%d\n",x);
//		x = x-1;
//	//	x--;
//	}

// ----------------------------------------------------------------

//	Ejercicio 2. Número secreto (do-while)

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

//	Ejercicio 3. Números pares del 1 al 100 (for)

//	for (int i = 1; i<= 100; i++) {
//		if(i % 2 == 0) {
//			printf("%d\n", i);
//		}
//	}
	
// ----------------------------------------------------------------

//	Ejercicio 4. Menú interactivo (do-while)
//	
//	int opcion;
//	float a,b;
//	
//	do {
//		
//		printf("Elije una opcion: \n1. Sumar\n2. Restar\n3. Multiplicar\n4. Dividir\n5. Salir\n");
//		printf("Seleccione: ");
//		scanf("%d", &opcion);
//		
//		if(opcion >= 1 && opcion <= 4) {
//			printf("\nIngrese primer numero: ");
//            scanf("%f", &a);
//            printf("Ingrese segundo numero: ");
//			scanf("%f", &b);
//		}
//		
//		switch(opcion) {
//            case 1: printf("\nResultado: %.2f\n\n", a + b); break;
//            case 2: printf("\nResultado: %.2f\n\n", a - b); break;
//            case 3: printf("\nResultado: %.2f\n\n", a * b); break;
//            case 4: 
//                if(b != 0) {
//                    printf("\nResultado: %.2f\n\n", a / b);
//                } else {
//                    printf("Error: división por cero\n");
//                }
//                break;
//            case 5: break;
//            default: printf("\nOpcion invalida\n");
//        }
//	} while (opcion != 5);
	
// ----------------------------------------------------------------

//	Ejercicio 5. Factorial de un número (for)

//	int n, factorial = 1;
//	
//	printf("Ingrese un numero: ");
//	scanf("%d", &n);
//	
//	if (n < 0) {
//		printf("No existe factorial negativo de un numero negativo.\n");
//		scanf("&d", &n);
//	} else {
//		for (int i = 1; i <= n; i++){
//			factorial *= i;
//		}
//		printf("El factorial es %d es %d\n",n, factorial);
//	}
	
// ----------------------------------------------------------------

//	Ejercicio 6. Dígitos invertidos (while)

//	int numero, digito;
//	
//	printf("Ingrese un numero: ");
//	scanf("%d", &numero);
//	
//	printf("Digitos invertidos: ");
//	while(numero != 0) {
//		digito = numero % 10;
//		printf("%d", digito);
//		numero /= 10;
//	}
	
// ----------------------------------------------------------------

//	Ejercicio 7. Contador de caracteres (for)
	

	
// ----------------------------------------------------------------

//	Ejercicio 8. Contar positivos y negativos (for)
	
	int n, positivos, negativos = 0;
    float num;
    
    printf("¿Cuántos números desea ingresar? ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        printf("Ingrese número %d: ", i+1);
        scanf("%f", &num);
        
        if(num > 0) positivos++;
        else if(num < 0) negativos++;
    }
    
    printf("Positivos: %d\nNegativos: %d\n", positivos, negativos);

	return 0;
}

