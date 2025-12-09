#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

const int MAX_CUOTAS = 48;

struct Prestamo {
    double monto_solicitado;
    double tasa_interes_anual; 
    int cuotas_iniciales; 
    int realizar_pago_extra; 
    int periodo_extra; 
    double monto_extra; 
};

// === FUNCIONES ===

void limpiar_buffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void solicitar_datos(Prestamo &datos) {
    cout << fixed << setprecision(2);
    // cout << "--- SISTEMA DE PRESTAMOS ---\n\n";

    do {
        cout << "Ingrese monto del prestamo a solicitar (10000 a 500000$) = ";
        cin >> datos.monto_solicitado;
    } while (datos.monto_solicitado < 10000.0 || datos.monto_solicitado > 500000.0);

    do {
        cout << "Ingrese el interes del prestamo (3.5 - 10%) = ";
        cin >> datos.tasa_interes_anual;
        if (datos.tasa_interes_anual < 3.5 || datos.tasa_interes_anual > 10.0) {
            cout << "Dato incorrecto. ";
        }
    } while (datos.tasa_interes_anual < 3.5 || datos.tasa_interes_anual > 10.0);

    do {
        cout << "Ingrese la cantidad de cuotas de pago (12 - 48 meses) = ";
        cin >> datos.cuotas_iniciales;
    } while (datos.cuotas_iniciales < 12 || datos.cuotas_iniciales > 48);

    do {
        cout << "Ingrese (1) si desea hacer un pago extraordinario / Ingrese (2) si NO desea hacer pagos extraordinarios = ";
        cin >> datos.realizar_pago_extra;
    } while (datos.realizar_pago_extra != 1 && datos.realizar_pago_extra != 2);

    if (datos.realizar_pago_extra == 1) {
        do {
            cout << "Ingrese el periodo cuando realizara el pago extraordinario = ";
            cin >> datos.periodo_extra;
        } while (datos.periodo_extra < 1 || datos.periodo_extra >= datos.cuotas_iniciales);

        cout << "Ingrese el monto del pago extraordinario = ";
        cin >> datos.monto_extra;
    } else {
        datos.periodo_extra = 0;
        datos.monto_extra = 0.0;
    }

}

// *** AQUÍ ESTÁ LA FÓRMULA DEL EXCEL ***
// P = Monto (Principal)
// i = Interés (0.04)
// n = Periodo (48)
// cuota = (monto * Interes) / (1 - ((interes + 1)^-Periodo))
double calcular_cuota_fija(double P, double i, int n) {
    if (i == 0.0) return P / n;
    
    // pow(base, exponente). Nota el '-n' para hacerlo negativo
    double denominador = 1.0 - pow(i + 1.0, -n); 
    
    return (P * i) / denominador;
}

void generar_tabla(const Prestamo &datos, double cuota_fija, double arr_interes[], double arr_aporte[], double arr_saldo[], int &cuotas_finales) {
    double saldo_pendiente = datos.monto_solicitado;
    double tasa_mensual_decimal = datos.tasa_interes_anual / 100.0;
    int i = 0;

    while (saldo_pendiente > 0.01 && i < MAX_CUOTAS) {
        double interes_mes = saldo_pendiente * tasa_mensual_decimal;
        double aporte_capital = 0.0;
        
        // Ajuste última cuota
        if (saldo_pendiente + interes_mes <= cuota_fija + 0.1) { // +0.1 margen de error
             aporte_capital = saldo_pendiente;
             saldo_pendiente = 0.0;
        } else {
             aporte_capital = cuota_fija - interes_mes;
             saldo_pendiente -= aporte_capital;
        }

        // Pago extraordinario
        if (datos.realizar_pago_extra == 1 && (i + 1) == datos.periodo_extra) {
            saldo_pendiente -= datos.monto_extra;
            if (saldo_pendiente < 0) saldo_pendiente = 0.0;
        }

        arr_interes[i] = interes_mes;
        arr_aporte[i] = aporte_capital;
        arr_saldo[i] = saldo_pendiente;
        
        i++;
    }
    cuotas_finales = i;
}

