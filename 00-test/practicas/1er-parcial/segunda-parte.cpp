#include<iostream>
#include<math.h>

using namespace std;

main() {
	int contador=1;
	int numero =100000;
	double raiz;
	int divisor;
	double residuo;
	int aux;
	int aux1;
	
	while (contador <=20) {
		raiz=sqrt(numero);
		aux=raiz;
		if(raiz-aux==0){
			for (divisor=2;divisor<=raiz;divisor=divisor+1) {
				residuo=aux%divisor;
				if(residuo==0){
					if(divisor<raiz) {
						break;
					} else {
						aux1=raiz+3;
						if(aux1%10==0) {
							if(contador <=20) {
								cout << " (" << contador << ") " <<numero << " - " <<raiz <<endl;
							}
							contador=contador+1;
						}
					}
				}
			}
		}
		numero=numero+1;
	}
}
