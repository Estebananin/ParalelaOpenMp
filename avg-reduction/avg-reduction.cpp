/***
	Programa: 		avg-reduction.cpp
	Autor: 	  		Mustafa Atik
	Documentado por: 	E. López - J. García
	Función:  		Algoritmo que realiza un promedio y escribe el tiempo que tarda en realizar este procedimiento 
				variando en las claúsulas de OMP que se utiliza para el procedimiento. 	 
	Fecha de documentación:	3 de octubre, 2020
 ***/
 
#include <iostream>
#include <omp.h>

void avg();
void avg_reduction();

int main() {
//    avg();
    avg_reduction();
    return 0;
}

/***
	Método: 	avg_round_robin()
	Función:	Imprime el tiempo tomado en realizar este procedimiento por hilo (usando claúsula "parallel")
***/
void avg_round_robin() {
    int N = 600000000;
    double tavg = 0;

    double timer_start = omp_get_wtime();
    omp_set_num_threads(16);
    #pragma omp parallel
    {
        double avg;
        int id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        for (int i = id; i < N; i+=nthreads) {
            avg += i;
        },
        #pragma omp atomic
        tavg += avg;
    }
    double timer_elapsed = omp_get_wtime() - timer_start;
    tavg = tavg / N;

    std::cout << tavg << " took " << timer_elapsed << std::endl;
    //     1 threads took 2.1
    //     4 threads took 0.7
    //    48 threads took 0.65
}


/***
	Método: 	avg_reduction()
	Función:	Imprime el tiempo tomado en realizar este procedimiento por hilo (usando claúsula "parallel for reduction")
	
	*******     Reduce específica que una o más variables que son privadas para cada hilo serán
				el objetivo de una operación de reducción al final de la región paralela.
***/
void  avg_reduction() {
    int N = 600000000;
    int j = 0;
    double tavg = 0;

    double timer_start = omp_get_wtime();
    omp_set_num_threads(48);

    #pragma omp parallel for reduction(+:tavg)
    for (j = 0; j < N; ++j) {
        tavg += j;
    }

    double timer_elapsed = omp_get_wtime() - timer_start;
    tavg = tavg / N;

    std::cout << tavg << " took " << timer_elapsed << std::endl;
    //     1 threads took 2.1
    //     4 threads took 0.69
    //    48 threads took 0.65
}
