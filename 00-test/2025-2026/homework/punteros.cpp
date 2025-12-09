#include <iostream>
using namespace std;

main() {
    int valor1 = 14;

    /* El operador * me indica a mi que la 
    proxima etiqueta no es una posicion de 
    valor fija, si no, que es un elemento 
    que va a cambiar en cierta posicion */

    /* El operador & cuando se usa delante
    de una variable existente en una expresión,
    el operador & devuelve la dirección de
    memoria donde se almacena esa variable.
    El resultado es un puntero al tipo de
    la variable.  */

    int *puntero;

    puntero = &valor1;

    cout << *puntero << endl;
    // 14
    cout << puntero << endl;
    // 0xf9449ff704

    int valores[3]={-2,18,100};

    puntero=&valores[0];

    cout << *puntero << endl;
    // -2

    puntero=puntero+1;

    cout << *puntero << endl;
    // 18

    cout << "---------" << endl;

    // ------- Variable tipo string ------

    string yoyo = "Caracas-Venezuela";
    string yoyo1="Sudamerica";

    string *puntero2;

    puntero2 = &yoyo;

    cout << puntero2 << endl;
    // Caracas-Venezuela

    puntero2 = &yoyo1;

    cout << puntero2 << endl;
    // Sudamerica

    for (int i = 0; i < yoyo.size(); i=i+1) {
        char *puntero3;
        puntero3 = &yoyo[i];
        cout << i << " - " << *puntero3 << " " << puntero3 << " - " << &puntero3 << endl;
    }
}