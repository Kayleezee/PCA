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
#include <unistd.h>

using namespace std;

const double g 		= 6.673 * 10e-11;	// gamma
const double dt		= .001;		// step-size
typedef double vector2[2];


int main(int argc, char **argv) {
  
  /* number of bodies */
  int nbodies = 100, seed = 8;
  srand(seed);
  /* time measurement */
  //double t, tend;
  
  /* get commandline parameters */
  if (argc != 2) {
    cout << "Wrong number of arguments!" << endl;
    cout << "Usage: ./nbody <N>" << endl;
    return 0;
  }
  else {
    nbodies = atoi(argv[1]);
  }
  
  /* dynamic arrays for position, velocity and mass of bodies */
  double *m 	= new double[nbodies];
  vector2 *v	= new vector2[nbodies];
  vector2 *xy 	= new vector2[nbodies];
  vector2 *a	= new vector2[nbodies];
  
  /* initialise mass of bodies */
  for(int i = 0; i < nbodies; i++) {
    m[i] = rand();
  }
  
  for(int i = 0; i < nbodies; i++) {
    v[i][0] = v[i][1] = 0.0;
  }
  
  for(int i = 0; i < nbodies; i++) {
    xy[i][0] = 3+i;//rand();
    xy[i][1] = 7+i;//rand();
  }
  
  double Fx, Fy, rxij, ryij, sx, sy;
  
  for(double j = 0; j < 0.01; j += dt) {
  for(int i = 0; i < nbodies; i++) {
    for(int j = 0; j < nbodies; j++) {
      if(j != i) {
	
	rxij = xy[j][0] - xy[i][0];
	ryij = xy[j][1] - xy[i][1];
	
	Fx = g*((m[i]*m[j])/abs(rxij*rxij))*rxij;
	Fy = g*((m[i]*m[j])/abs(ryij*ryij))*ryij;
	
	a[i][0] += Fx/m[i];
	a[i][1] += Fy/m[i];
	
      }
    }
    v[i][0] = a[i][0] * dt;
    v[i][1] = a[i][1] * dt;
    
    sx = v[i][0] * dt;
    sy = v[i][1] * dt;
    
    xy[i][0] += sx;
    xy[i][1] += sy;
    
    cout << i << ". Element:" << endl;
    cout << m[i] << "\t" << v[i][0] << "/" << v[i][1] << "\t" << xy[i][0] << "/" << xy[i][1] << "\t" 
				      << a[i][0] << "/" << a[i][1] << endl;
    cout << endl;
    cout << endl;
  }
  }
  /*
  for(int j = 0; j < 1000; j += dt) {
    for(int i = 0; i < nbodies; i++) {
      cout << m[i] << "\t" << v[i][0] << "/" << v[i][1] << "\t" << xy[i][0] << "/" << xy[i][1] << "\t" 
				      << a[i][0] << "/" << a[i][1] << endl;
    }
    cout << endl;
    cout << endl;
  }
  */
  
  
  
  return 0;
}


