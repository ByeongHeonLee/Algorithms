mat : smatrix.o main.o
	g++ -o mat smatrix.o main.o

smatrix.o : smatrix.cpp
	g++ -c -o smatrix.o smatrix.cpp

main.o : main.cpp
	g++ -c -o main.o main.cpp

clear :
	rm *.o mat