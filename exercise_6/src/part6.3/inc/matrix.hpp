/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 06
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        matrix.hpp
*
* Purpose :     MATRIX VECTOR MULTIPLY (Parallel OpenMP Version)
*
* Last Change : 05. Dec. 2014
*
*************************************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

extern int threads;

/*************************************************************************************************
* Function description: 	allocates memory for matrix elements and assign to random number
*                           (type: float or double)
*
* Parameter:			    Integer:	size of matrix
*
* Return:		            Integer: 	matrix
*************************************************************************************************/
float **fgenMatrix(int);
double **dgenMatrix(int);

/*************************************************************************************************
* Function description: 	allocates memory for vector elements and assign to random number
*                           (type: float or double)
*
* Parameter:			    Integer:	size of vector
*
* Return:		            Integer: 	vector
*************************************************************************************************/
float *fgenVector(int);
double *dgenVector(int);

/*************************************************************************************************
* Function description: 	Prints out matrix
*
* Parameter:			    Integer:	    size of matrix
*                           Double Pointer: double pointer to matrix elements
*
* Return:		            Void
*************************************************************************************************/
void **foutMatrix(int, float **);
void **doutMatrix(int, double **);

/*************************************************************************************************
* Function description: 	Prints out vector
*
* Parameter:			    Integer:	size of vector
*                           Pointer:    pointer to vector elements
*
* Return:		            Void
*************************************************************************************************/
void **foutVector(int, float *);
void **doutVector(int, double *);

/*************************************************************************************************
* Function description: 	Prints out vector
*
* Parameter:			    Integer:	size of vector
*                           Pointer:    pointer to vector elements
*
* Return:		            Void
*************************************************************************************************/
void **foutResult(int, float *);
void **doutResult(int, double *);

/*************************************************************************************************
 MATRIX VECTOR MULTIPLY (SEQUENTIAL)
**************************************************************************************************/
/*************************************************************************************************
* Function description: 	matrix vector multiply for matrix/vector of type float and double
*                           (type: float or double)
*
* Parameter:			    Integer:    	size of vector
*                           Double Pointer: double pointer to matrix elements
*                           Single Pointer: pointer to vector elements
*
* Return:		            Double Pointer: double pointer to result matrix
*************************************************************************************************/
float *fmvMulti(int, float **, float *);
double *dmvMulti(int, double **, double *);

/*************************************************************************************************
 MATRIX VECTOR MULTIPLY (PARALLEL OPENMP)
**************************************************************************************************/
/*************************************************************************************************
* Function description: 	matrix vector multiply for matrix/vector of type float and double
*                           (type: float or double)
*
* Parameter:			    Integer:    	size of vector
*                           Double Pointer: double pointer to matrix elements
*                           Single Pointer: pointer to vector elements
*
* Return:		            Double Pointer: double pointer to result matrix
*************************************************************************************************/
float *fmvMultiPar(int, float **, float *);
double *dmvMultiPar(int, double **, double *);

#endif
