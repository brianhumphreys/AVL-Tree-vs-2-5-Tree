#I am a makefile

main:  AVL.cpp main.o
	g++ AVL.cpp main.o -o main

AVL.o: AVL.cpp
	g++ -c AVL.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o main