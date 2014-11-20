/*************************************************************************************************
 *
 *        Heidelberg University - PCA Exercise 03
 *
 *                           Group : PCA03
 * 		       Participant : Klaus Naumann
 *				     Jan Brodhaecker  
 *
 *                            File : nbody.cpp
 *
 *                         Purpose : N-Body Simulation (2D)
 *
 *************************************************************************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "stdio.h"
#include "nbody.h"
using namespace std;


/* create new bodies */
sBody* initBody(int nbodies, int max) {
  sBody *bodys = new sBody[nbodies];
  
  
  for(int i = 0; i < nbodies; i++) {
    
    bodys[i].dM = (double)(rand()%max);
    bodys[i].dPx = (double)(rand()%max);
    bodys[i].dPy = (double)(rand()%max);
    bodys[i].dVx = 0.0;
    bodys[i].dVy = 0.0;
  }
  
  return bodys;
}


/* applyForce */
void applyForce(sBody *m1, sBody *m2, double dt) {
  
  double distX = m2->dPx - m1->dPx;
  double distY = m2->dPy - m1->dPy;
  
  double Fx = (G * m1->dM * m2->dM) / (abs(distX) * abs(distX));
  double Fy = (G * m1->dM * m2->dM) / (abs(distY) * abs(distY));
  
  double ax1 = Fx / m1->dM;
  double ay1 = Fy / m1->dM;
  
  double ax2 = Fx / m2->dM;
  double ay2 = Fy / m2->dM;
  
  m1->dVx += ax1 * dt;
  m1->dVy += ay1 * dt;
  
  m2->dVx += ax2 * dt;
  m2->dVy += ay2 * dt;
}


/* newPos */
void newPos(sBody *body, double dt) {
  body->dPx += dt * body->dVx;
  body->dPy += dt * body->dVy;
}


/* outBody */
void outBody(sBody *body) {
  
  printf("Mass: \t %.30f \n", body->dM);
  printf("Position X: \t %.30f \n", body->dPx);  
  printf("Position Y: \t %.30f \n", body->dPy); 
  printf("Velocity X: \t %.30f \n", body->dVx);
  printf("Velocity Y: \t %.30f \n", body->dVy);
  
}

