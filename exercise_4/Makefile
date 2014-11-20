#*************************************************************************************************
#
#        Heidelberg University - PCA Exercise 04
#
#                            Group : PCA03
#		       Participant : Klaus Naumann
#				     Jan Brodhaecker  
#
#                             File : Makefile
#
#                          Purpose : MVMULTI (Parallel POSIX Threads Version)
#
#*************************************************************************************************
 
CPP=g++
CFLAGS = -Wall

nbody :
	$(CPP) $(CFLAGS)	src/main.cpp \
				src/mvmulti.cpp \
				-o mvmulti

clean :
	rm -f mvmulti
