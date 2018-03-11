#I am a makefile

main:  AVL.o  main.o
	g++ -std=c++11 AVL.o main.o -o main

AVL.o: AVL.cpp
	g++ -std=c++11 -c AVL.cpp

main.o: main.cpp
	g++ -c main.cpp

test: test.o
	g++ test.o -o test

test: tftTest.cpp	
	g++ -c tftTest.cpp test

clean: 
	rm -rf *.o main