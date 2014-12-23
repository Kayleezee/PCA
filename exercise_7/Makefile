#*************************************************************************************************
#
# Heidelberg University - PCA Exercise 07
#
# Group : 		PCA03
# Participant : Klaus Naumann
#				Jan Brodhaecker
#
# File : 		Makefile
#
# Purpose : 	EXERCISE 7 (Parallel OpenMP Version)
#
#*************************************************************************************************

CC = gcc
CPP = g++
CFLAGS = -fopenmp

heatrelax :
	$(CC) $(CFLAGS)	part7.1/src/main.c \
			part7.1/src/heat_relaxation.c \
			part7.1/src/time_measurement.c \
			-o heatrelax

nbody :
	$(CPP) $(CFLAGS) part7.2/src/main.cpp \
			part7.2/src/nbody.cpp \
			-o nbody

clean :
	rm -f heatrelax
	rm -f nbody
