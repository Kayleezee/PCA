/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 07
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        main.cpp
*
* Purpose :     N-BODY SIMULATION (3D) (Parallel OpenMP Version)
*
* Last Change : 22. Dec. 2014
*
*************************************************************************************************/
#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include "nbody.hpp"
using namespace std;

const double dt		= 10;			// step-size
const double iter	= 1000;			// number of iterations

int main(int argc, char **argv) {

  int nbodies;
  int iNumThreads;
  int iMyID;

  double dStart     = 0.0;
  double dTimeSeq   = 0.0;
  double dTimePar   = 0.0;

  /* get commandline parameters */
  if (argc != 3) {
    cout << "Wrong number of arguments!" << endl;
    cout << "Usage: " << endl;
    cout << "\t" << argv[0] << endl;
    cout << "\t<N number of bodies>" << endl;
    cout << "\t<T number of threads>" << endl;
    return EXIT_FAILURE;
  }
  else {
    nbodies = atoi(argv[1]);
    iNumThreads = atoi(argv[2]);
  }

  /* Initialize bodies */
  sBody *bodys = initBody(nbodies, 10);

  /* Parallel Part */
  dStart = omp_get_wtime();

  #pragma omp parallel
  {
    for(int i = 0; i < iter; i++) {

        iMyID = omp_get_thread_num();

        for(int m = iMyID; m < nbodies; m += iNumThreads) {
            for(int n = m + 1; n < nbodies; n++) {
                applyForce(&bodys[m], &bodys[n], dt);
            }
        }

        #pragma omp barrier

        for(int x = iMyID; x < nbodies; x += iNumThreads) {
            newPos(&bodys[x], dt);
            //if(i%100 == 0) {
                //cout << "\n" << x << ". Body" << endl;
                //outBody(&bodys[x]);
            //}
        }
        #pragma omp barrier
    }
  }

  dTimePar = (omp_get_wtime() - dStart) / iter;


  /* Sequential Part */
  dStart = omp_get_wtime();

  for(int i = 0; i < iter; i++) {

        for(int m = 0; m < nbodies; m++) {
            for(int n = m + 1; n < nbodies; n++) {
                applyForce(&bodys[m], &bodys[n], dt);
            }
        }

        for(int x = 0; x < nbodies; x++) {
            newPos(&bodys[x], dt);
            //if(i%100 == 0) {
                //cout << "\n" << x << ". Body" << endl;
                //outBody(&bodys[x]);
            //}
        }
  }

  dTimeSeq = (omp_get_wtime() - dStart) / iter;

  printf("\n#########################################################\n#\n#\n#");
  printf("\n#\t Parallel 3D N-Body Simulation with OpenMP \n#");
  printf("\n#\t Calculation time per Iteration: \n#");
  printf("\n#\t Parallel       : %lfs \n#", dTimePar);
  printf("\n#\t Sequential     : %lfs \n#", dTimeSeq);
  printf("\n#\t Speed-Up       : %lf  \n#", dTimeSeq/dTimePar);
  printf("\n#\n#\n#########################################################\n\n\n");

  return EXIT_SUCCESS;
}


