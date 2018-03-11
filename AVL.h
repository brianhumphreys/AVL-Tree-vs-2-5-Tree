#ifndef __AVL_H_INCLUDED__
#define __AVL_H_INCLUDED__

#include <string>
#include <vector>
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
        AVL(void) {
            root = NULL;
            nodeCount = 0;
        }

        //destructor
	    ~AVL() {
            destroyRecursive(root);
        }
        void destroyRecursive(Node* node) {
            if (Node)
            {
                destroyRecursive(Node->left);
                destroyRecursive(Node->right);
                delete Node;
            }
        }

        void printTree() {
            printTree(root);
        }
        void printTree(Node * root) {
            if(root != NULL) {
                printTree(root->left);
                cout << root->word << endl;
                printTree(root->right);
            }
        }

        //search functions
	    void search(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            searchHelper(root, word);
        }
        void searchHelper(struct Node* root, string word) {
            if(root == NULL) 
                cout << "false" << endl;
            else if (word < root->word)
                searchHelper(root->left, word);
            else if (word > root->word)
                searchHelper(root->right, word);
            else cout << "true" << endl;
        }

        //utility functions
        void rotateLeft(Node* y) {

            //label the nodes to be rotated
            Node* x = y->right;
            Node* T = x->left;

            //rotate the nodes
            x->left = y;
            y->right = T;

            //If there was a height variable in the Node then we would 
            //recalculate height here...

            return;

        }
        void rotateRight(Node* y) {
            //label the nodes to be rotated
            Node* x = y->left;
            Node* T = x->right;

            //rotate the nodes
            x->right = y;
            y->left = T;

            //If there was a height variable in the Node then we would 
            //recalculate height here...

            return;
        }

        //inteprets rotations
        void rotationMaker(Node* x, string word) {

            int balance = height(x->left) - height(x->right);
            //Now to perform Rotation Operations
            //CASE 1: LEFT LEFT
            if(balance > 1 && word < x->left->word) 
            {
                rotateRight(x);
                return;
            }

            //CASE 2: LEFT RIGHT
            if (balance > 1 && word > x->left->word)
            {
                rotateLeft(x->left);
                rotateRight(x);
                return;
            }

            //CASE 3: RIGHT LEFT
            if (balance < -1 && word < x->right->word)
            {
                rotateRight(x->right);
                rotateLeft(x);
                return;
            }

            //CASE 4: RIGHT RIGHT
            if (balance < -1 && word > x->right->word)
            {
                rotateLeft(x);
                return;
            }
            else return;
        }
        int height(Node* root) {
            if(root == NULL) 
                return 1;
            else return max(height(root->left), height(root->right)) + 1;
        }

        bool isBalance(Node* x) {
            int balance = height(x->left) - height(x->right);
            if(balance == 1 || 0 || -1)
                return true;
            else
                return false;
        }

        //insert functions
        void insert(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            cout << nodeCount << endl;
            if(this->root != NULL){
                insert(this->root, word);
            }
            else
            {
                this->root = new Node(word);
                nodeCount += 1;
            }


        }
        void insert(Node* root, string word) {
    
            if(word < root->word)
            {
                
                if(root->left != NULL)
                    insert(root->left, word);
                else
                {
                    root->left = new Node(word);
                    nodeCount += 1;
                }  
            }
            else if(word > root->word)
            {
            
                if(root->right != NULL)
                    insert(root->right, word);
                else
                {
                    root->right = new Node(word);
                    nodeCount += 1;
                }
            }
            //word is already in the tree so we increment counter
            else  root->count += 1;

            //find the balance of the tree to know whcih sequence of 
            //rotations to perform
        //    int balance = height(root->left) - height(root->right);
            if (isBalance(root) == false)
            {
                rotationMaker(root, word);
            }
        }

        //Handles directories
        void parseFileInsert(string fullPath);

        //delete function
        struct Node* deleteOne(Node *ptr, string word);
        struct Node* deleteOne(string word);


        void lexSort();
        void lexSort(Node *node, ofstream &outputFile);


        std::vector<string> rangeSearch(string begin, string end);
        void rangeSearch(Node *node, vector<string>& rangeVector, string low, string high);

};

#endif