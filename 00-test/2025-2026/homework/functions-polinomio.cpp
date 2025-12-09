/* Este programa le envia una funcion a los coeficinetes
de un polinomio ed 2do grado para determinar las raices
usando la resolvente de 2do grado. */

using namespace std;
#include <iostream>
#include <cmath>

// double calcular(int a, int b, int c) {
//     int raiz1;
//     int raiz2;
//     double suma;

//     raiz1 = (-b + sqrt(pow(b,2)-4*a*c))/(2*a);
//     raiz2 = (-b - sqrt(pow(b,2)-4*a*c))/(2*a);

//     cout<< "\nLas raices del polinomio " << a << "x^2 + " << "(" << b << "x) + (" << c << ") = 0 son: " <<endl;
//     system("pause");
//     cout<< "Raiz Nro 1: " << raiz1 << endl;
//     system("pause");
//     cout<< "Raiz Nro 2: " << raiz2 << endl << endl<< endl;

//     suma=raiz1+raiz2;

//     // return para que regrese al programa principal
//     return suma;
// }

// Se usan punteros cuando se espero que retorne mas de un valor

int calcular(int *puntero1, int *puntero2, int *puntero3, int *a, int *b, int *c) {

    *a=*puntero1;
    *b=*puntero2;
    *c=*puntero3;

    *a=*a+100;
    *b=*b+100;
    *c=*c+100;
}

main () {
    // double respuesta1,respuesta2;

    // Saquemos las raices del polinomio x^2 - 1x -6 = 0 => (x-3)(x+2) = 0
    // respuesta1= calcular(1,-1,-6);
    // cout << respuesta1 << endl;
    
    int v1=14, v2=33, ff=35;
    int r1,r2,r3;

    calcular(&v1,&v2,&ff,&r1,&r2,&r3);

    cout << v1 << endl;
    cout << v2 << endl;
    cout << ff << endl << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;

    return 0;
}