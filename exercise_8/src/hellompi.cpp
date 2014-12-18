/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 08
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        hellompi.cpp
*
* Purpose :     HELLO WORLD (Parallel MPI Version)
*
* Last Change : 18. Dec. 2014
*
*************************************************************************************************/
#include <mpi.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv) {
	int size;
	int rank;	

	char hostname[50];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	gethostname(hostname, 50);

	cout << "Hello World! from Process No.: " << rank 
		 << " of " << size << " Processes "
		 << " (Host: " << hostname << ")" << endl; 

	MPI_Finalize();

	return EXIT_SUCCESS;
}
