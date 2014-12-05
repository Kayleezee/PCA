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
	$(CPP) $(CFLAGS)	src/helloworld_openmp.cpp \
						-o hellomp

pi :
	$(CPP) $(CFLAGS)	src/numerical_integration_openmp.cpp \
						-o pi

clean :
	rm -f hellomp
	rm -f pi
