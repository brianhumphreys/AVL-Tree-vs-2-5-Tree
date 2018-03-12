#I am a makefile

main:  AVL.o TFT.o main.o TFTNode.o
	g++ AVL.o TFT.o main.o TFTNode.o -o main

AVL.o: AVL.cpp
	g++ -c AVL.cpp

TFT.o: TFT.cpp	
	g++ -c TFT.cpp

TFTNode.o: TFTNode.cpp	
	g++ -c TFTNode.cpp

main.o: main.cpp
	g++ -c main.cpp 

clean: 
	rm -rf *.o main