#include <string>

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