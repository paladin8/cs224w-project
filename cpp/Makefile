hnetwork_test: hnetwork_test.cpp hnetwork.o deg_dist.o
	g++ -O2 hnetwork_test.cpp hnetwork.o deg_dist.o -o hnetwork_test

hnetwork.o: hnetwork.cpp hnetwork.h
	g++ -O2 -c hnetwork.cpp

deg_dist.o: deg_dist.cpp deg_dist.h
	g++ -O2 -c deg_dist.cpp
	
clean:
	rm *.o *.exe
