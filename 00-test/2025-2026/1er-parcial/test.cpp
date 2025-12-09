#include <iostream>
using namespace std;

int main() {
    int mes, dia_mes, dia_semana;
    
    cout << "Programa para determinar en que año se cumple la combinacion dia + mes + dia de semana" << endl;
    cout << endl;
    
    // Pedir los datos al usuario
    cout << "Ingrese mes = ";
    cin >> mes;
    
    cout << "Ingrese Dia de mes = ";
    cin >> dia_mes;
    
    cout << "Ingrese Dia de semana (Dom=1 Lun=2 Mar=3 Mie=4 Jue=5 Vie=6 Sab=7) = ";
    cin >> dia_semana;
    
    cout << "Los años que se presentan esta combinacion entre 2025 y 2099 corresponden a:" << endl;
    cout << endl;
    
    // Verificar que los datos sean válidos
    if (mes < 1 || mes > 12) {
        cout << "Error: El mes debe estar entre 1 y 12" << endl;
        return 1;
    }
    
    if (dia_mes < 1 || dia_mes > 31) {
        cout << "Error: El dia del mes debe estar entre 1 y 31" << endl;
        return 1;
    }
    
    if (dia_semana < 1 || dia_semana > 7) {
        cout << "Error: El dia de semana debe estar entre 1 y 7" << endl;
        return 1;
    }
    
    // Algoritmo de Zeller para calcular el día de la semana
    // Fórmula: h = (q + ((13*(m+1))/5) + K + (K/4) + (J/4) - 2*J) mod 7
    // Donde:
    // h = día de la semana (0=sábado, 1=domingo, 2=lunes, ..., 6=viernes)
    // q = día del mes
    // m = mes (3=marzo, 4=abril, ..., 12=diciembre, 13=enero, 14=febrero)
    // K = año del siglo (año % 100)
    // J = siglo (año / 100)
    
    int contador = 0; // Para contar cuántos años encontramos
    
    // Probar todos los años desde 2025 hasta 2099
    for (int año = 2025; año <= 2099; año++) {
        int m = mes;
        int año_temp = año;
        
        // Ajustar para el algoritmo de Zeller (enero y febrero se consideran del año anterior)
        if (m < 3) {
            m += 12;
            año_temp--;
        }
        
        int q = dia_mes;
        int K = año_temp % 100;  // Año del siglo
        int J = año_temp / 100;  // Siglo
        
        // Aplicar la fórmula de Zeller
        int h = (q + (13*(m+1))/5 + K + (K/4) + (J/4) - 2*J;
        
        // Ajustar para que sea positivo
        h = h % 7;
        if (h < 0) {
            h += 7;
        }
        
        // Convertir a nuestro sistema (0=sábado, 1=domingo, ..., 6=viernes)
        // a (1=domingo, 2=lunes, ..., 7=sábado)
        int dia_semana_calculado;
        if (h == 0) {
            dia_semana_calculado = 7; // sábado
        } else if (h == 1) {
            dia_semana_calculado = 1; // domingo
        } else {
            dia_semana_calculado = h; // lunes=2, martes=3, etc.
        }
        
        // Verificar si coincide con el día de semana ingresado
        if (dia_semana_calculado == dia_semana) {
            cout << año << " ";
            contador++;
        }
    }
    
    cout << endl;
    cout << endl;
    cout << "Total de años encontrados: " << contador << endl;
    
    return 0;
}
