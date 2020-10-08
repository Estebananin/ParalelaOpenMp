/***
	Programa: 		queues.cpp
	Autor: 	  		Mustafa Atik
	Documentado por: 	E. López - J. García
	Función:  		Este algoritmo crea estructuras de nodos y colas llenas de nodos, que posteriormente 
				son procesadas por un metodo que detiene la ejecución en un valor aleatorio por cada
				nodo creado para esta.	
	Fecha de documentado: 	4 de octubre, 2020
 ***/

#include <iostream>
#include <omp.h>
#include <zconf.h>

/*** 
	Estructura: Node (Nodo)
	Función: 	Creación de nodos para el programa
***/
struct Node {
    int data;
    struct Node* next = NULL;
    Node() {}
    Node(int data) {
        this->data = data;
    }
    Node(int data, Node* node) {
        this->data = data;
        this->next = node;
    }
};

void processNode(Node *pNode);

/***
	Estructura: Queue (Cola)
	Función: 	Creación de la estructura cola a partir de nodos utilizando claúsulas de OMP 
				para añadir o eliminar. 
***/
struct Queue {
    Node *head = NULL, *tail = NULL;

    Queue& add(int data) {
        add(new Node(data));
        return *this;
    }
	/** 
	Método: 	add
	Función:	Adición de nodos a la estructura de cola
	**/
    void add(Node *node) {
        #pragma omp critical // Esta clausúla ejecuta un hilo a la vez.
        {
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }

	/** 
	Método: 	remove
	Función:	Remover nodos a la estructura de cola
	**/
    Node* remove() {
        Node *node;
        #pragma omp critical // Esta clausúla ejecuta un hilo a la vez.
        {
            node = head;
            if (head != NULL)
                head = head->next;
        }
        return node;
    }

};

int main() {
    srand(12);
    Queue queue;

    #pragma omp parallel for
    for (int i = 0; i < 500; ++i) {		//Creación de la cola
        queue.add(i);
    }

    size_t totalProcessedCounter = 0;
    double timer_started = omp_get_wtime();	//Medidor de tiempo
    omp_set_num_threads(5);				// 5 hilos establecidos por defecto
    #pragma omp parallel				//Comienzo Región paralela
    {
        Node *n;
        size_t processedCounter = 0;
        double started = omp_get_wtime();

        while ((n = queue.remove()) != NULL) {		//Procesamiento de nodos con processNode hasta que esté vacío
            processNode(n);
            processedCounter++;
        }

        double elapsed = omp_get_wtime() - started;
        printf("Thread id: %d,  processed: %d nodes, took: %f seconds \n",
               omp_get_thread_num(), processedCounter, elapsed);
        #pragma omp atomic
        totalProcessedCounter += processedCounter;
    }									//Fin región paraelela

    double elapsed = omp_get_wtime() - timer_started;
    std::cout << "end. processed " << totalProcessedCounter <<" nodes. took " << elapsed << " in total " << std::endl;
//    Thread id: 4,  processed: 100 nodes, took: 5.114557 seconds
//    Thread id: 0,  processed: 111 nodes, took: 5.118820 seconds
//    Thread id: 2,  processed: 102 nodes, took: 5.125992 seconds
//    Thread id: 3,  processed: 95 nodes, took: 5.158186 seconds
//    Thread id: 1,  processed: 92 nodes, took: 5.173112 seconds
//    end. processed 500 nodes. took 5.17337 in total

    return 0;
}

/***
	Método: 	processNode
	Función:	Esta función recibe un nodo de la cola y crea un valor que puede ser entre 9 y 1 
				y hace uso de la función "usleep" para detener la ejecución por unos milisegundos dados.
***/
void processNode(Node *node) {
    int r = rand() % 9 + 1; // between 1 and 9
    usleep(r * 10000); // sleeps 0.001 or 0.090 second
}
