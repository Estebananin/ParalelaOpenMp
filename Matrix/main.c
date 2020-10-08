/***
	Programa: 		 main.c
	Autor: 	  		 Mustafa Atik
	Implementado en c: 	 E. López - J. García
	Función:  		 Este algoritmo genera y opera matrices entre si. Realiza: suma, resta, multiplicacion y la transpuesta.  
	Fecha de implementación: 3 de octubre, 2020
 ***/
 
#include <stdio.h>

struct Matrix {
    double *data;
    int rows, cols;

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        data = new double[rows*cols];
    }

    double get(int row, int col) {
        return data[row * cols + col];
    }

    double set(int row, int col, double val) {
        data[row * cols + col] = val;
    }

    Matrix& operator +(const Matrix& m2)
    {
        return sum(m2);
    }

/*** 
	Método: 	Matrix sum
	Función: 	Suma dos matrices dadas.
***/

    Matrix& sum(Matrix matrix) {
        Matrix *s = new Matrix(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            s->data[i] = data[i] + matrix.data[i];
        }
        return *s;
    }

/*** 
	Método: 	Matrix substract
	Función: 	Resta entre matrices.
***/

    Matrix& substract(Matrix matrix) {
        Matrix *s = new Matrix(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            s->data[i] = data[i] - matrix.data[i];
        }
        return *s;
    }

/*** 
	Método: 	Matrix multiply
	Función: 	Multiplicacion de matrices.
***/

    Matrix& multiply(Matrix matrix) {
        if (!(shape()[0] == matrix.shape()[1] && shape()[1] == matrix.shape()[0]))

        Matrix *s = new Matrix(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            s->data[i] = data[i] - matrix.data[i];
        }
        return *s;
    }

/*** 
	Método: 	Matrix T
	Función: 	Genera la transpuesta de una matriz.
***/

    Matrix& T() {
        Matrix *s = new Matrix(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                s->set(j, i, get(i, j));
            }
        }
        return * s;
    }

    int* shape() {
        int * shape = new int[2];
        shape[0] = rows;
        shape[1] = cols;
        return shape;
    }


int main() {
    Matrix m1  = Matrix(2, 3);
    Matrix m2  = Matrix(2, 3);
    for (int i = 0; i < 6; ++i) {
        m1.set((int)i / 3, i % 3, i);
        m2.set((int)i / 3, i % 3, i);
    }

    m1.set(0, 1, 6);
    return 0;
}
