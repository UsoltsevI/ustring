all: ustring.o test.o
	g++ -std=c++20 ustring.o test.o -o us.x

ustring.o: ustring.cpp
	g++ -std=c++20 ustring.cpp -c

test.o: test.cpp
	g++ -std=c++20 test.cpp -c
