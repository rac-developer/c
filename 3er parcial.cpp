#include <stdio.h>

int main() {
	int opcion, input_value = 0;
	
	do {
		printf("\nMenu principal:\n");
		printf("1. Multiplicar y ordenar numeros\n");
        printf("2. Contar vocales en letras\n");
        printf("3. Calcular promedios de estudiantes\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        
        int input_valid = 0;
        while(!input_valid) {
            if(scanf("%d", &opcion) != 1) {
                printf("Entrada no numerica! Ingrese 1-4: ");
                // Limpiar buffer manualmente
                while(1) {
                    char c;
                    if(scanf("%c", &c) != 1) break;
                    if(c == '\n') break;
                }
            } else if(opcion < 1 || opcion > 4) {
                printf("Opcion invalida! Ingrese 1-4: ");
            } else {
                input_valid = 1;
            }
        }
        
        switch(opcion) {
        	case 1: {
        		int original [5], multiplicados[5], ordenados[5], i;
        		printf("\nIngrese 5 numeros enteros:\n");
        		
        		for (i = 0; i < 5; i++) {
        			printf("Numero %d: ", i+1);
        			
        			//Validacion
        			int num_valido = 0;
        			while(!num_valido) {
		        	if(scanf("%d",&original[i]) != 1) {
			        		printf("No es un numero! Ingrese entero: ");
			        		while(1) {
			        			char c;
			        			if(scanf("%c", &c) != 1) break;
			        			if(c == '\n') break;
							}
						} else {
							num_valido = 1;
						}
					}
        			multiplicados[i] = original[i] *2;
        			ordenados[i] = multiplicados[i];
				}
				
				for(i = 0; i < 5; i++) {
					for(int j = i+1; j < 5; j++) {
						if(ordenados[i] > ordenados[j]) {
							int temp = ordenados[i];
							ordenados[i] = ordenados[j];
							ordenados[j] = temp;
						}
					}
				}
				
				printf("\nResultados ordenados:\n");
				for(i = 0; i < 5; i++) {
					printf("%d ", ordenados[i]);
				}
				
        		printf("\n");
				break;
			}
			case 2: {
				char letras[10];
				int vocales[5] = {0}, i;
				
				printf("Ingrese 10 letras (A-Z o a-z):\n");
				
				for (i = 0; i < 10; i++) {
					printf("Letra %d: ", i+1);
					
					int letra_valid = 0;
					while(!letra_valid) {
						if (scanf(" %c", &letras[i]) !=1) {
							printf("Entrada invalida! Ingrese letra: ");
							while(1) {
								char c;
								if(scanf("%c", &c) != 1) break;
								if (c == '\n') break;
							} 
						} else if (!((letras[i] >= 'A' && letras[i] <= 'Z') || (letras[i] >= 'a' && letras[i] <= 'z'))) {
                        	printf("No es letra! Ingrese A-Z o a-z: ");
						} else {
							letra_valid = 1;
						}
					}
					switch(letras[i]) {
                        case 'a': case 'A': vocales[0]++; break;
                        case 'e': case 'E': vocales[1]++; break;
                        case 'i': case 'I': vocales[2]++; break;
                        case 'o': case 'O': vocales[3]++; break;
                        case 'u': case 'U': vocales[4]++; break;
					}
				}
				printf("\nVocales encontradas:\n");
                printf("a/A: %d\n", vocales[0]);
                printf("e/E: %d\n", vocales[1]);
                printf("i/I: %d\n", vocales[2]);
                printf("o/O: %d\n", vocales[3]);
                printf("u/U: %d\n", vocales[4]);
				break;
			}
			case 3:{
				char nombres[4][50];
				float notas[4][3], promedios[4];
				int aprobados = 0, reprobados = 0, i;
				
				for (i = 0; i < 4; i++) {
					printf("\nEstudiante %d: \n", i+1);
					
					printf("Nombre: ");
					int name_valid = 0;
					while(!name_valid) {
						if(scanf("%49s", nombres[i]) != 1) {
							printf("Nombre invalido! Ingrese solo letras: ");
							while(1) {
								char c;
								if(scanf("%c", &c) != 1) break;
								if(c == '\n') break;
							}
						} else {
							int j = 0;
							name_valid = 1;
							while(nombres[i][j] != '\0') {
                                if(!((nombres[i][j] >= 'A' && nombres[i][j] <= 'Z') || 
                                    (nombres[i][j] >= 'a' && nombres[i][j] <= 'z'))) {
                                    input_valid = 0;
                                    break;
                                }
                                j++;
                            }
                            if(!input_valid) {
                                printf("Solo letras! Ingrese nombre valido: ");
						}
					}	
				}
				// Validación notas (0-10)
                    for(int j = 0; j < 3; j++) {
                        printf("Nota %d (0-10): ", j+1);
                        input_valid = 0;
                        while(!input_valid) {
                            if(scanf("%f", &notas[i][j]) != 1) {
                                printf("No es numero! Ingrese 0-10: ");
                                // Limpieza manual
                                while(1) {
                                    char c;
                                    if(scanf("%c", &c) != 1) break;
                                    if(c == '\n') break;
                                }
                            } else if(notas[i][j] < 0 || notas[i][j] > 10) {
                                printf("Rango 0-10! Ingrese nota valida: ");
                            } else {
                                input_valid = 1;
                            }
                        }
                    }
                    
                    promedios[i] = (notas[i][0] + notas[i][1] + notas[i][2]) / 3;
                    if(promedios[i] >= 6.0) aprobados++;
                    else reprobados++;
                }
                
                printf("\nReporte:\n");
                for(int i = 0; i < 4; i++) {
                    printf("%s: %.1f, %.1f, %.1f = %.2f (%s)\n", 
                          nombres[i], notas[i][0], notas[i][1], notas[i][2],
                          promedios[i], promedios[i] >= 6.0 ? "Aprobado" : "Reprobado");
                }
                
                printf("\nResumen: Aprobados=%d, Reprobados=%d\n", aprobados, reprobados);
                break;
			}
			case 4: {
				printf("\nSaliendo del programa...\n");
                return 0;
			}
		}
	} while(opcion != 4);
	
	return 0;
}
