#*************************************************************************************************
#
#        Heidelberg University - PCA Exercise 05
#
#                            Group : PCA03
#		       Participant : Klaus Naumann
#				     Jan Brodhaecker  
#
#                             File : Makefile
#
#                          Purpose : HEAT RELAXATION (Parallel POSIX Threads Version)
#
#*************************************************************************************************
 
CPP=g++
CFLAGS = -pthread

nbody :
	$(CPP) $(CFLAGS)	src/main.cpp \
				src/heat_relax.cpp \
				src/time_measurement.cpp \
				-o heat_relax

clean :
	rm -f heat_relax
