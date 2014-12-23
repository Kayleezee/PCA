/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 07
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        main.c
*
* Purpose :     HEAT RELAXATION (Parallel OpenMP Version)
*
* Last Change : 22. Dec. 2014
*
*************************************************************************************************/
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "heat_relaxation.h"
#include "time_measurement.h"

void print_usage() {
  printf("\nUsage:\n\n./heat_relax\n"
         "\n\t<S: size of grid>"
         "\n\t<D: diameter of inner grid>"
         "\n\t<V: initial value>"
         "\n\t<T: number of threads>"
         "\n\t<I: number of iterations>"
         "\n\t<P: print matrix [0 = off;        1 = on      ]"
         "\n\t<M: version mode [0 = PThreads;   1 = OpenMP  ]\n");
}


int main(int argc, char** argv){

  /* Integer declaration */
  int i;                    // INTEGER: loop variable
  int j;                    // INTEGER: loop variable
  int k;                    // INTEGER: loop variable
  int iDiameter;            // INTEGER: diameter of inner grid
  int iInitValue;           // INTEGER: initial value of inner grid elements
  int iIterations;          // INTEGER: number of iterations
  int iDisplay;             // INTEGER: display mode [0 = off; 1 = on]
  int iVersion;             // INTEGER: version mode [0 = POSIX Threads; 1 = OPENMP]

  /* Double declaration */
  double dStart     = 0.0;
  double dTimeSeq   = 0.0;
  double dTimePar   = 0.0;

  /* check arguments */
  if(argc != 8)
  {
    print_usage();
    return EXIT_FAILURE;
  }

  /* Get command line arguments */
  iSize         = atoi(argv[1]);
  iDiameter     = atoi(argv[2]);
  iInitValue    = atoi(argv[3]);
  iNumThreads   = atoi(argv[4]);
  iIterations   = atoi(argv[5]);
  iDisplay      = atoi(argv[6]);
  iVersion      = atoi(argv[7]);

  if(iSize < iDiameter) {
    printf("\nExiting program ...\nInner grid size bigger than main grid size!\n\n");
    print_usage();
    return EXIT_FAILURE;
  }

  /* Memory allocation main grid: dGrid(iSize) */
  if(iAllocGridDouble(&dGrid, iSize, iSize))
  {
    printf("\nExiting program ...\nAllocation failed!");
    return EXIT_FAILURE;
  }

  /* Memory allocation temp grid: dGrid(iSize) */
  if(iAllocGridDouble(&dTemp, iSize, iSize))
  {
    printf("\nExiting program ...\nAllocation failed!");
    return EXIT_FAILURE;
  }

  /* Initialize Grid with 0.0 */
  vInitGridDouble(&dGrid);
  /* Fill inner grid with initial value */
  vFillInnerGridDouble(&dGrid, iDiameter, iInitValue);

/*************************************************************************************************
 2D HEAT DISTRIBUTION (PARALLEL POSIX THREADS)
**************************************************************************************************/
  if(iVersion == 0) {
    /* Pointer declaration */
    pthread_t * pThreads;

    /* Memory allocation pointer to threads: tPointer(iNumThreads) */
    pThreads = (pthread_t *) malloc(iNumThreads*sizeof(pthread_t));

    /* begin time measurement for parallel heat relaxation */
    dStart = dStartMeasurement();

    /* Start parallel heat relaxation */
    for(k = 0; k < iIterations; k++)
    {

        for(i = 0; i < dGrid.iRows; i++) {
            for(j = 0; j < dGrid.iCols; j++) {
            dTemp.dpGrid[i][j] = dGrid.dpGrid[i][j];
            }
        }

        for(i = 0; i < iNumThreads; i++)
        {
            if(pthread_create(&pThreads[i], NULL, (void *)vHeatRelaxGridDoubleParPThreads, (void *)(intptr_t)i) != 0)
            {
                printf("\nExiting program ...\nThread creation failed!");
                free(pThreads);
                return EXIT_FAILURE;
            }
        }

        for(j = 0; j < iNumThreads; j++)
            pthread_join(pThreads[j], NULL);
    }

    /* stop time measurement for parallel heat relaxation */
    dTimePar = dStopMeasurement(dStart) / iIterations;

    if(iDisplay == 1 && iSize <= 10) {
        printf("\nResult grid for parallel heat relaxation:\n\n");
        vOutputGridDouble(&dGrid);
    }

    /* Initialize Grid with 0.0 */
    vInitGridDouble(&dGrid);
    /* Fill inner grid with initial value */
    vFillInnerGridDouble(&dGrid, iDiameter, iInitValue);

    /* begin time measurement for sequential heat relaxation */
    dStart = dStartMeasurement();
    for(j = 0; j < iIterations; j++) {
        vHeatRelaxGridDoubleSeq();
    }

    /* stop time measurement for sequential heat relaxation */
    dTimeSeq = dStopMeasurement(dStart) / iIterations;

    if(iDisplay = 1 && iSize <= 10) {
        printf("\nResult grid for sequential heat relaxation:\n\n");
        vOutputGridDouble(&dGrid);
    }
  }

/*************************************************************************************************
 2D HEAT DISTRIBUTION (PARALLEL OPENMP)
**************************************************************************************************/
  if(iVersion == 1) {
    int iMyID;

    /* begin time measurement for parallel heat relaxation */
    dStart = omp_get_wtime();

    /* Start parallel heat relaxation */
    for(k = 0; k < iIterations; k++)
    {
        #pragma omp parallel num_threads(iNumThreads)
        vHeatRelaxGridDoubleParOpenMP(omp_get_thread_num());
        #pragma omp barrier
    }

    /* stop time measurement for parallel heat relaxation */
    dTimePar = (omp_get_wtime() - dStart) / iIterations;

    if(iDisplay == 1 && iSize <= 10) {
        printf("\nResult grid for parallel heat relaxation:\n\n");
        vOutputGridDouble(&dGrid);
    }

    /* Initialize Grid with 0.0 */
    vInitGridDouble(&dGrid);
    /* Fill inner grid with initial value */
    vFillInnerGridDouble(&dGrid, iDiameter, iInitValue);

    /* begin time measurement for sequential heat relaxation */
    dStart = omp_get_wtime();
    for(j = 0; j < iIterations; j++) {
        vHeatRelaxGridDoubleSeq();
    }

    /* stop time measurement for sequential heat relaxation */
    dTimeSeq = (omp_get_wtime() - dStart) / iIterations;

    if(iDisplay == 1 && iSize <= 10) {
        printf("\nResult grid for sequential heat relaxation:\n\n");
        vOutputGridDouble(&dGrid);
    }
  }

  printf("\n#########################################################\n#\n#\n#");
  if(iVersion == 0) {
    printf("\n#\t Parallel 2D Heat Distribution with PThreads \n#");
  }
  if(iVersion == 1) {
    printf("\n#\t Parallel 2D Heat Distribution with OpenMP \n#");
  }
  printf("\n#\t ");
  printf("\n#\t Calculation time per Iteration: \n#");
  printf("\n#\t Parallel       : %lfs \n#", dTimePar);
  printf("\n#\t Sequential     : %lfs \n#", dTimeSeq);
  printf("\n#\t Iteration /sec : %lf  \n#", 1/dTimePar);
  printf("\n#\t Speed-Up       : %lf  \n#", dTimeSeq/dTimePar);
  printf("\n#\n#\n#########################################################\n\n\n");

  return EXIT_SUCCESS;
}
