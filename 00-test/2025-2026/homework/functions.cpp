#include <iostream>
using namespace std;

main() {
    float notas[11];
    string nombre[21]={""};
    string opcion="s";
    int n, i, j=1;
    float notas_finales[21]={0};
    float promedio(float valores[], int cantidad); 

    cout<<"Elaborado por Carlos Ferrer"<<endl;

    while ((opcion== "s" or opcion == "S") and j<20) {
        cout<<"Escriba el apellido del alumno nro "<<j<<" (Max 20)= ";
        cin>> nombre[j];
        n=0;
        
        while(n<1 or n>10) {
            cout<<"Cuantas notas tiene "<<nombre[j]<<" (Max 10)= ";
            cin>> n;
        }

        for (i = 0; i < n; i=i+1) {
            notas[i]=-1;
            while(notas[i]<0 or notas[i]>20) {
                cout<<"  Nota "<< i + 1<<" (Rango 0-20)= ";
                    cin>> notas[i];
            }
        }
        notas_finales[j]=promedio(notas, n);
        cout<<"El promedio de "<<nombre[j]<<" es: "<< notas_finales[j]<<endl;

        cout<<"Desea calcular mas promedios (S=continuar)? ";
        cin>> opcion;
        j=j+1;
        system ("cls");
    } i=1;
    
    cout <<endl<<"RESUMEN"<<endl;
    
    while (nombre[i] != "" and i<21) {
        cout<<"El alumno "<<nombre[i]<<" tiene un promedio de = "<<notas_finales[i]<<endl;
        i=i+1;
    }

}

float promedio (float valores[], int cantidad) {

    int i;
    float suma = 0.0;     /*El ciclo for cuenta el número de notas que desea promediar*/

    for (i = 0; i < cantidad; i=i+1)

    {
    suma=suma+valores[i];
    }

    suma=suma/cantidad;
    return suma;

}   