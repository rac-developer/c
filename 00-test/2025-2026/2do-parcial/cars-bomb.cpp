/* Programa de desactivación de la bomba de la película 

Cars 2 utilizando la técnica del Kbhit y del Getch de 

la biblioteca Conio.h

 

Rev 0;

Elaborado: Carlos Ferrer

*/

#include <iostream>

#include <windows.h>

#include <conio.h>

#include <locale.h>

using namespace std;



main()

{

int min=5,seg=0;

char tecla,aux1='*',aux2='*';

setlocale(LC_ALL,"spanish");



repite:

/* Detectamos si se pisa una tecla del teclado

cero = no se ha pisado nada / Cualquier valor

distinto se piso una tecla*/

if(kbhit()==0)

	{

// implementamos un reloj de 5 minutos descendiente

	if (seg!=0)

		{

		seg=seg-1;

		}

	else

		{

		seg=59;

		min=min-1;

		}

	Sleep(800);

	Beep(250,200);



//Presentamos los datos de la bomba

	system("cls");

	cout <<"Tiempo para explosión "<<min<<":"<<seg<<"  clave de desactivación= "<<aux1<<aux2;



// Si se agota el tiempo explotamos la bomba

	if (min<=0 or (min==0 and seg==0))

		{		

		system ("cls");

		cout <<"BOOOOOM"<<endl;

		Beep (75,1500);

		exit(0);

		}

	}

else  // recibimos la clave del teclado

	{

    tecla=getch();

    	if (aux1=='*')

    		{

    		aux1=tecla;

			}

		else

		    {

		    if (aux2=='*')

		    	{

		    	aux2=tecla;	//Verificamos la clave y desactivamos la bomba

		    	if ((aux1=='c' or aux1=='C') and (aux2=='f' or aux2=='F'))

		    		{

		    		system("cls");

					cout <<"Tiempo para explosión "<<min<<":"<<seg<<"  clave de desactivación= "<<aux1<<aux2;	

					cout <<endl<<endl<<"Usted a desactivado la bomba"<<endl;

					cout <<"FELICITACIONES !!!"<<endl;

					Beep (500,500);

					Beep (500,500);

					exit(0);

					}

					else //clave incorrecta penalizamos

					{

					system("cls");

					cout <<"Tiempo para explosión "<<min<<":"<<seg<<"  clave de desactivación= "<<aux1<<aux2;	

					cout <<endl<<endl<<"Clave de desactivación"<<endl;

					cout <<"INCORRECTA !!!"<<endl;

					cout <<"SE LE RESTARA UN MINUTO!!!"<<endl;

					min=min-1;

					Beep(100,500);	

					Beep(100,500);	

					aux1='*';

					aux2='*';

					}

				}

			}	

	}



goto repite;

}
