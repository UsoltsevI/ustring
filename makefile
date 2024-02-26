all: ustring.o test.o
	g++ ustring.o test.o -o us.x

ustring.o: ustring.cpp
	g++ -O2 ustring.cpp -c

test.o: test.cpp
	g++ -O2 test.cpp -c
