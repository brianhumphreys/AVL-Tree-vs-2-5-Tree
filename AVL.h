#ifndef __AVL_H_INCLUDED__
#define __AVL_H_INCLUDED__

#include <string>

class AVL {

    private: 

        struct Node
		{
			//struct Node(string word) : word(word), count(0), right(NULL), left(NULL) {}

			std::string word;
			int count;
			struct Node *right, *left, *parent

            struct Node(std::string word) {
                word = word;
                count = 1;
                right = NULL;
                left = NULL;
            }

		};
		struct Node * root;
    
    public:
        //constructor
        AVL(void);

        //destructor
	    ~AVL();
        void destroyRecursive(Node* node);

        //search functions
	    struct Node * search(std::string word);
        struct Node * searchHelper(struct Node* root, std::string word);

        //utility functions
        struct Node* rotateLeft(Node* y);
        struct Node* rotateRight(Node* y);
        int height(Node* root);

        //insert functions
        struct Node* insert(std::string word);
        struct Node* insert(Node* root, std::string word);

};

#endif