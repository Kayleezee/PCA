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
* Purpose :     HELLO WORLD (Parallel OpenMP Version)
*
* Last Change : 05. Dec. 2014
*
*************************************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int iNumThreads;

    if(argc != 2) {
        printf("Usage:\n\t");
        printf("./hellomp\n\t");
        printf("\t<N number of threads>\n");
        return EXIT_FAILURE;
    }

    iNumThreads = atoi(argv[1]);

    omp_set_num_threads(iNumThreads);

    #pragma omp parallel for
    for(int i = 0; i < iNumThreads; i++) {
        int iMyId = omp_get_thread_num();

        printf("\nHello World! I'm Thread No. %d", iMyId);

        if(iMyId == 0) {
            printf("\nTotal amount of active Threads: %d", omp_get_num_threads());
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}
