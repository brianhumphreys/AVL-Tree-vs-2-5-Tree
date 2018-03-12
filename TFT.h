#include "TFTNode.h"

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

class TFT
{
    TFTNode *root; // Pointer to root node
    int MAXWORDS;  // Minimum degree

public:
 
    // Constructor (Initializes tree as empty)
    TFT(int _t);
 
    void traverse();

    void lexSort();

    void insert(std::string word);

    void deleteOne(std::string word);

    void parseFileInsert(AVL& avl, TFT& tft, string fullPath);

    std::vector<string> rangeSearch(std::string begin, string end);

    TFTNode* search(std::string word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        return (root == NULL)? NULL : root->search(word);
    }
};