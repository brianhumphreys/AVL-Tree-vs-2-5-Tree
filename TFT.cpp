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
            destroyRecursive(node->children->at(i));
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
            search(word, root->children->at(MAXCHILDREN));

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

struct TFT::Node* TFT::deleteOne(string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    deleteOne(root, word);
};


struct TFT::Node* TFT::deleteOne(Node *ptr, string word) 
{
    bool found = false;
    Node* predecessor=NULL; //was NULLptr -DR
    Node* current=ptr;

    //Deleting a node
        //delete current;
        //current=NULL;

    if(current==NULL) 
    {
        return current;
    }
    while(current!=NULL)
    {
    //Cases:
    // 1. If the word "word" is in vector words and words only has one node(leaf), delete the word from the vector words
        if(current->words.at(0)->word == word && words.size() == 1)
        {
            if(count != 1)
            {
                count--;
            }
            else
            {
                delete current;
                current = NULL;
            }
        }
    //2. If the key k is in node x and x is an internal node, do the following.
        if (current->words.size() > 1 && (current->words.begin()->word < word && current->words.end()->word > word)
        {
            for (int i=0; i<words.size(); i++)
            {
                if(words[i]->word == word)
                {
                    if(words[i]->count != 1)
                    {
                        count--;
                    }
                    else
                    {
                    words.erase(i);
                    }
                }
            }
        }

        // DR - we have the deleting part secured but we need to check if B tree properties are intact
        if(current->words.size() < MAXVALUES)
        {
            //coo
        }

    //   a) If the child y that precedes k in node x has at least t keys, 
     //   then find the predecessor k0 of k in the sub-tree rooted at y. 
    //        Recursively delete k0, and replace k by k0 in x. (We can find k0 and delete it in a single downward pass.)

       // b) If y has fewer than t keys, then, symmetrically, examine the child z that follows k in node x. 
       // If z has at least t keys, then find the successor k0 of k in the subtree rooted at z. 
      //  Recursively delete k0, and replace k by k0 in x. (We can find k0 and delete it in a single downward pass.)

       // c) Otherwise, if both y and z have only t-1 keys, merge k and all of z into y, so that x loses both k and the pointer to z, 
    //and y now contains 2t-1 keys. Then free z and recursively delete k from y.

    //3. If the key k is not present in internal node x, determine the root x.c(i) of the appropriate subtree that must contain k, if k is in the tree at all. 
      // If x.c(i) has only t-1 keys, execute step 3a or 3b as necessary to guarantee that we descend to a node containing at least t keys. 
      // Then finish by recursing on the appropriate child of x.

       // a) If x.c(i) has only t-1 keys but has an immediate sibling with at least t keys, give x.c(i) an extra key by moving a key 
        //from x down into x.c(i), moving a key from x.c(i) ’s immediate left or right sibling up into x, and moving the 
        //appropriate child pointer from the sibling into x.c(i).

    // b) If x.c(i) and both of x.c(i)’s immediate siblings have t-1 keys, merge x.c(i) with one sibling, which involves moving 
    //  a key from x down into the new merged node to become the median key for that node.
    //
    
    }
    }

        void TFT::insert(string word)
        {

        }
        void TFT::insert(Node* root, string word)
        {

        }

        void TFT::lexSort()
        {

        }
        void TFT::lexSort(Node *node, ofstream &outputFile)
        {

        }

        vector<string> rangeSearch(string begin, string end)
        {
            
        }
        void TFT::rangeSearch(Node *node, vector<string>& rangeVector, string low, string high)
        {

        }

        //Handles directories
        void TFT::parseFileInsert(string fullPath)
        {

        }