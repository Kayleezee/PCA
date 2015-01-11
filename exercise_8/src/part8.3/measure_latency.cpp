/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 08
*
* Group :       PCA03
* Participant : Klaus Naumann
*				Jan Brodhaecker
*
* File :        measure_latency.cpp
*
* Purpose :     HALF-ROUND-TRIP LATENCY (Parallel MPI Version)
*
* Last Change : 10. Jan. 2014
*
*************************************************************************************************/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "mpi.h"

#define MS 	1024*1024		// define max. message size
using namespace std;

int main(int argc, char** argv)
{
    char    *signal;
    int     rank, size, loops;
    double  starttime, endtime, t;
    ofstream fout;
    fout.open("result_latency.txt");

    MPI_Init( &argc, &argv );

    MPI_Status   status;
    MPI_Request  req;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size < 2) {
	cout << "Minimum of 2 Processes required! Aborting programm!";
	MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int k = 1; k <= MS; k *= 2) {
        loops = 100;

        signal = new char[k];

        if (rank == 0) {
            /* Synchronize both processes */

            MPI_Barrier(MPI_COMM_WORLD);
            starttime = MPI_Wtime();

            for (int j = 0; j < loops; j++) {

                MPI_Isend( signal, k, MPI_CHAR, 1, j, MPI_COMM_WORLD, &req );
                MPI_Wait( &req, &status );
                MPI_Irecv( signal, k, MPI_CHAR, 1, j, MPI_COMM_WORLD, &req );
                MPI_Wait( &req, &status );

            }
            endtime = MPI_Wtime();

            t = (endtime - starttime) / loops;

        } else {
            /* Synchronize both processes */

            MPI_Barrier(MPI_COMM_WORLD);

            for (int j = 0; j < loops; j++) {

                MPI_Irecv( signal, k, MPI_CHAR, 0, j, MPI_COMM_WORLD, &req );
                MPI_Wait( &req, &status );
                MPI_Isend( signal, k, MPI_CHAR, 0, j, MPI_COMM_WORLD, &req );
                MPI_Wait( &req, &status );

            }
        }


        if (rank == 0) {

            if(!fout) {
                cerr << "Could not open file!" << endl;
            }
            fout << k << ";" << t/2.0 << endl;
            //cout << "Full round-trip:\t" << k << " Bytes" << "\t\t" << t << endl;
            cout << "Half round-trip:\t" << k << "\tBytes" << "\t\t" << t/2.0 << endl;

        }
    }
    fout.close();
    MPI_Finalize( );
    return EXIT_SUCCESS;
}
