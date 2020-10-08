/***
	Programa: 	parallel-loop.c
	Autor: 	  	Mustafa Atik
	Modificado: 	E. López - J. García
	Función:  	Algoritmo breve de realización de un ciclo en una claúsula de parallel.
	Fecha: 		  4 de octubre, 2020	
 ***/

#include <stdio.h>
#include <omp.h>

int main() {
    printf("the begin of loop");

    #pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        cout << i;
    }
    printf("the end of loop");

//    Expected output will be similar to this:
//    the begin of loop
//    6378049152
//    the end of loop
    return 0;
}
