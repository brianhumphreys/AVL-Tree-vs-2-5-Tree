#ifndef __AVL_H_INCLUDED__
#define __AVL_H_INCLUDED__

#include <string>
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

        void printRoot();

        //search functions
	    struct Node * search(string word);
        struct Node * searchHelper(struct Node* root, string word);

        //utility functions
        void rotateLeft(Node* y);
        void rotateRight(Node* y);
        int height(Node* root);

        //insert functions
        void insert(string word);
        void insert(Node* root, string word);

        //Handles directories
        void parseFileInsert(string fullPath);

        //inteprets rotations
        void rotationMaker(Node* x, string word);
        bool isBalance(Node* x);

        //delete function
        struct Node* deleteOne(Node *ptr, string word);
        struct Node* deleteOne(string word);

};

#endif