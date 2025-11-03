#include <iostream>

using namespace std;

int main () {

	struct Hogar {
		int personas;
		int numerotel;
		
		// Esto pone valores por defecto
		Hogar() {personas = 1; numerotel = 2;}
		
		int verPer () {return personas;}
		int savedPeople (int a) {personas = a;}
		
	} Castro, Mejias, Velasquez;
	Castro.personas = 4;
	Mejias.numerotel = 3;
	
	Castro = Mejias;
	
	cout << Castro.numerotel << endl;
	cout << Mejias.personas << endl;
	cout << Velasquez.personas << endl;
	
	Velasquez.savedPeople(4);
	cout << Velasquez.verPer() << endl;
	
	return 0;
}
