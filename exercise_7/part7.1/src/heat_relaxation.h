/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 07
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        head_relaxation.h
*
* Purpose :     HEAT RELAXATION (Parallel OpenMP Version)
*
* Last Change : 22. Dec. 2014
*
*************************************************************************************************/
#ifndef HEAT_RELAXATION_H
#define HEAT_RELAXATION_H
/*************************************************************************************************
 HEADER
**************************************************************************************************/
typedef struct sGridDouble {
  int iRows;			// amount of rows in grid
  int iCols;			// amount of columns in grid
  double **dpGrid;		// double pointer to grid elements
} sGridDouble;


sGridDouble dGrid, dTemp;
int iSize, iNumThreads;
int r;


/*************************************************************************************************
* Function description: 	allocates memory for grid elements (type: double)
*
* Parameter:			sGridDouble: 	pointer to sGridDouble for which memory will be allocated
* 				Integer:	grid rows
* 				Integer:	grid columns
*
* Return:		        Integer: 	Success or Fail
*************************************************************************************************/
int iAllocGridDouble(sGridDouble *, int, int);

/*************************************************************************************************
* Function description: 	Initialization of Grid with 0.0 (type: double)
*
* Parameter:			sGridDouble: 	pointer to sGridDouble
*
* Return:		        Void
*************************************************************************************************/
void vInitGridDouble(sGridDouble *);

/*************************************************************************************************
* Function description: 	Deletes allocated memory of grid
*
* Parameter:			sGridDouble: 	pointer to sGridDouble
*
* Return:		        Void
*************************************************************************************************/
void vDeleteGridDouble(sGridDouble *);

/*************************************************************************************************
* Function description: 	Output for grid elements
*
* Parameter:			sGridDouble: 	pointer to sGridDouble
*
* Return:		        Void
*************************************************************************************************/
void vOutputGridDouble(sGridDouble *);

/*************************************************************************************************
* Function description: 	Fill inner grid with initValue
*
* Parameter:			sGridDouble: 	pointer to sGridDouble
* 				Integer:	diameter
* 				Double:		initial Value
*
* Return:		        Void
*************************************************************************************************/
void vFillInnerGridDouble(sGridDouble *, int, double);

/*************************************************************************************************
* Function description: 	Heat Relaxation (sequential)
*
* Parameter:			Void
*
* Return:		        Void
*************************************************************************************************/
void vHeatRelaxGridDoubleSeq(void);

/*************************************************************************************************
* Function description: 	Heat Relaxation (parallel PThreads)
*
* Parameter:			Integer *:	pointer to thread ID
*
* Return:		        Void
*************************************************************************************************/
void vHeatRelaxGridDoubleParPThreads(int *);

/*************************************************************************************************
* Function description: 	Heat Relaxation (parallel OpenMP)
*
* Parameter:			Void
*
* Return:		        Void
*************************************************************************************************/
void vHeatRelaxGridDoubleParOpenMP(int);

/*************************************************************************************************
* Function description: 	Barrier for parallel heat relaxation
*
* Parameter:			Void
*
* Return:		        Void
*************************************************************************************************/
void Barrier(void);

#endif
