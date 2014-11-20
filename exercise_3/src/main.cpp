/*************************************************************************************************
 *
 *        Heidelberg University - PCA Computing Exercise 03
 *
 *                           Group : PCA03
 * 		       Participant : Klaus Naumann
 *				     Jan Brodhaecker  
 *
 *                            File : main.cu
 *
 *                         Purpose : N-Body Simulation (2D)
 *
 *************************************************************************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "nbody.h"
using namespace std;

const double dt		= 10;			// step-size
const double iter	= 100;			// number of iterations

int main(int argc, char **argv) {
  
  int nbodies = 0;
  
  /* get commandline parameters */
  if (argc != 2) {
    cout << "Wrong number of arguments!" << endl;
    cout << "Usage: " << argv[0] << " <Number bodies>" << endl;
    return 1;
  }
  else {
    nbodies = atoi(argv[1]);
  }
  
  /* Initialize bodies */
  sBody *bodys = initBody(nbodies, 10);
  
  for(int i = 0; i < iter; i++) {
    for(int m = 0; m < nbodies; m++) {
      for(int n = 0; n < nbodies; n++) {
	if(m != n) {
	  applyForce(&bodys[m], &bodys[n], dt);
	}
      }
    }
    
    for(int x = 0; x < nbodies; x++) {
      newPos(&bodys[x], dt);
      if(i%10 == 0) {
	cout << "\n" << x << ". Body" << endl;
	outBody(&bodys[x]);
      }
    }
    
  }
  
  return 0;
}


