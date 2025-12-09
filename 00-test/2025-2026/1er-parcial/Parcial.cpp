#include <iostream>
	
using namespace std;

int main () {
	int mes;
	int diaMes;
	int diaSemana;
	
    cout << "Ingrese mes = ";
    cin >> mes;
    
    cout << "Ingrese Dia de mes = ";
    cin >> diaMes;
    
    cout << "Ingrese Dia de semana (Dom=1 Lun=2 Mar=3 Mie=4 Jue=5 Vie=6 Sab=7) = ";
    cin >> diaSemana;
    
    int contador = 0;
    int years[100];
    
    for(int year = 2025; year <= 2099; year++) {
    	int m = mes;
        int year_temp = year;
        
        if (m < 3) {
            m += 12;
            year_temp--;
        }
        
        int q = diaMes;
        int K = year_temp % 100;  
        int J = year_temp / 100;  
        
        int h = (q + (13*(m+1))/5 + K + (K/4) + (J/4) - 2*J);
        
        h = h % 7;
        if (h < 0) {
            h += 7;
        }
        
        int dia_semana_calculado;
        if (h == 0) {
            dia_semana_calculado = 7; 
        } else if (h == 1) {
            dia_semana_calculado = 1; 
        } else {
            dia_semana_calculado = h; 
        }
        
        if (dia_semana_calculado == diaSemana) {
            years[contador] = year;
            contador++;
        }
    }
    
    cout << "Los anos que se presentan esta combinacion entre 2025 y 2099 corresponden a: " << endl;
    
    for (int i = 0; i < contador; i++) {
        cout << years[i] << " ";
    }
    cout << endl;
    
    return 0;
}
