poly : polynomial.o main.o
	g++ -o poly polynomial.o main.o

polynomial.o : polynomial.cpp
	g++ -c -o polynomial.o polynomial.cpp

main.o : main.cpp
	g++ -c -o main.o main.cpp

clear :
	rm *.o poly