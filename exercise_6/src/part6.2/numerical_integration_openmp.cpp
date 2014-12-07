/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 06
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        helloworld_openmp.cpp
*
* Purpose :     NUMERICAL INTEGRATION (Parallel OpenMP Version)
*
* Last Change : 05. Dec. 2014
*
*************************************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int iNumThreads;

double dx_arctan(int iNumIterations) {
	double dWidth;
	double dSum;
	double dPosition;

	dWidth = 1./iNumIterations;
	dSum = 0.0;
	dPosition = 0.0;

    #pragma omp parallel private(dPosition)
    {
        #pragma omp parallel for reduction(+:dSum) schedule(static)
        for(int i = 0; i <= iNumIterations; i++) {
            int par = omp_in_parallel();
            //printf("\nAm I parallel: %d", par);
            dPosition += dWidth;
            dSum += (4. / (1. + dPosition * dPosition)) * dWidth;
        }
    }

    int par = omp_in_parallel();
    //printf("\nAm I parallel: %d", par);
	return dSum;
}

int main(int argc, char **argv) {
	int iNumIterations;
	double dPi;
	double dStart, dTime;

	if(argc != 3) {
        printf("Usage:\n\t");
        printf("./pi\n");
        printf("\t<N number of threads>\n");
        printf("\t<I number of iterations>\n");
        return EXIT_FAILURE;
    }

    iNumThreads = atoi(argv[1]);
    iNumIterations = atoi(argv[2]);

    omp_set_num_threads(iNumThreads);

    dStart = omp_get_wtime();

    dPi = dx_arctan(iNumIterations);

    dTime = omp_get_wtime() - dStart;

    printf("\nPi (approx.):\t %f", dPi);
    printf("\nTime needed:\t %f\n", dTime);

	return EXIT_SUCCESS;
}
