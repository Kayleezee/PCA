/*************************************************************************************************
 *
 *        Heidelberg University - PCA Exercise 03
 *
 *                           Group : PCA03
 * 		       Participant : Klaus Naumann
 *				     Jan Brodhaecker  
 *
 *                            File : nbody.h
 *
 *                         Purpose : N-Body Simulation (2D)
 *
 *************************************************************************************************/
#ifndef NBODY_H
#define NBODY_H

#define G 0.00000000006673

typedef struct sBody {
  double dM;		// mass
  double dPx;		// x-position
  double dPy;		// y-position
  double dVx;		// velocity in x-direction
  double dVy;		// velocity in y-direction
} sBody;

sBody* initBody(int, int);

double distance(double, double);

void applyForce(sBody *, sBody *, double);

void newPos(sBody *, double);

void outBody(sBody *);

#endif
  