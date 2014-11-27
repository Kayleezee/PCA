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
#include "../inc/time_measurement.hpp"
#include "../inc/heat_relaxation.hpp"
using namespace std;

sGridDouble dGrid;
int numThreads;

void print_usage(){
	cout << "Usage : \n";
	cout << "./aufgabe_2 <size> <m> <H> <iterations> <display>";
}

int main(int argc, char** argv) {

  /* Input from commandline */
  int iSize 		= atoi(argv[1]);
  int iDiameter 	= atoi(argv[2]);
  double dInitValueH 	= atof(argv[3]);
  
  if(argc != 4) {
    print_usage();
  }
  //int iterations = atoi(argv[4]);
  //int display = atoi(argv[5]);

  /*
  // Do Iterations for the heat relaxation
  for(int i = 0; i < iterations; i++) {
    cout << "\n";		
    cout << (i + 1) <<". Iteration: \n";			
    grid = heatRelaxGTOD(grid, size);
    heatRelaxRDTSC(grid, size);
    cout << (i + 1) <<". Iteration: \n";
    if(display == 1 && iterations == 1 && size <= 15) {
      outMatrix(size, grid);
    }
  }
  */
  
  iAllocGridDouble(&dGrid, iSize, iSize);
  vInitGridDouble(&dGrid);
  vOutputGridDouble(&dGrid);
  vFillInnerGridDouble(&dGrid, iDiameter, dInitValueH);
  for(int i = 0; i < 100; i++) {
    cout << i << ". Iteration:" << endl;
    vOutputGridDouble(&dGrid);
    vHeatRelaxGridDoubleSeq();
  }

  return 0;
}
