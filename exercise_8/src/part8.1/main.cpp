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
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include "nbody.hpp"
#include <typeinfo>
using namespace std;

const double dt		= 10;			// step-size
const double iter	= 100;			// number of iterations

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

  ofstream fout;
  fout.open("results_nbody.txt", fstream::app);

  /* Initialize bodies */
  sBody *bodysPar = initBody(nbodies, 10);
  sBody *bodysSeq = initBody(nbodies, 10);

  /* Parallel Part */
  dStart = omp_get_wtime();

  #pragma omp parallel
  {
    for(int i = 0; i < iter; i++) {

        iMyID = omp_get_thread_num();

        for(int m = iMyID; m < nbodies; m += iNumThreads) {
            for(int n = m + 1; n < nbodies; n++) {
                applyForce(&bodysPar[m], &bodysPar[n], dt);
            }
        }

        #pragma omp barrier

        for(int x = iMyID; x < nbodies; x += iNumThreads) {
            newPos(&bodysPar[x], dt);
            //if(i%100 == 0) {
                //cout << "\n" << x << ". Body" << endl;
                //outBody(&bodys[x]);
            //}
        }
        #pragma omp barrier
    }
  }

  dTimePar = (omp_get_wtime() - dStart);

  /* Sequential Part */
  dStart = omp_get_wtime();

  for(int i = 0; i < iter; i++) {

        for(int m = 0; m < nbodies; m++) {
            for(int n = m + 1; n < nbodies; n++) {
                applyForce(&bodysSeq[m], &bodysSeq[n], dt);
            }
        }

        for(int x = 0; x < nbodies; x++) {
            newPos(&bodysSeq[x], dt);
            //if(i%100 == 0) {
                //cout << "\n" << x << ". Body" << endl;
                //outBody(&bodys[x]);
            //}
        }
  }

  dTimeSeq = (omp_get_wtime() - dStart);

  printf("\n#########################################################\n#\n#\n#");
  printf("\n#\t Parallel 3D N-Body Simulation with OpenMP \n#");
  printf("\n#\t N-Bodies       : %d", nbodies);
  printf("\n#\t Threads        : %d", iNumThreads);
  printf("\n#");
  printf("\n#\t Calculation time (total): \n#");
  printf("\n#\t Parallel       : %lfs", dTimePar);
  printf("\n#\t Sequential     : %lfs", dTimeSeq);
  printf("\n#");
  printf("\n#\t Calculation time per Iteration: \n#");
  printf("\n#\t Parallel       : %lfs", dTimePar/iter);
  printf("\n#\t Sequential     : %lfs", dTimeSeq/iter);
  printf("\n#\t Speed-Up       : %lf  \n#", dTimeSeq/dTimePar);
  printf("\n#\n#\n#########################################################\n\n\n");


  fout  << nbodies << ";"
        << iNumThreads << ";"
        << dTimePar/iter << ";"
        << dTimeSeq/iter << ";"
        << dTimeSeq/dTimePar << endl;

  fout.close();
  return EXIT_SUCCESS;
}


