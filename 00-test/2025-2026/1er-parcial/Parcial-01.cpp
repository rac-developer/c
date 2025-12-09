#include <iostream>
using namespace std;

// Función para calcular el día de la semana usando el algoritmo de Zeller
int calcularDiaSemana(int dia, int mes, int year) {
	// PASO 1: Ajustar enero y febrero como meses del año anterior
    if (mes < 3) {
        mes += 12;
        year--;
    }
    
    // PASO 2: Separar el año en siglo y año dentro del siglo
    int k = year % 100;  // Año dentro del siglo
    int j = year / 100;  // Siglo
    
    // PASO 3: Aplicar la fórmula de Zeller
    int h = (dia + (13 * (mes + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j)) % 7;
    
    // Ajustar para que 0 = Domingo
    h = (h + 6) % 7;
    
    return h;
}

// Función para obtener el nombre del día
void obtenerNombreDia(int diaNumero, char nombreDia[]) {
    char dias[7][10] = {
        "Domingo",
        "Lunes",
        "Martes",
        "Miercoles",
        "Jueves",
        "Viernes",
        "Sabado"
    };
    
    // Copiar el nombre del día al arreglo proporcionado
    int i = 0;
    while (dias[diaNumero][i] != '\0') {
        nombreDia[i] = dias[diaNumero][i];
        i++;
    }
    nombreDia[i] = '\0';
}

int main() {
    int year;
    
    cout << "Ingrese el ano a buscar (2024 - 2099) = ";
    cin >> year;
    
    // Verificar que el año esté en el rango válido
    if (year < 2024 || year > 2099) {
        cout << "Error: El ano debe estar entre 2024 y 2099" << endl;
        return 1;
    }
    
    cout << "\nLos dias feriados para " << year << " corresponderan a:\n" << endl;
    
    // Arrays con los días feriados fijos (día, mes)
    int feriados[][2] = {
        {1, 1},   // 01 de enero
        {19, 4},  // 19 de abril
        {1, 5},   // 01 de mayo
        {24, 6},  // 24 de junio
        {5, 7},   // 05 de julio
        {24, 7},  // 24 de julio
        {12, 10}, // 12 de octubre
        {24, 12}, // 24 de diciembre
        {25, 12}, // 25 de diciembre
        {31, 12}  // 31 de diciembre
    };
    
    // Nombres de los feriados como arreglos de caracteres
    char nombresFeriados[10][80] = {
        "01 de enero: Ano Nuevo",
        "19 de abril: Declaracion de la Independencia",
        "01 de mayo: Dia del trabajador",
        "24 de junio: Aniversario de la Batalla de Carabobo",
        "05 de Julio: Inicio de la firma del acta de la independencia",
        "24 de Julio: Natalicio de Simon Bolivar",
        "12 de octubre: Dia de la resistencia indigena",
        "24 de diciembre: Vispera de Navidad",
        "25 de diciembre: Navidad",
        "31 de diciembre: Fin de ano"		
    };
    
    // Calcular y mostrar cada feriado
    for (int i = 0; i < 10; i++) {
        int dia = feriados[i][0];
        int mes = feriados[i][1];
        
        int diaSemana = calcularDiaSemana(dia, mes, year);
        char nombreDia[10];
        obtenerNombreDia(diaSemana, nombreDia);
        
        cout << nombresFeriados[i] << " = " << nombreDia << endl;
    }
    
    return 0;
}
