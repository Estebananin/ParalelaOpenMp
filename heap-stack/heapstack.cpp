/***
	Programa: 		heapstack.cpp
	Autor: 	  		Mustafa Atik
	Documentado por: 	E. López - J. García
	Función:  		Este algortimo realiza un breve conteo de pila según los hilos dados en "omp_set_num_threads" 
	Fecha de documentación: 3 de octubre, 2020
 ***/

#include <iostream>
#include <omp.h>

int main() {
    
    int heap_sum = 0;
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        int stack_sum=0;
        stack_sum++;
        heap_sum++;
        printf("stack sum is %d\n", stack_sum);
        printf("heap sum is %d\n", heap_sum);
    }
    std::cout << "final heap sum is " << heap_sum << std::endl;

//    output:
//    stack sum is 1
//    stack sum is 1
//    stack sum is 1
//    heap sum is 3
//    heap sum is 3
//    heap sum is 3
//    final heap sum is 3
    return 0;
}
