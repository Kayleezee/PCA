/*************************************************************************************************
*
* Heidelberg University - PCA Exercise 06
*
* Group :       PCA03
* Participant : Klaus Naumann
*		Jan Brodhaecker
*
* File :        part_1.c
*
* Purpose :     Hello World (OpenMP)
*
* Last Change : 02. Dec. 2014
*
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_usage() {
  printf("\nUsage:\n\n./hello_world\n"
         "\n\t<T: number of threads\n");
}

int main(int argc, char **argv) {
  
  int i, iNumThreads;
  
  if(argc != 2) {
    print_usage();
    return EXIT_FAILURE;
  }
  
  iNumThreads = atoi(argv[1]);
  
  omp_set_num_threads(iNumThreads);
  
  #pragma omp parallel for
  for(i = 0; i < iNumThreads; i++) {
    const int iMyId = omp_get_thread_num();
    
    if(iMyId == 0) {
      printf("\nTotal threads: %d\n", omp_get_num_threads());
    }
    
    printf("\nHello world! Here's thread no. %d\n", iMyId);
    
  }
  
  return EXIT_SUCCESS;
}