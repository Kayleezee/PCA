/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 07
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        head_relaxation.c
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

pthread_mutex_t     barrier;
pthread_cond_t      start;
int count = 0;

int iAllocGridDouble(sGridDouble *pGrid, int iRows, int iCols) {
  int i, iReturn 	= 0;

  pGrid->iRows 	= iRows;
  pGrid->iCols 	= iCols;

  pGrid->dpGrid = malloc(iRows * sizeof(double *));
  if(NULL == pGrid->dpGrid) {
    iReturn = 1;
  }

  for(i = 0; i < iCols; i++) {
    pGrid->dpGrid[i] = malloc(iCols * sizeof(double));
    if(NULL == pGrid->dpGrid[i]) {
      iReturn == 1;
    }
  }

  return iReturn;
}

void vInitGridDouble(sGridDouble *pGrid) {
  int i, j;

	for(i = 0; i < pGrid->iRows; i++) {
    for(j = 0; j < pGrid->iCols; j++) {
      pGrid->dpGrid[i][j] = 0.0;
    }
  }
}
/*
void vDeleteGridDouble(sGridDouble *pGrid) {
	int i;

	for(i = 0; i < pGrid->iRows; i++) {
			delete [] pGrid->dpGrid[i];
	}
	delete [] pGrid->dpGrid;
}
*/
void vOutputGridDouble(sGridDouble *pGrid) {
  int i, j;

	for(i = 0; i < pGrid->iRows; i++) {
    printf("\n");
    for(j = 0; j < pGrid->iCols; j++) {
      printf("%f\t", pGrid->dpGrid[i][j]);
    }
  }
  printf("\n");
}

void vFillInnerGridDouble(sGridDouble *pGrid, int iDiameter, double dInitValue) {
  int n, m, i, j;
  int x 	= pGrid->iRows / 2;
  int y 	= pGrid->iCols / 2;
  int radius 	= iDiameter / 2;

  for(i = 0; i < pGrid->iRows; i++) {
    for(j = 0; j < pGrid->iCols; j++) {
      n = i - x;
      m = j - y;

      if((n * n + m * m) <= (radius * radius)) {
	pGrid->dpGrid[i][j] = dInitValue;
      }
    }
  }
}

void vHeatRelaxGridDoubleSeq(void) {
  int i,j;

  for(i = 0; i < dGrid.iRows; i++)
    for(j = 0; j < dGrid.iCols; j++)
      dTemp.dpGrid[i][j] = dGrid.dpGrid[i][j];

  for(i = 0; i < dGrid.iCols; i++)
    for(j = 0; j < dGrid.iCols; j++)
    {
      if(!(i == 0  || i == dGrid.iRows-1 || j == 0 || j == dGrid.iCols-1)) {
        dGrid.dpGrid[i][j] = dTemp.dpGrid[i][j];
        dGrid.dpGrid[i][j] += 0.24 * ((-4)*dTemp.dpGrid[i][j] + dTemp.dpGrid[i+1][j] + dTemp.dpGrid[i-1][j] + dTemp.dpGrid[i][j+1] + dTemp.dpGrid[i][j-1]);
      }
    }
}

void vHeatRelaxGridDoubleParPThreads(int *Id) {
  int i,j;

  int s = (intptr_t) Id;
  int iFrom = (s * dGrid.iRows) / iNumThreads;
  int iTo = ((s+1) * dGrid.iRows) / iNumThreads;

  for(i = 0; i < dGrid.iRows; i++)
    for(j = 0; j < dGrid.iCols; j++)
      dTemp.dpGrid[i][j] = dGrid.dpGrid[i][j];

  Barrier();

  for(i = iFrom; i < iTo; i++)
    for(j = 0; j < dGrid.iCols; j++)
    {
      if(!(i == 0  || i == dGrid.iRows-1 || j == 0 || j == dGrid.iCols-1))
      {
        dGrid.dpGrid[i][j] = dTemp.dpGrid[i][j];
        dGrid.dpGrid[i][j] += 0.24 * ((-4)*dTemp.dpGrid[i][j] + dTemp.dpGrid[i+1][j]+ dTemp.dpGrid[i-1][j] + dTemp.dpGrid[i][j+1] + dTemp.dpGrid[i][j-1]);
      }
    }
    Barrier();
}

void vHeatRelaxGridDoubleParOpenMP(int Id) {
  int i,j;

  int s = Id;
  int iFrom = (s * dGrid.iRows) / iNumThreads;
  int iTo = ((s+1) * dGrid.iRows) / iNumThreads;

  for(i = iFrom; i < iTo; i++)
    for(j = 0; j < dGrid.iCols; j++)
      dTemp.dpGrid[i][j] = dGrid.dpGrid[i][j];

  for(i = iFrom; i < iTo; i++)
    for(j = 0; j < dGrid.iCols; j++)
    {
      if(!(i == 0  || i == dGrid.iRows-1 || j == 0 || j == dGrid.iCols-1))
      {
        dGrid.dpGrid[i][j] = dTemp.dpGrid[i][j];
        dGrid.dpGrid[i][j] += 0.24 * ((-4)*dTemp.dpGrid[i][j] + dTemp.dpGrid[i+1][j]+ dTemp.dpGrid[i-1][j] + dTemp.dpGrid[i][j+1] + dTemp.dpGrid[i][j-1]);
      }
    }
}

void Barrier() {
    pthread_mutex_lock(&barrier);
    count++;
    if(count == iNumThreads) {
        count = 0;
        pthread_cond_broadcast(&start);
        printf("\nAll threads done!");
    } else {
        pthread_cond_wait(&start, &barrier);
    }
    pthread_mutex_unlock(&barrier);
}
