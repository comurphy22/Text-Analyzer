make: proj6.o
	g++ proj6.o -o a.out
proj6.o: proj6.cpp
	g++ -c proj6.cpp
clean: 
	rm *.o proj6
