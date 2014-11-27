/*************************************************************************************************
*
*        Heidelberg University - PCA Exercise 05
*
*                            Group : PCA03
*		       Participant : Klaus Naumann
*				     Jan Brodhaecker  
*
*                             File : time_measurement.cpp
*
*                          Purpose : HEAT RELAXATION (Parallel POSIX Threads Version)
* 
* 		       Last Change : 27. Nov. 2014
*
*************************************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include "../inc/time_measurement.hpp"

/* Start time-measurement with gettimeofday() */
double dStartMeasurement(void)
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec+(t.tv_usec/1000000.0);
}

/* Stop time-measurement with gettimeofday() */
double dStopMeasurement(double dStartTime)
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec+(t.tv_usec/1000000.0)) - dStartTime;
}