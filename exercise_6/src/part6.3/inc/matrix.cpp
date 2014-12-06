/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 06
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        matrix.cpp
*
* Purpose :     MATRIX VECTOR MULTIPLY (Parallel OpenMP Version)
*
* Last Change : 05. Dec. 2014
*
*************************************************************************************************/
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include "matrix.hpp"
using namespace std;

/*************************************************************************************************
 GENERATING MATRICES
**************************************************************************************************/
float **fgenMatrix(int size) {

	float **matrix = new float*[size];
	for(int i = 0; i < size; i++) {
		matrix[i] = new float[size];
		for(int j = 0; j < size; j++) {
			matrix[i][j] = rand();
		}
	}

	return matrix;
}

double **dgenMatrix(int size) {

	double **matrix = new double*[size];
	for(int i = 0; i < size; i++) {
		matrix[i] = new double[size];
		for(int j = 0; j < size; j++) {
			matrix[i][j] = rand();
		}
	}

	return matrix;
}

/*************************************************************************************************
 GENERATING VECTORS
**************************************************************************************************/
// generates a Vector with random numbers - size: N
float *fgenVector(int size) {

	float *vector = new float[size];
	for(int i = 0; i < size; i++) {
		vector[i] = (float)rand();
	}

	return vector;
}

double *dgenVector(int size) {

	double *vector = new double[size];
	for(int i = 0; i < size; i++) {
		vector[i] = (double)rand();
	}

	return vector;
}

/*************************************************************************************************
 PRINT MATRIX
**************************************************************************************************/
void **foutMatrix(int size, float **matrix) {
	cout << "Matrix:\n";
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

void **doutMatrix(int size, double **matrix) {
	cout << "Matrix:\n";
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

/*************************************************************************************************
 PRINT VECTOR
**************************************************************************************************/
void **foutVector(int size, float *vector) {
	cout << "Vector:\n";
	for(int i = 0; i < size; i++) {
		cout << vector[i] << "\n";
	}
}

void **doutVector(int size, double *vector) {
	cout << "Vector:\n";
	for(int i = 0; i < size; i++) {
		cout << vector[i] << "\n";
	}
}

/*************************************************************************************************
 PRINT RESULT
**************************************************************************************************/
void **foutResult(int size, float *vector) {
	cout << "Result:\n";
	for(int i = 0; i < size; i++) {
		cout << vector[i] << "\n";
	}
}

void **doutResult(int size, double *vector) {
	cout << "Result:\n";
	for(int i = 0; i < size; i++) {
		cout << vector[i] << "\n";
	}
}

/*************************************************************************************************
 MATRIX VECTOR MULTIPLY (SEQUENTIAL)
**************************************************************************************************/
// multiplies the matrix by vector
float *fmvMulti(int size, float **matrix, float *vector) {

	float *new_vector = new float[size];
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			new_vector[i] += (matrix[i][j] * vector[j]);
		}
	}

	return new_vector;
}

double *dmvMulti(int size, double **matrix, double *vector) {

	double *new_vector = new double[size];
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			new_vector[i] += (matrix[i][j] * vector[j]);
		}
	}

	return new_vector;
}

/*************************************************************************************************
 MATRIX VECTOR MULTIPLY (PARALLEL OPENMP)
**************************************************************************************************/
// multiplies the matrix by vector

float *fmvMultiPar(int size, float **matrix, float *vector) {
    omp_set_num_threads(threads);

	float *new_vector = new float[size];
	//#pragma omp parallel //shared(matrix, vector, new_vector)
	//{
	    #pragma omp parallel for shared(matrix, vector, new_vector) //schedule(dynamic)
        for(int i = 0; i < size; i++) {
            new_vector[i] = 0.0;
            for(int j = 0; j < size; j++) {
                new_vector[i] += (matrix[i][j] * vector[j]);
            }
            //cout << "Thread No.: " << omp_get_thread_num() << " calculated Element No.: " << new_vector[i] << endl;
        }
	//}
	return new_vector;
}

double *dmvMultiPar(int size, double **matrix, double *vector) {
    omp_set_num_threads(threads);

	double *new_vector = new double[size];

	#pragma omp parallel for shared(matrix, vector, new_vector)
	for(int i = 0; i < size; i++) {
        new_vector[i] = 0.0;
		for(int j = 0; j < size; j++) {
			new_vector[i] += (matrix[i][j] * vector[j]);
		}
	}

	return new_vector;
}
