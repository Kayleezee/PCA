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
#                          Purpose : MVMULTIPLY (Parallel POSIX Threads Version)
#
#*************************************************************************************************
 
CPP=g++
CFLAGS = -pthread

nbody :
	$(CPP) $(CFLAGS)	src/mvmultiply.cpp \
				-o mvmultiply

clean :
	rm -f mvmultiply
