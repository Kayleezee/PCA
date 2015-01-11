#*************************************************************************************************
#
# Heidelberg University - PCA Exercise 08
#
# Group : 		PCA03
# Participant : Klaus Naumann
#				Jan Brodhaecker
#
# File : 		Makefile
#
# Purpose : 	EXERCISE 8
#
#*************************************************************************************************

MPI = mpic++
CC = gcc
CPP = g++
CFLAGS1 = -fopenmp
CFLAGS2 = -Wall

nbody :
	$(CPP) $(CFLAGS1)	src/part8.1/main.cpp \
						src/part8.1/nbody.cpp \
						src/part8.1/nbody.hpp \
						-o nbody

hello :
	$(MPI) $(CFLAGS2) 	src/part8.2/hellompi.cpp \
						-o hello

latency :
	$(MPI) $(CFLAGS2) 	src/part8.3/measure_latency.cpp \
						-o latency

clean :
	rm -f nbody
	rm -f hello
	rm -f latency
