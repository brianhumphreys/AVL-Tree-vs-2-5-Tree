#ifndef __TFTNODE_H_INCLUDED__
#define __TFTNODE_H_INCLUDED__

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

class TFTNode
{
    //struct for each individual node
    struct Nodelete 
    {
        std::string word;
        int duplicates;

        Nodelete() : word(""), duplicates(0) {}
        Nodelete(std::string word) : word(word), duplicates(0) {}
    };
    struct Nodelete *words;  // An array of words
    int MAXWORDS;      // Minimum degree (defines the range for number of words)
    TFTNode **children; // An array of child pointers
    int wordsInNode;     // Current number of words
    bool leaf; // Is true when node is leaf. Otherwise false
 
    public:
    TFTNode(int _t, bool _leaf);   // Constructor
    
        // A function to traverse all nodes in a subtree rooted with this node
        void traverse();
    
        // A function to search a key in subtree rooted with this node.
        TFTNode *search(std::string word);   // returns NULL if word is not present.
    
        // A function that returns the index of the first key that is greater
        // or equal to word
        int findKey(std::string word);
    
        // A utility function to insert a new key in the subtree rooted with
        // this node. The assumption is, the node must be non-full when this
        // function is called
        void insertNonFull(std::string word);
    
        // A utility function to split the child y of this node. i is index
        // of y in child array children[].  The Child y must be full when this
        // function is called
        void splitChild(int i, TFTNode *y);
    
        // A wrapper function to deleteOne the key word in subtree rooted with
        // this node.
        void deleteOne(std::string word);
    
        // A function to deleteOne the key present in idx-th position in
        // this node which is a leaf
        void removeFromLeaf(int idx);
    
        // A function to deleteOne the key present in idx-th position in
        // this node which is a non-leaf node
        void removeFromNonLeaf(int idx);
    
        // A function to get the predecessor of the key- where the key
        // is present in the idx-th position in the node
        std::string getPred(int idx);


        // A function to get the successor of the key- where the key
        // is present in the idx-th position in the node
        std::string getSucc(int idx);
    
        // A function to fill up the child node present in the idx-th
        // position in the children[] array if that child has less than MAXWORDS-1 words
        void fill(int idx);
    
        // A function to borrow a key from the children[idx-1]-th node and place
        // it in children[idx]th node
        void borrowFromPrev(int idx);
    
        // A function to borrow a key from the children[idx+1]-th node and place it
        // in children[idx]th node
        void borrowFromNext(int idx);
    
        // A function to merge idx-th child of the node with (idx+1)th child of
        // the node
        void merge(int idx);

        void lexSort(std::ofstream &outputFile);

        void rangeSearch(std::vector<std::string>& rangeVector, std::string low, std::string high);
    
        // Make TFT friend of this so that we can access private members of
        // this class in TFT functions
        friend class TFT;
};

#endif
