/***
	Programa: 	data-share.cpp
	Autor: 	  	Mustafa Atik
	Modificado: E. López - J. García
	Función:  	En este algoritmo se hace una presentación del funcionamiento de las 
				variables "private" y "firstprivate" evidenciando sus diferencias haciendo
				uso de la región paralela de OMP.
	Fecha: 		3 de octubre, 2020	
 ***/
 
#include <iostream>
#include <omp.h>

void compare_cases();
using namespace std;

double G = 2.1;  		//Esta variable no se verá afectada en ningún punto ya que es estática en el algoritmo

int main() {
    compare_cases();
    return 0;
}

/*** 
	Método: 	compare_cases()
	Función: 	Tomando la cantidad de hilos, usa la región paralela para mostrar 
				por pantalla las diferencias entre los tipos de variable tomadas
				en esta claúsula haciendo dos impresiones: una sobre la región de 
				omp parallel y otra afuera de este; evidenciando así las diferencias.
***/
void compare_cases() {
    int a=1, b=2, c=3, t=4;
    omp_set_num_threads(3);
    #pragma omp parallel private(a), firstprivate(b)
    {
        // a será privada pero no será inicializada por su especificación en la claúsula "private";
        // b será privada e inicializada por su categoría "firstprivate" en la claúsula tomando el valor anterior de inicio;
        // c será compartida;
        // t será local siendo privada.
        int t = 5;	//Creada dentro de la región

        static int s = 8; // será compartido.
        if (omp_get_thread_num() == 0) //Si el valor de "omp_get_thread_num" es 0 el valor dado de s será 2
            s = 2;	

        printf("ID hilo: %d, a: %d, b: %d, c: %d, t: %d, s: %d, G: %f, \n", omp_get_thread_num(), a, b, c, t, s, G); //Impresión dentro de la región omp
        a = 21;
        b = 22;
        c = 23;
        t = 24;
    }
    
    

    printf("\nout of the parallel region\n");
    printf("ID hilo: %d, a: %d, b: %d, c: %d, t: %d, G: %f, \n", omp_get_thread_num(), a, b, c, t, G); //Impresión fuera de la región

//    OUTPUT:
//    ID hilo: 0, a: 0, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//    ID hilo: 2, a: 32752, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//    ID hilo: 1, a: 32767, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//
//    out of the parallel region
//    ID hilo: 0, a: 1, b: 2, c: 23, t: 4, G: 2.100000,
}
