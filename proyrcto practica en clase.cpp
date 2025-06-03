// haga un programa con 4 opciones, 1. de la tabla de multiplicar, 2. el numero mayor entre 5 numeros, 3. la suma de 10 numeros, 4. fin y regreso //

#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	int opc = 0, numero1 = 0, numero2 = 0;
	do{
		
      system("cls");
	 
	 printf("MENU DE OPCIONES \n\n");
	
     printf("1. Tablas de multiplicar \n");
	 printf("2. Suma de numeros \n");
	 printf("3. Numero mayor y menor \n");
	 printf("4. Salir \n\n");
	 printf("5. Opcion a escoger: ");
	 scanf("%d", &opc);
	 switch(opc){
	 	
		// Empezamos con las tablas de multiplicar //  
		 
		 case 1:
	 		system("cls");
	
	 		int i, r, n; 

      printf("Que tabla de multiplicar quieres saber? \n\n");

        printf("Ingrese el primero numero: ");
        scanf("%d", &n);	
   
      for(i=1; i<=10; i++){
   	
   	    r = i * n; 
	   
	   printf("\n %d x %d = %d", n, i, r);
   	
       }
		   break;	
	 	  
		   // Hacemos la operacion de la suma //
	 	 
		   case 2:
	 	  	system("cls");

	
	  int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, resultado_suma;
	
	
       printf("\n\n Comenzamos con la operacion de la suma \n\n");

     	printf("Ingrese el primer numero de la suma: ");
    	scanf("%d", &n6);
    	printf("Ingrese el segundo numero de la suma: ");
    	scanf("%d", &n7);
	    printf("Ingrese el tercer numero de la suma: ");
     	scanf("%d", &n8);
	    printf("Ingrese el cuarto numero de la suma: ");
	    scanf("%d", &n9);
	    printf("Ingrese el quinto numero de la suma: ");
	    scanf("%d", &n10);
	    printf("Ingrese el primer numero de la suma: ");
	    scanf("%d", &n11);
	    printf("Ingrese el segundo numero de la suma: ");
	    scanf("%d", &n12);
	    printf("Ingrese el tercer numero de la suma: ");
	    scanf("%d", &n13);
	    printf("Ingrese el cuarto numero de la suma: ");
	    scanf("%d", &n14);
	    printf("Ingrese el quinto numero de la suma: ");
	    scanf("%d", &n15);

	  resultado_suma = n6 + n7 + n8 + n9 + n10 + n11 + n12 + n13 + n14 + n15;
	
	  printf(" \n El resultado de la suma es: %d \n\n", resultado_suma);
	
	 	break;
	 	
	 	// colocamos los numeros mayor y menor //
		
		 case 3:
	 		system("cls");
	 		printf("Comenzamos con la operacion de numero mayor y menor \n\n");
	
	   printf("Coloque el primer numero: ");
	   scanf("%d", &n1);
	   printf("Coloque el segundo numero: ");
	   scanf("%d", &n2);
	   printf("Coloque el tercero numero: ");
	   scanf("%d", &n3);
	   printf("Coloque el cuarto numero: ");
	   scanf("%d", &n4);
	   printf("Coloque el quinto numero: ");
	   scanf("%d", &n5);
	
		if( n1 < n2 && n1 < n3 && n1 < n4 && n1 < n5 ){
		printf(" \n %d es el numero menor \n", n1);
	  }
	   else if( n2 < n1 && n2 < n3 && n2 < n4 && n2 < n5 ){
		printf("\n %d es el numero menor \n", n2);
	  }
	   else if( n3 < n2 && n3 < n1 && n3 < n4 && n3 < n5 ){
		printf("\n %d es el numero menor \n", n3);
	  }
	   else if ( n4 < n2 && n4 < n3 && n4 < n1 && n4 < n5 ){
		printf("\n %d es el numero menor \n", n4);
	  }
	   else if ( n5 < n2 && n5 < n3 && n5 < n4 && n5 < n1 ){
		printf("\n %d es el numero menor \n", n5);
	  }
	   else
	  {
	   printf("\n Error");
	  }

    	if ( n1 > n2 && n1 > n3 && n1 > n4 && n1 > n5 ){
		printf("\n %d es el numero mayor \n", n1);
	  }
	   else if( n2 > n1 && n2 > n3 && n2 > n4 && n2 > n5 ){
		printf("\n %d es el numero mayor \n", n2);
   	  }
	   else if( n3 > n2 && n3 > n1 && n3 > n4 && n3 > n5 ){
		printf("\n %d es el numero mayor \n", n3);
	  }
	   else if ( n4 > n2 && n4 > n3 && n4 > n1 && n4 > n5 ){
		printf("\n %d es el numero mayor \n", n4);
	  }
	   else if ( n5 > n2 && n5 > n3 && n5 > n4 && n5 > n1 ){
		printf("\n %d es el numero mayor \n", n5);
	  }
	   else
	  {
		printf("\n Error");
	  }
	 

	  break;
	  
	  case 4:
	  	break;
	  
	  default:
	  	system("cls");
	  	printf("La opcion que ingreso es incorrecta");

	 	break;
	 }	
	
		
	}while(opc != 4);
	
return 0;
}
