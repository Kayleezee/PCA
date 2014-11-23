/*************************************************************************************************
 *
 *        Heidelberg University - PCA Exercise 04
 *
 *                           Group : PCA03
 * 		       Participant : Klaus Naumann
 *				     Jan Brodhaecker  
 *
 *                            File : mvmultiply.cpp
 *
 *                         Purpose : Matrix-Vector-Multiplication (2D; parallel)
 *
 *************************************************************************************************/

#include <iostream>
#include <ctime>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

float 	**fmatrix, *fvector, *fresult;
double 	**dmatrix, *dvector, *dresult;

int 	size, numThreads;

/*************************************************************************************************
 GENERATING MATRICES
**************************************************************************************************/

/* generates Matrix with float elements */
float **fgenMatrix(int size) {	

	float **fmatrix = new float*[size];
	for(int i = 0; i < size; i++) {
		fmatrix[i] = new float[size];
		for(int j = 0; j < size; j++) {
			fmatrix[i][j] = (float)rand();
		}
	}

	return fmatrix;
}

/* generates Matrix with double elements */
double **dgenMatrix(int size) {	

	double **dmatrix = new double*[size];
	for(int i = 0; i < size; i++) {
		dmatrix[i] = new double[size];
		for(int j = 0; j < size; j++) {
			dmatrix[i][j] = (double)rand();
		}
	}

	return dmatrix;
}

/*************************************************************************************************
 GENERATING VECTORS
**************************************************************************************************/

/* generates Vector with float elements */
float *fgenVector(int size) {

	float *fvector = new float[size];
	for(int i = 0; i < size; i++) {
		fvector[i] = (float)rand();
	}

	return fvector;
}

double *dgenVector(int size) {

	double *dvector = new double[size];
	for(int i = 0; i < size; i++) {
		dvector[i] = (double)rand();
	}

	return dvector;
}

/*************************************************************************************************
 PRINT MATRIX
**************************************************************************************************/

void **foutMatrix() {
	cout << "Matrix:\n";
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cout << fmatrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

void **doutMatrix() {
	cout << "Matrix:\n";
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cout << dmatrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

/*************************************************************************************************
 PRINT VECTOR
**************************************************************************************************/

void **foutVector() {
	cout << "Vector:\n";	
	for(int i = 0; i < size; i++) {
		cout << fvector[i] << "\n";
	}
}

void **doutVector() {
	cout << "Vector:\n";	
	for(int i = 0; i < size; i++) {
		cout << dvector[i] << "\n";
	}
}

/*************************************************************************************************
 PRINT RESULT
**************************************************************************************************/

void **foutResult() {
	cout << "Vector:\n";	
	for(int i = 0; i < size; i++) {
		cout << fresult[i] << "\n";
	}
}

void **doutResult() {
	cout << "Vector:\n";	
	for(int i = 0; i < size; i++) {
		cout << dresult[i] << "\n";
	}
}

/*************************************************************************************************
 MATRIX VECTOR MULTIPLY (SEQUENTIAL) 
**************************************************************************************************/

float *fmvMulti() {
	
	float *fresult = new float[size];
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			fresult[i] += (fmatrix[i][j] * fvector[j]);	 
		}
	}

	return fresult;
}

double *dmvMulti() {
	
	double *dresult = new double[size];
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			dresult[i] += (dmatrix[i][j] * dvector[j]);	 
		}
	}

	return dresult;
}

/*************************************************************************************************
 MATRIX VECTOR MULTIPLY (PARALLEL) 
**************************************************************************************************/

void *fmvMultiPar(int Id) {
	
	int start = (Id * size) / numThreads;
	int end = (Id + 1) * (size / numThreads) - 1;
	cout << start << endl;
	cout << end << endl;
	
	for(int i = start; i <= end; i++) {
		for(int j = 0; j < size; j++) {
			fresult[i] += (fmatrix[i][j] * fvector[j]);
		}
	}
}

void *dmvMultiPar(int Id) {
	
	int start = Id * size / numThreads;
	int end = (Id + 1) * (size / numThreads) - 1;
	
	for(int i = start; i <= end; i++) {
		for(int j = 0; j < size; j++) {
			dresult[i] += (dmatrix[i][j] * dvector[j]);
		}
	}
}

/*************************************************************************************************
 WORKER FUNCTIONS (PARALLEL) 
**************************************************************************************************/

