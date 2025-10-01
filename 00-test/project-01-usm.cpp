#include <iostream>
using namespace std;

int main() {
	
    int dia = 0; 
	int mes = 0;
	int year = 0;
    
    // Dia
    cout << "Ingrese el dia a validar (1-31): ";
    cin >> dia;
    
    if (dia < 1) {
        cout << "Error: El dia no puede ser menor a 1" << endl;
        return 1;
    }
    
    // Mes
	cout << "Ingrese el mes a validar (1-12): ";
	cin >> mes;
	
    if (mes < 1 || mes > 12) {
        cout << "Error: El mes debe estar entre 1 y 12" << endl;
        return 1;
    }
	
	// A�o
    cout << "Ingrese el a#o a validar (>2025): ";
    cin >> year;
    
    if (year < 2025 || (year == 2025 && mes < 1) || (year == 2025 && mes == 1 && dia < 1)) {
        cout << "Error: La fecha debe ser posterior al 1ro de enero de 2025" << endl;
        return 1;
    }

    bool esBisiesto = false;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        esBisiesto = true;
    }
    
    int diasEnMes;
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasEnMes = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasEnMes = 30;
            break;
        case 2:
            if (esBisiesto) {
                diasEnMes = 29;
            } else {
                diasEnMes = 28;
            }
            break;
    }
    
    if (dia > diasEnMes) {
        cout << "Error: El mes " << mes << " del a�o " << year;
        cout << " tiene " << diasEnMes << " dias" << endl;
        return 1;
    }
    
    int diasTotales = 0;
    
    for (int a = 2025; a < year; a++) {
        bool bisiesto = false;
        if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
            bisiesto = true;
        }
        
        if (bisiesto) {
            diasTotales += 366;
        } else {
            diasTotales += 365;
        }
    }
    
    for (int m = 1; m < mes; m++) {
        switch (m) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                diasTotales += 31;
                break;
            case 4: case 6: case 9: case 11:
                diasTotales += 30;
                break;
            case 2:
                if (esBisiesto) {
                    diasTotales += 29;
                } else {
                    diasTotales += 28;
                }
                break;
        }
    }
    
    diasTotales += (dia - 1);
    
    cout << "\nEl " << dia << "/" << mes << "/" << year;

    if (diasTotales % 5 == 0) {
        cout << " la farmacia esta de turno" << endl;
    } else {
        cout << " la farmacia no esta de turno" << endl;
    }
    
    return 0;
}
