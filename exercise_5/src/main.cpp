/*************************************************************************************************
*
*        Heidelberg University - PCA Exercise 05
*
*                            Group : PCA03
*		       Participant : Klaus Naumann
*				     Jan Brodhaecker  
*
*                             File : main.cpp
*
*                          Purpose : HEAT RELAXATION (Parallel POSIX Threads Version)
* 
* 		       Last Change : 27. Nov. 2014
*
*************************************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <stdint.h>
#include "../inc/time_measurement.hpp"
#include "../inc/heat_relaxation.hpp"
using namespace std;

sGridDouble dGrid, dTemp;
int iSize, iNumThreads;

void print_usage(){
	cout << "Usage : \n";
	cout << "./aufgabe_2 <size> <m> <H> <iterations> <display>";
}
/*
void **dworker(void *arg) {
	int Id = *((int *) arg);
	vHeatRelaxGridDoublePar(Id);
	return NULL;
}
*/
int main(int argc, char** argv) {

  /* Input from commandline */
  //iSize 		= atoi(argv[1]);
  //int iDiameter 	= atoi(argv[2]);
  iSize =	1024;
  int iDiameter = 128;
	double dInitValueH 	= atof(argv[1]);
  int display = atoi(argv[2]);
  int iNumThreads = atoi(argv[3]);
  
  double dStart = 0.0,/* dElapsedSeq = 0.0, */dElapsedPar = 0.0;
  pthread_t* threads;
  
  if(argc != 4) {
    print_usage();
  }
  
  iAllocGridDouble(&dGrid, iSize, iSize);
  iAllocGridDouble(&dTemp, iSize, iSize);
  vInitGridDouble(&dGrid);
  vInitGridDouble(&dTemp);
  
  vFillInnerGridDouble(&dGrid, iDiameter, dInitValueH);
  
  if((display == 1) && (iSize <= 10)) {
  	vOutputGridDouble(&dGrid);
  	vOutputGridDouble(&dTemp);
  }

	threads = new pthread_t[iNumThreads];
	
	
  for(int k = 0; k < 2; k++) {
  
  for(int i = 0; i < dGrid.iRows; i++) {
  	for(int j = 0; j < dGrid.iCols; j++) {
  		dTemp.dpGrid[i][j] = dGrid.dpGrid[i][j];
  	}
  }
  
  vOutputGridDouble(&dGrid);
  vOutputGridDouble(&dTemp);
  
  cout << "reached [threads init]!" << endl;
  dStart = dStartMeasurement();
  
  cout << "reached [started measurement]!" << endl;
  
  for(int i = 1; i < iNumThreads; i++) {
		pthread_create(&threads[i], NULL, vHeatRelaxGridDoublePar, reinterpret_cast<void*>(&i));
		cout << "reached [thread creation]!" << endl;
  }
  
  vOutputGridDouble(&dGrid);
  vOutputGridDouble(&dTemp);
  
  cout << "reached [before join]!" << endl;
  
  for(int i = 0; i < iNumThreads; i++) {
  	pthread_join(threads[i], NULL);
  }
	
	vOutputGridDouble(&dGrid);
	vOutputGridDouble(&dTemp);
	dElapsedPar = dStopMeasurement(dStart);
	
	if((display == 1) && (iSize <= 10)) {
  	vOutputGridDouble(&dGrid);
  }
  
  cout << "\nTime for parallel computation:\t\t" << dElapsedPar << endl;
	
	}
  return 0;
}