void *fworker(void *arg) {
	int Id = *((int *) arg);
	fmvMultiPar(Id);
	return NULL;
}

void *dworker(void *arg) {
	int Id = *((int *) arg);
	dmvMultiPar(Id);
	return NULL;
}

/*************************************************************************************************
 TIME MEASUREMENTS 
**************************************************************************************************/

double dStartGTOD(void) {
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec/1000000.0);
}

double dStopGTOD(double dStartTime) {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (t.tv_sec + (t.tv_usec/1000000.0)) - dStartTime;
}

/*************************************************************************************************
 PRINT USAGE
**************************************************************************************************/

void print_usage() {
	cout << endl;
	cout << "Usage:\n" << endl;
	//cout << "./" << argv[0] << endl;
	cout << "<S matrix size>" << endl;
	cout << "<R seed for random>" <<endl;
	cout << "<I iterations for time measurement>" << endl;
	cout << "<V variable type [0 = float; 1 = double]>" << endl;
	cout << "<T number of threads>" << endl;
	cout << "<D display mode  [0 = on; 1 = off]>" << endl;
} 

/*************************************************************************************************
 MAIN FUNCTION
**************************************************************************************************/

int main(int argc, char **argv) {
  
	size 		= atoi(argv[1]);
	int seed 	= atoi(argv[2]);
	int iter 	= atoi(argv[3]);
	int type 	= atoi(argv[4]);
	numThreads 	= atol(argv[5]);
	int display 	= 1;//= atoi(argv[3]);
	int *p;
	
	double dStart = 0.0, dElapsedSeq = 0.0, dElapsedPar = 0.0; 
	
	pthread_t* threads;
	
	srand(seed);
	
	if(argc != 7) {
		print_usage();
		return 1;
	}
	
	if(type == 0) {
		fmatrix = fgenMatrix(size);
		fvector = fgenVector(size);
		fresult = new float[size];
		
		threads = new pthread_t[numThreads];
		
		dStart = dStartGTOD();
		
		for(int n = 0; n < iter; n++) {
			for(int i = 0; i < numThreads; i++) {
				p = (int *) malloc(sizeof(int));
				*p = i;
				pthread_create(&threads[i], NULL, fworker, (void*)(p));
			}
			
			for(int i = 0; i < numThreads; i++) {
				pthread_join(threads[i], NULL);
			}
		}
		
		dElapsedPar = dStopGTOD(dStart) / iter;
		
		cout << "Type:\t\tFLOAT" << endl;
		cout << "Time for parallel computation:\t\t" << dElapsedPar << endl;;
		
		dStart = dStartGTOD();
		
		for(int n = 0; n < iter; n++) {
			fmvMulti();
		}
		
		dElapsedSeq = dStopGTOD(dStart) / iter;
		
		cout << "Time for sequential computation:\t" << dElapsedSeq << endl;
		cout << "Speed-Up:\t\t\t\t" << dElapsedSeq/dElapsedPar << endl;
	} else if(type == 1) {
		dmatrix = dgenMatrix(size);
		dvector = dgenVector(size);
		dresult = new double[size];
		
		threads = new pthread_t[numThreads];
		
		dStart = dStartGTOD();
		
		for(int n = 0; n < iter; n++) {
			for(int i = 0; i < numThreads; i++) {
				p = (int *) malloc(sizeof(int));
				*p = i;
				pthread_create(&threads[i], NULL, dworker, (void*)(p));
			}
			
			for(int i = 0; i < numThreads; i++) {
				pthread_join(threads[i], NULL);
			}
		}
		
		dElapsedPar = dStopGTOD(dStart) / iter;
		
		cout << "Type:\t\tDOUBLE" << endl;
		cout << "Time for parallel computation:\t\t" << dElapsedPar << endl;;
		
		dStart = dStartGTOD();
		
		for(int n = 0; n < iter; n++) {
			dmvMulti();
		}
		
		dElapsedSeq = dStopGTOD(dStart) / iter;
		
		cout << "Time for sequential computation:\t" << dElapsedSeq << endl;
		cout << "Speed-Up:\t\t\t\t" << dElapsedSeq/dElapsedPar << endl;
	} else {
		cout << endl;
		cout << "Wrong argument for variable type!" << endl;
		cout << "Please choose between the following options: " << endl;
		cout << "0 = float" << endl;
		cout << "1 = double" << endl;
	}
	
	return 0;
}
