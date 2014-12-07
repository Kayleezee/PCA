/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 06
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        main.cpp
*
* Purpose :     MATRIX VECTOR MULTIPLY (Parallel OpenMP Version)
*
* Last Change : 05. Dec. 2014
*
*************************************************************************************************/
#include <omp.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
#include "inc/matrix.hpp"
using namespace std;

int threads;

void print_usage() {
    cout << "\nUsage:" << endl;
    cout << "\t<S size of matrix / vector>" << endl;
    cout << "\t<R seed for random-function>" << endl;
    cout << "\t<D display argument [0 = off   | 1 = on    ]>" << endl;
    cout << "\t<M type mode        [0 = float | 1 = double]>" << endl;
    cout << "\t<I number of iteration>" << endl;
    cout << "\t<T number of threads>" << endl;
}

/*************************************************************************************************
 MAIN FUNCTION
**************************************************************************************************/
int main(int argc, char **argv) {
	if(argc != 7) {
        print_usage();
        return EXIT_FAILURE;
	}

	int size    = atoi(argv[1]);
	int seed    = atoi(argv[2]);
	int display = atoi(argv[3]);
    int mode    = atoi(argv[4]);
    int iterate = atoi(argv[5]);
    threads     = atoi(argv[6]);

    double dStart   = 0.0;
    double dTimeSeq = 0.0;
    double dTimePar = 0.0;

	srand(seed);

	cout << "Matrix Vector Multiplication with OpenMP starting ..." << endl;

    /* Calculation for FLOAT type elements */
    if(mode == 0) {
        /* sequential part */
        float **matrix, *vector, *new_vector;

        matrix = fgenMatrix(size);
        vector = fgenVector(size);

        dStart = omp_get_wtime();

        for(int i = 0; i < iterate; i++) {
            new_vector = fmvMulti(size, matrix, vector);
        }

        dTimeSeq = (omp_get_wtime() - dStart)/iterate;

        if(display == 1 && size <= 10) {
            foutResult(size, new_vector);
        }

        /* parallel part */
        dStart = omp_get_wtime();

        for(int i = 0; i < iterate; i++) {
            new_vector = fmvMultiPar(size, matrix, vector);
        }
        dTimePar = (omp_get_wtime() - dStart)/iterate;

        if(display == 1 && size <= 10) {
            foutResult(size, new_vector);
        }

        /* result */
        cout << "===========================================" << endl;
        cout << "RESULTS:" << endl;
        cout << "-------------------------------------------" << endl;
        cout << endl;
        cout << "Matrix-Vector-Multiplication:" << endl;
        cout << "Sequential time:\t" << dTimeSeq << endl;
        cout << "Parallel time  :\t" << dTimePar << endl;
        cout << "Speed-Up       :\t" << dTimeSeq/dTimePar << endl;
        cout << "===========================================" << endl;
    }

    /* Calculation for DOUBLE type elements */
    if(mode == 1) {
        /* sequential part */
        double **matrix, *vector, *new_vector;

        matrix = dgenMatrix(size);
        vector = dgenVector(size);

        dStart = omp_get_wtime();

        for(int i = 0; i < iterate; i++) {
            new_vector = dmvMulti(size, matrix, vector);
        }

        dTimeSeq = (omp_get_wtime() - dStart)/iterate;

        if(display == 1 && size <= 10) {
            doutResult(size, new_vector);
        }

        /* parallel part */
        dStart = omp_get_wtime();

        for(int i = 0; i < iterate; i++) {
            new_vector = dmvMultiPar(size, matrix, vector);
        }

        dTimePar = (omp_get_wtime() - dStart)/iterate;

        if(display == 1 && size <= 10) {
            doutResult(size, new_vector);
        }

        /* result */
        cout << "===========================================" << endl;
        cout << "RESULTS:" << endl;
        cout << "-------------------------------------------" << endl;
        cout << endl;
        cout << "Matrix-Vector-Multiplication:" << endl;
        cout << "Sequential time:\t" << dTimeSeq << endl;
        cout << "Parallel time  :\t" << dTimePar << endl;
        cout << "Speed-Up       :\t" << dTimeSeq/dTimePar << endl;
        cout << "===========================================" << endl;
    }

    if(mode > 1) {
        print_usage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
