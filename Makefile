#I am a makefile

main:  AVL.o TFT.o main.o TFTNode.o
	g++ AVL.o TFT.o main.o TFTNode.o -o main

AVL.o: AVL.cpp
	g++ -std=c++11 -c AVL.cpp

TFT.o: TFT.cpp	
	g++ -std=c++11 -c TFT.cpp

TFTNode.o: TFTNode.cpp	
	g++ -std=c++11 -c TFTNode.cpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp 

clean: 
	rm -rf *.o main