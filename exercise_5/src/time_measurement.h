/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 05
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        time_measurement.h
*
* Purpose :     HEAT RELAXATION (Parallel POSIX Threads Version)
*
* Last Change : 02. Dec. 2014
*
*************************************************************************************************/
#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

/*************************************************************************************************
* Function description:		Starts a time-measurement, based on the gettimeofday() functions
*               		It has a resolution up to one microsecond.
* Parameter:			void
*
* Return:      			double: elapsed seconds this day (is the parameter for dstopMesGTOD())
*************************************************************************************************/
double dStartMeasurement(void);

/*************************************************************************************************
* Function description:		Stops the time-measurement, based on the gettimeofday() functions.
*               		It has a resolution up to one microsecond.
* Parameter:			double: return-value of dstartMesGTOD()
*
* Return:			double: elapsed seconds since dstartMesGTOD()
*************************************************************************************************/
double dStopMeasurement(double);

#endif