void escribir_reporte(ostream &salida, const Prestamo &datos, const double arr_interes[], const double arr_aporte[], const double arr_saldo[], int cuotas_finales, double cuota_fija) {
    double total_intereses = 0.0;

    salida << fixed << setprecision(2);
    salida << "\nPRESTAMO = " << datos.monto_solicitado << endl;
    
    // Mostramos el % como entero si es exacto, o decimal si no
    salida << "INTERES = " << datos.tasa_interes_anual << "%" << endl; 
    salida << "PERIODO = " << datos.cuotas_iniciales << endl;
    
    salida << "\nNro       Couta         Interes       Aporte        Monto Pendiente" << endl;
    
    for (int i = 0; i < cuotas_finales; i++) {
        total_intereses += arr_interes[i];
        
        double cuota_mes = cuota_fija;
        // Ajuste visual de la última cuota para que cuadre Aporte + Interes
        if (i == cuotas_finales - 1) {
             cuota_mes = arr_aporte[i] + arr_interes[i];
        }

        salida << setfill('0') << setw(2) << i + 1 << setfill(' '); // Formato 01, 02...
        salida << setw(13) << cuota_mes;
        salida << setw(13) << arr_interes[i];
        salida << setw(13) << arr_aporte[i];
        salida << setw(14) << arr_saldo[i];

        if (datos.realizar_pago_extra == 1 && (i + 1) == datos.periodo_extra) {
            salida << "  ------->   Couta Extraordinaria = " << datos.monto_extra;
        }
        salida << endl;
    }
    
    salida << "Total intereses pagados = " << total_intereses << endl;
    salida << "Total pagado = " << datos.monto_solicitado << " + " << total_intereses << " = " << datos.monto_solicitado + total_intereses << endl;
}

void imprimir_tabla(const Prestamo &datos, const double arr_interes[], const double arr_aporte[], const double arr_saldo[], int cuotas_finales, double cuota_fija) {
    escribir_reporte(cout, datos, arr_interes, arr_aporte, arr_saldo, cuotas_finales, cuota_fija);
}

void guardar_archivo(const Prestamo &datos, const double arr_interes[], const double arr_aporte[], const double arr_saldo[], int cuotas_finales, double cuota_fija) {
    int opcion;
    cout << "\nDesea guardar la informacion en un archivo de texto presione (1)\n";
    cout << "Presione cualquier otra tecla para salir\n";
    cin >> opcion;

    if (opcion == 1) {
        string ruta_archivo;
        cout << "Ingrese ruta y nombre de archivo, recuerde colocar\nla extension del archivo(Por ejemplo D:\\yoyo.txt):\n";
        
        limpiar_buffer();
        getline(cin, ruta_archivo);

        ofstream archivo_salida(ruta_archivo.c_str());

        if (archivo_salida.is_open()) {
            escribir_reporte(archivo_salida, datos, arr_interes, arr_aporte, arr_saldo, cuotas_finales, cuota_fija);
            archivo_salida.close();
            cout << "\nArchivo creado y data ingresada!!\n";
        } else {
            cout << "Error al crear el archivo.\n";
        }
    }
}

// === MAIN ===

int main() {
    Prestamo mi_prestamo;
    double cuota_fija = 0.0;
    int cuotas_finales = 0;

    // Inicializamos arreglos en 0
    double arr_interes[MAX_CUOTAS] = {0.0};
    double arr_aporte[MAX_CUOTAS] = {0.0};
    double arr_saldo[MAX_CUOTAS] = {0.0};

    solicitar_datos(mi_prestamo);

    // OConvertierte el porcentaje a decimal (4% -> 0.04)
    double tasa_mensual_decimal = mi_prestamo.tasa_interes_anual / 100.0;

    // Calculamos la cuota
    cuota_fija = calcular_cuota_fija(mi_prestamo.monto_solicitado, tasa_mensual_decimal, mi_prestamo.cuotas_iniciales);

    // Generamos los datos
    generar_tabla(mi_prestamo, cuota_fija, arr_interes, arr_aporte, arr_saldo, cuotas_finales);

    // Imprimimos en pantalla
    imprimir_tabla(mi_prestamo, arr_interes, arr_aporte, arr_saldo, cuotas_finales, cuota_fija);

    // Preguntamos si guardar
    guardar_archivo(mi_prestamo, arr_interes, arr_aporte, arr_saldo, cuotas_finales, cuota_fija);

    cout << "\nPresione Enter para salir...";
    limpiar_buffer();
    cin.get();
    return 0;
}