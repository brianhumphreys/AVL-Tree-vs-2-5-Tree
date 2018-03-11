#include <string>
#include <vector>

#include "TFT.h"

using namespace std;

TFT::TFT(void) {
    root = NULL;
    nodeCount = 0;
}

TFT::~TFT() {
    destroyRecursive(root);
}

void TFT::destroyRecursive(Node* node) {

    if(node) {
        for(int i = 0; i < MAXCHILDREN; i++) {
            destroyRecursive(node->children->at(i);
        }
        delete node;
    }
}

void TFT::search(string word) {
    search(word, root);
}

void TFT::search(string word, Node *root) {

    //continue if root is not NULL
    if(root) {
        
        //if the word is larger than the last value, then go to last child
        if(word > root->word->at(MAXVALUES)
            search(word, root->children->at(MAXCHILDREN);

        //otherwise, find the right child to recurse into
        else {
            for(int i = 0; i < MAXVALUES; i++) {

                //return true if matching
                if(word == root->word->at(i) 
                    cout << "True" << endl;

                //if word is less than index value, recurse to this child
                else if(word < root->word->at(i)
                    search(word, root->children->at(i);
                
            }
        }

    }
    //if node is NULL, then word is not in the tree
    else 
        cout << "False" << endl;
}


bool TFT::hasMaxChildren() {

    bool isMax;
    if(children.size() < MAXCHILDREN)
        isMax = true;
    else 
        isMax = false;

    return isMax;
}

void insert(string word);
{
    //if tree is empty
    if(root == NULL) {
        root = new Node(word);
    }
    //if tree is not empty
    else {
        //if root is full
        if (root->words.size() == MAXVALUES) {
            //create a new node
            Node * newRoot = new Node();

            //make old root the new root
            newRoot->children[0] = root;

            //split old root and make children of new root
            
        }
    }
}
void insertNonFull(string word);
void splitChild(string word, Node *node) {

    //new node will hold 
    Node *newNode = new Node();

    //copy all but 1 word over to new node
    for (int i = 0; i < node->words.length() - 1; i++) {
        newNode->words.push(node->words.at(i+1));
    }

    //if node was not a leaf, 
    if (node->isLeaf == false) {
        for (int i = 0; i < node)
    }

    for(int j = )
}