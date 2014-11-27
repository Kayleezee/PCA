/*************************************************************************************************
*
*        Heidelberg University - PCA Exercise 05
*
*                            Group : PCA03
*		       Participant : Klaus Naumann
*				     Jan Brodhaecker  
*
*                             File : head_relaxation.cpp
*
*                          Purpose : HEAT RELAXATION (Parallel POSIX Threads Version)
* 
* 		       Last Change : 27. Nov. 2014
*
*************************************************************************************************/
#include <iostream>
#include <cstdlib>
#include "heat_relaxation.hpp"
//#include "time_measurement.hpp"
using namespace std;


int iAllocGridDouble(sGridDouble *pGrid, int iRows, int iCols) {
  int iReturn 	= 0;
  
  pGrid->iRows 	= iRows;
  pGrid->iCols 	= iCols;
  
  pGrid->dpGrid = new double*[iRows];
  if(NULL == pGrid->dpGrid) {
    iReturn = 1;
  }
  
  for(int i = 0; i < iCols; i++) {
    pGrid->dpGrid[i] = new double[iCols];
    if(NULL == pGrid->dpGrid[i]) {
      iReturn == 1;
    }
  }
  
  return iReturn;
}

void vInitGridDouble(sGridDouble *pGrid) {
  for(int i = 0; i < pGrid->iRows; i++) {
    for(int j = 0; j < pGrid->iCols; j++) {
      pGrid->dpGrid[i][j] = 0.0;
    }
  }
}

void vDeleteGridDouble(sGridDouble *pGrid) {
}

void vOutputGridDouble(sGridDouble *pGrid) {
  for(int i = 0; i < pGrid->iRows; i++) {
    cout << endl;
    for(int j = 0; j < pGrid->iCols; j++) {
      cout << pGrid->dpGrid[i][j] << "\t";
    }
  }
  cout << endl;
}

void vFillInnerGridDouble(sGridDouble *pGrid, int iDiameter, double dInitValue) {
  int n, m;
  int x 	= pGrid->iRows / 2;
  int y 	= pGrid->iCols / 2;
  int radius 	= iDiameter / 2;
  
  for(int i = 0; i < pGrid->iRows; i++) {
    for(int j = 0; j < pGrid->iCols; j++) {
      n = i - x;
      m = j - y;
      
      if((n * n + m * m) <= (radius * radius)) {
	pGrid->dpGrid[i][j] = dInitValue;
      }
    }
  }
}

void vHeatRelaxGridDoubleSeq(void) {
  sGridDouble dtemp;
  
  iAllocGridDouble(&dtemp, dGrid.iRows, dGrid.iCols);
  
  for(int i = 0; i < dtemp.iRows; i++) {
    for(int j = 0; j < dtemp.iCols; j++) {
      dtemp.dpGrid[i][j] = dGrid.dpGrid[i][j];
    }
  }
  
  for(int i = 1; i < dGrid.iRows - 1; i++) {
    for(int j = 1; j < dGrid.iCols - 1; j++) {
      
      dGrid.dpGrid[i][j] = dtemp.dpGrid[i][j] + (24/100.) * ((-4.) * dtemp.dpGrid[i][j] + dtemp.dpGrid[i+1][j] +
											     dtemp.dpGrid[i-1][j] +
											     dtemp.dpGrid[i][j+1] +
											     dtemp.dpGrid[i][j-1]);
    }
  }
}
  