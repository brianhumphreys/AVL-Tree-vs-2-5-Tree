#ifndef __AVL_H_INCLUDED__
#define __AVL_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <dirent.h>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <ctime>

using namespace std;

class AVL {

    private: 

        struct Node
		{
			//struct Node(string word) : word(word), count(0), right(NULL), left(NULL) {}

			string word;
			int count;
			struct Node *right, *left; 

            Node(string word) : word(word), count(1), right(NULL), left(NULL){}
                //word = word;
                //count = 1;
                //right = NULL;std::string
                // left = NULL;
        //}
		};
            int nodeCount;
		    struct Node * root;
    
    public:
        //constructor
        AVL(void);
        //destructor
	    ~AVL();
        void destroyRecursive(Node* node);
        
        void printTree();
        void printTree(Node * root);
        
        bool search(string word);
        bool searchHelper(struct Node* root, string word);
        
        void rotateLeft(Node* y);
        void rotateRight(Node* y);
        void rotationMaker(Node* x, string word);
        
        int height(Node* root);
        bool isBalance(Node* x);
        
        void insert(string word);
        void insert(Node* root, string word);
        
        struct Node* deleteOne(string word);
        struct Node* deleteOne(Node * ptr, string word);
        
        void lexSort(ofstream &outputFile);
        void lexSort(Node *node, ofstream &outputFile);
        
        std::vector<string> rangeSearch(string begin, string end);
        void rangeSearch(Node *node, vector<string>& rangeVector, string low, string high);
};

#endif








