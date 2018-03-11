#I am a makefile

main:  AVL.o  main.o
	g++ -std=c++11 AVL.o main.o -o main

AVL.o: AVL.cpp
	g++ -std=c++11 -c AVL.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o main