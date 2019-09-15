CFLAGS = -Wall -Wextra -DDebug -g -std=c++14

bohn_p1: Structs.h Classes.o bohn_p1.o
	g++ Structs.h Classes.o bohn_p1.o -o bohn_p1

bohn_p1.o: bohn_p1.cpp
	g++ -c $(CFLAGS) bohn_p1.cpp

Classes.o: Classes.cpp Structs.h
	g++ -c $(CFLAGS) Classes.cpp

clean:
	rm -rf bohn_p1
	rm -rf bohn_p1.o
	rm -rf Classes.o
