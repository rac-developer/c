#include <iostream>
using namespace std;

int main() {
    int mes, diaMes, diaSemana;
    
    cout << "Programa para determinar en que año se cumple la combinacion dia + mes + dia de semana" << endl;
    cout << endl;
    
    // Pedir los datos al usuario
    cout << "Ingrese mes = ";
    cin >> mes;
    
    cout << "Ingrese Dia de mes = ";
    cin >> diaMes;
    
    cout << "Ingrese Dia de semana (Dom=1 Lun=2 Mar=3 Mie=4 Jue=5 Vie=6 Sab=7) = ";
    cin >> diaSemana;
    
    int contador = 0;
    int years[100]; // Arreglo para guardar los años

    int diaActual = 4; // 1 de enero de 2025 = miércoles = 4

    for (int year = 2025; year <= 2099; year++) {
        // Días por mes (para año no bisiesto)
        int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Verificar si el año es bisiesto
        bool bisiesto = false;
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0) {
                    bisiesto = true;
                }
            } else {
                bisiesto = true;
            }
        }
        
        // Ajustar febrero si es bisiesto
        if (bisiesto) {
            diaMes[1] = 29;
        }
        
        // Calcular el día de la semana para el 1 de este mes
        int diaInicioMes = diaActual;
        
        // Sumar días de meses anteriores hasta llegar al mes deseado
        for (int m = 1; m < mes; m++) {
            diaInicioMes += diaMes[m-1];
        }
        
        // Calcular el día de la semana para la fecha específica
        int diaFecha = (diaInicioMes + diaMes - 1) % 7;
        if (diaFecha == 0) diaFecha = 7; // Ajustar de 0 a 7 (sábado)
        
        // Verificar si coincide con el día de semana ingresado
        if (diaFecha == diaSemana) {
            years[contador] = year;
            contador++;
        }
        
        // Preparar para el próximo año: calcular el día de la semana del 1 de enero del próximo año
        int diasEnEsteAño = bisiesto ? 366 : 365;
        diaActual = (diaActual + diasEnEsteYear) % 7;
        if (diaActual == 0) diaActual = 7;
    }
    
    // Mostrar resultados
    cout << "Los anos que se presentan esta combinacion entre 2025 y 2099 corresponden a: " << contador << endl;
    
    for (int i = 0; i < contador; i++) {
        cout << years[i] << " ";
    }
    cout << endl;
    
    return 0;
}
