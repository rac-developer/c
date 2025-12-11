#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES

using namespace std;

struct elementos {
    double L1;
    double L2;
    double L3;
    double ang1;
    double ang2;
    double ang3;
};

// const double PI = 3.14159265;

void Calcular(double l1, double l2, double ang3deg, double *l3, double *a1, double *a2) {

    double ang3rad = ang3deg * (M_PI / 180.0);

    *l3 = sqrt(pow(l1, 2) + pow(l2, 2) - 2 * l1 * l2 * cos(ang3rad));

    double val_sen_a1 = (l1 * sin(ang3rad)) / (*l3);
    double ang1rad = asin(val_sen_a1);
    
    double val_sen_a2 = (l2 * sin(ang3rad)) / (*l3);
    double ang2rad = asin(val_sen_a2);

    *a1 = ang1rad * (180.0 / M_PI);
    *a2 = ang2rad * (180.0 / M_PI);
}

int main() {

    elementos triangulo;

    cout << "L1 = ";
    cin >> triangulo.L1;
    
    cout << "L2 = ";
    cin >> triangulo.L2;
    
    cout << "ang3 (deg): ";
    cin >> triangulo.ang3;

    Calcular(triangulo.L1, triangulo.L2, triangulo.ang3, &triangulo.L3, &triangulo.ang1, &triangulo.ang2);

    cout << "\nL3: " << triangulo.L3 << " - " << &triangulo.L3 << endl;
    cout << "ang1: " << triangulo.ang1 << " - " << &triangulo.ang1 << endl;
    cout << "ang3: " << triangulo.ang2 << " - " << &triangulo.ang2 << endl;

    return 0;
}