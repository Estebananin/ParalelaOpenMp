/***
	Programa: 	hello-mp.cpp
	Autor: 	  	Mustafa Atik
	Modificado: E. L�pez - J. Garc�a
	Funci�n:  	En este algoritmo se hace uso de la regi�n paralela de OpenMp 
				para la escritura de texto haciendo uso de diferentes hilos seg�n
				se hayan configurado en el comando "omp_get_thread_num()"  
 ***/
 
#include <iostream>
#include <omp.h>

using namespace std;	

int main() {
	/*** Regi�n Paralela OMP ***/
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hola  %d\n", ID);
        printf("hola de nuevo %d\n", ID);
    }
//    output:
//    hola  1
//    hola  0
//    hola  3
//    hola  2
//    hola de nuevo 1
//    hola de nuevo 0
//    hola de nuevo 3
//    hola de nuevo 2
    return 0;
}
