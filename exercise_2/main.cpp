/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the "Parallel Computer Architecture" (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 2 - Heat Distribution
 * 
 * AUTHORS          Klaus Naumann
 *                  Jan Brodhaecker
 *
 * LAST CHANGE      03. Nov 2014
 * 
 ********************************************************************************/
#include <iostream>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

const double PHI = 24/100;

void print_usage(){
	cout << "Usage : \n";
	cout << "./aufgabe_2 <size> <m> <H> <iterations>";
}

unsigned long long rdtsc() {
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
    return ((unsigned long long) a) | (((unsigned long long) d) << 32);
}



double **initGrid(int size, double initValueH, int radius){
	int center = ceil(size/2);

	//init grid with 0

	//using +2 to prevent complex errorchecking
	double **grid = new double*[size+2];
	for(int i = 1; i <= size; i++) {
		grid[i] = new double[size+2];
		for(int j = 1; j <= size; j++) {
				grid[i][j] = 0.0;
		}
	}

	// set init circle
	// http://members.chello.at/~easyfilter/bresenham.html
	int xm = center;
	int ym = center;
	int x = -radius, y = 0, err = 2-2*radius; /* II. Quadrant */
	   do {
		  grid[xm-x][ym+y] = initValueH;
		  grid[xm-y][ym-x] = initValueH;
		  grid[xm+x][ym-y] = initValueH;
		  grid[xm+y][ym+x] = initValueH;
	      radius = err;
	      if (radius <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
	      if (radius > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
	   } while (x < 0);

	   return grid;
}


void calcNewGridRDTSC(double **oldGrid, int size, int iterations){
	double **newGrid = new double*[size+2];



	for(int cnt = 0; cnt < iterations; cnt++){
		unsigned long long t1, t2;
		t1 = rdtsc();
			for(int i = 1; i <= size; i++){
					for(int j = 1; j <= size; j++){
						newGrid[i][j] = oldGrid[i][j]+PHI*((-4)*oldGrid[i][j]+oldGrid[i+1][j]+oldGrid[i-1][j]+oldGrid[i][j+1]+oldGrid[i][j-1]);
					}
				}
			t2 = rdtsc();
			cout << "rdtsc() : - iteration -  "<< cnt << "- " << 1.0 * (t2 - t1) / 1600000.0 / 1000.0 << " s" << endl;
		}

	}


void calcNewGridGTOT(double **oldGrid, int size, int iterations){
	double **newGrid = new double*[size+2];



	for(int cnt = 0; cnt < iterations; cnt++){

		timeval t1, t2;
		gettimeofday(&t1, NULL);

		for(int i = 1; i <= size; i++){
				for(int j = 1; j <= size; j++){
					newGrid[i][j] = oldGrid[i][j]+PHI*((-4)*oldGrid[i][j]+oldGrid[i+1][j]+oldGrid[i-1][j]+oldGrid[i][j+1]+oldGrid[i][j-1]);
				}
			}

		gettimeofday(&t2, NULL);
		cout << "gettimeofday() - iteration : "<< cnt << " - " << ((t2.tv_sec - t1.tv_sec)+ ((t2.tv_usec - t1.tv_usec) / 1000000.0))<< " s" << endl;
	}
}




void printGrid(int size, double **grid){
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				if(grid[i][j] != 0){
					cout << "X";
				} else 	cout << " ";
			}
			cout << "\n";
		}
}


int main(int argc, char* argv[]) {
	/*if(argc < 4){
		print_usage();
	}*/
	
	int size, iterations;
	double radius, initValueH;

	size = atoi(argv[1]);
	radius = atof(argv[2]);
	initValueH = atof(argv[3]);
	iterations = atoi(argv[4]);

	double **grid = initGrid(size, radius, initValueH);

	cout << "GetTimeOfToday";
	calcNewGridGTOT(grid, size, iterations);

	cout << "\n";
	cout << "RDTSC";
	calcNewGridRDTSC(grid, size, iterations);
}


