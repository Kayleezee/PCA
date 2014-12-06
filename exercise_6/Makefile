#*************************************************************************************************
#
# Heidelberg University - PCA Exercise 06
#
# Group : 		PCA03
# Participant : Klaus Naumann
#				Jan Brodhaecker
#
# File : 		Makefile
#
# Purpose : 	EXERCISE 6 (Parallel OpenMP Version)
#
#*************************************************************************************************

CPP = g++
CFLAGS = -fopenmp

hellomp :
	$(CPP) $(CFLAGS)	src/part6.1/helloworld_openmp.cpp \
						-o hellomp

pi :
	$(CPP) $(CFLAGS)	src/part6.2/numerical_integration_openmp.cpp \
						-o pi

mvmult:
	$(CPP) $(CFLAGS)	src/part6.3/main.cpp \
						src/part6.3/inc/matrix.cpp \
						-o mvmult

clean :
	rm -f hellomp
	rm -f pi
	rm -f mvmult
