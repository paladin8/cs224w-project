CXX=g++
#CXX=/usr/bin/x86_64-w64-mingw32-g++.exe

CXXFLAGS=-O2
#CXXFLAGS+=-m64

hnetwork_test: hnetwork_test.cpp hnetwork.o deg_dist.o
	${CXX} ${CXXFLAGS} hnetwork_test.cpp hnetwork.o deg_dist.o -o hnetwork_test

hnetwork.o: hnetwork.cpp hnetwork.h
	${CXX} ${CXXFLAGS} -c hnetwork.cpp

deg_dist.o: deg_dist.cpp deg_dist.h
	${CXX} ${CXXFLAGS} -c deg_dist.cpp
	
clean:
	rm -f *.o hnetwork_test.exe
