#I am a makefile

main:  AVL.o TFT.o main.o
	g++ AVL.o TFT.o main.o -o main

AVL.o: AVL.cpp
	g++ -c AVL.cpp

TFT.o: TFT.cpp	
	g++ -c TFT.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o main