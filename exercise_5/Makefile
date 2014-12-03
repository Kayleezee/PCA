#*************************************************************************************************
#
# Heidelberg University - PCA Exercise 04
#
# Group : 	PCA03
# Participant : Klaus Naumann
#		Jan Brodhaecker  
#
# File : 	Makefile
#
# Purpose : 	HEAT RELAXATION (Parallel POSIX Threads Version)
#
#*************************************************************************************************
 
CC=gcc
CFLAGS = -pthread

heatrelax :
	$(CC) $(CFLAGS)	src/main.c \
			src/heat_relaxation.c \
			src/time_measurement.c \
			-o heatrelax

clean :
	rm -f heatrelax
